#include "game_logic.h"
#include <raylib.h>
#include <raymath.h>
#include <math.h> // Vektör normalleştirme (sqrtf) için gerekli

// ======================================================
// OYUNCU GÜNCELLEME (Karadelik Kontrolü)
// ======================================================
// Scratch Kodu: WASD/Ok tuşlarına basılınca konumu 10 değiştir.
void UpdatePlayer(Player *player, float deltaTime)
{
    // Scratch kodundaki '10 kadar değiştir' değeri. 
    // Frame Rate Independent Movement (Kare Hızı Bağımsız Hareket) için DeltaTime ile çarpmamız gerekir.
    // Ancak Scratch basit bir mantık kullandığı için, hız * player.speed yapabiliriz.
    // VEYA, daha basit ve Scratch'e yakın olması için sabit bir hareket değeri kullanalım:
    float movement = 5.0f * 60 * deltaTime; // 60 FPS'e normalize edilmiş 5 piksel adım

    // Yukarı/W
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        player->position.y -= movement;
    }
    // Aşağı/S
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        player->position.y += movement;
    }
    // Sağ/D
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        player->position.x += movement;
    }
    // Sol/A
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player->position.x -= movement;
    }

    // Karadelik, ekran sınırları içinde kalsın (opsiyonel ama iyi bir pratik)
    player->position.x = Clamp(player->position.x, player->radius, SCREEN_WIDTH - player->radius);
    player->position.y = Clamp(player->position.y, player->radius, SCREEN_HEIGHT - player->radius);
}


// ======================================================
// DÜŞMAN GÜNCELLEME (Beyaz Delik Kovalama)
// ======================================================
// Scratch Kodu: "Speed saniyede Black Hole'a git"
void UpdateEnemy(Enemy *enemy, const Player *player)
{
    // Yön vektörünü hesapla (Düşmandan Oyuncuya)
    Vector2 direction = {
        player->position.x - enemy->position.x,
        player->position.y - enemy->position.y
    };

    // Vektörün uzunluğunu (mesafeyi) hesapla
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

    // Yön vektörünü normalleştir (uzunluğunu 1 yap)
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }
    
    // Düşmanı, Karadeliğin hızı (player->speed) ile hareket ettir.
    // Bu hareket hızı, Oyuncunun hız değişkeninden (player->speed) alınmıştır.
    enemy->position.x += direction.x * player->speed; 
    enemy->position.y += direction.y * player->speed;
}


// ======================================================
// YILDIZ GÜNCELLEME (Rastgele Hareket Animasyonu)
// ======================================================
// Scratch Kodu: "sürekli tekrarla: 1 saniyede rastgele konum git"
void UpdateStar(Star *star, float deltaTime)
{
    // 1. Yıldızı Hedefe Doğru Hareket Ettir (Animasyon)
    if (star->moveTimer < star->moveTime)
    {
        star->moveTimer += deltaTime;
        // İlerleme yüzdesi (0.0'dan 1.0'a)
        float progress = star->moveTimer / star->moveTime; 
        
        // Lerp (Doğrusal Enterpolasyon) ile yumuşak geçiş.
        // NOT: Raylib'de Lerp(start, end, amount) mevcuttur.
        star->position = Vector2Lerp(star->position, star->targetPosition, progress);
    }

    // 2. Rastgele Konum Belirleme Mantığı
    if (star->moveTimer >= star->moveTime)
    {
        // Hareket tamamlandığında, yeni hedefi belirle
        
        // Yeni rastgele konumu ayarla (Ekran sınırları içinde)
        star->targetPosition.x = (float)GetRandomValue(star->radius, SCREEN_WIDTH - star->radius);
        star->targetPosition.y = (float)GetRandomValue(star->radius, SCREEN_HEIGHT - star->radius);
        
        // Sayacı sıfırla, hareket yeniden başlasın
        star->moveTimer = 0.0f;
    }
}


// ======================================================
// ÇARPIŞMA KONTROLLERİ
// ======================================================
// Scratch Kodu: Yıldız değiyor mu? / Black Hole değiyor mu?
GameScreen CheckCollisions(Player *player, Enemy *enemy, Star *star, Assets *assets, GameScreen currentScreen)
{
    // Sadece oyun oynanıyorken kontrol et
    if (currentScreen != GAMEPLAY)
    {
        return currentScreen;
    }

    // --------------------------------------------------
    // 1. YILDIZ YAKALAMA (Star Capture)
    // --------------------------------------------------
    // Yıldıza anlık olarak değiyor mu? (isTouchingStar durumunu güncelle)
    bool currentTouch = CheckCollisionCircles(
        player->position, player->radius, 
        star->position, star->radius
    );
    
    if (currentTouch) 
    {
        // Eğer değiyorsa, sayacı artır
        player->captureTimer += GetFrameTime(); // GetFrameTime() = deltaTime
        
        // Eğer süre dolduysa (0.05 saniye)
        if (player->captureTimer >= 0.05f) 
        {
            // Puanı ver ve hızı ayarla
            player->points += 1;
            PlaySound(assets->coinSound); 
            player->speed += 0.03125f; 

            // Sayacı sıfırla (Puan alındı, yeniden saymaya başla)
            player->captureTimer = 0.0f; 
            
            // Yıldızı ışınla (bir sonraki karede yeni konuma gitsin)
            star->moveTimer = star->moveTime; 
        }
    }
    else
    {
        // Eğer değmiyorsa, sayacı sıfırla
        player->captureTimer = 0.0f;
    }


    // --------------------------------------------------
    // 2. OYUN BİTİŞİ (Game Over - Beyaz Deliğe Çarpma)
    // --------------------------------------------------
    if (CheckCollisionCircles(
        player->position, player->radius, 
        enemy->position, enemy->radius
    ))
    {
        // Scratch: GameOver haberini sal
        // Scratch: Boom Cloud sesini başlat
        
        // Oyun durumunu ENDING olarak değiştir
        GameScreen newScreen = ENDING;

        // Sesi sadece bir kere çal (eğer GAMEPLAY durumundan geldiysek)
        if (currentScreen == GAMEPLAY)
        {
            PlaySound(assets->boomCloudSound);
        }

        // Scratch: Durdur tümü (Oyun döngüsü ENDING durumuna geçince kendiliğinden duracak)
        return newScreen;
    }

    return currentScreen; // Eğer çarpışma yoksa, mevcut durumu geri döndür
}
