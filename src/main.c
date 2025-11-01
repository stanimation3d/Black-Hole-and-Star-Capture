#include <raylib.h>
#include <raymath.h>
#include "game_structs.h" // Tüm yapılar (Player, Enemy, Star, Assets) ve sabitler
#include "game_logic.h"   // Oyun mantığı fonksiyonları (Update, CheckCollisions)
#include "game_draw.h"    // Çizim fonksiyonları (DrawGame)
#include <stdio.h>

// ======================================================
// YARDIMCI FONKSİYONLAR
// ======================================================

// Varlıkları yükler ve Assets yapısını döndürür
Assets LoadGameAssets(void)
{
    Assets assets = { 0 };
    
    // NOT: Bu dosyaların "main.c" ile aynı dizinde veya Raylib'in arama yaptığı 
    // yolda olduğundan emin olun!
    
    // Görselleri Yükle
    // Eğer resim dosyalarını bulamazsa, Raylib hata verecektir.
    assets.blackground = LoadTexture("blackground.jpg");
    assets.blackHoleTex = LoadTexture("blackhole.png");
    assets.whiteHoleTex = LoadTexture("whitehole.png");
    assets.starTex = LoadTexture("star.png");
    assets.gameOverTex = LoadTexture("gameover.png");

    // Sesleri Yükle
    // Varsayım: coin.wav ve boom_cloud.wav dosyaları mevcuttur.
    InitAudioDevice(); 
    assets.coinSound = LoadSound("coin.wav"); 
    assets.boomCloudSound = LoadSound("boom_cloud.wav"); 
    assets.backgroundMusic = LoadMusicStream("bg_music.mp3"); // Dosya adınızı buraya yazın
    // Müziği hemen çalmaya başla
    PlayMusicStream(assets.backgroundMusic);
    
    return assets;
}

// Yüklenen tüm varlıkları bellekten boşaltır
void UnloadGameAssets(const Assets *assets)
{
    // Görselleri Boşalt
    UnloadTexture(assets->blackground);
    UnloadTexture(assets->blackHoleTex);
    UnloadTexture(assets->whiteHoleTex);
    UnloadTexture(assets->starTex);
    UnloadTexture(assets->gameOverTex);

    // Sesleri Boşalt ve Ses Cihazını Kapat
    UnloadSound(assets->coinSound);
    UnloadSound(assets->boomCloudSound);
    UnloadMusicStream(assets->backgroundMusic);
    CloseAudioDevice();
}


// ======================================================
// ANA FONKSİYON
// ======================================================

int main(void)
{
    // 1. Raylib Penceresini Başlat
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Black Hole and Star Capture");
    SetTargetFPS(60); // Oyun hızını sabit 60 FPS'te tut

    // 2. Varlıkları Yükle
    Assets gameAssets = LoadGameAssets();

    // 3. Oyun Varlıklarını Başlat (Scratch'teki "e tıklandığında" mantığı)
    
    // Karadelik (Oyuncu)
    Player blackHole = {
        .texture = gameAssets.blackHoleTex,
        .position = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f }, // Merkez
        .speed = 0.25f,           // Başlangıç hızı (Scratch: 4 yap)
        .points = 0,             // Başlangıç puanı (Scratch: 0 yap)
        .radius = 30.0f,         // Çarpışma yarıçapı
        .captureTimer = 0.0f,
    };
    
    // Beyaz Delik (Düşman)
    Enemy whiteHole = {
        .texture = gameAssets.whiteHoleTex,
        .position = { -100.0f, 100.0f }, // Başlangıç konumu (Scratch: x: -100, y: 100)
        .radius = 30.0f
    };
    
    // Yıldız
    Star star = {
        .texture = gameAssets.starTex,
        .position = { 100.0f, 100.0f },  // Başlangıç konumu (Scratch: x: 100, y: 100)
        .targetPosition = { 100.0f, 100.0f }, 
        .moveTime = 1.0f, 
        .moveTimer = 1.0f,               // Hemen rastgele konum seçilmesi için 1.0f
        .radius = 25.0f
    };

    // Oyun Durumu
    GameScreen currentScreen = GAMEPLAY;

    // Rastgele sayı üreticiyi başlat
    SetRandomSeed(GetTime());
    
    // ======================================================
    // 4. ANA OYUN DÖNGÜSÜ
    // ======================================================

    while (!WindowShouldClose()) 
    {
        // Her kare için geçen süreyi al (Kare Hızı Bağımsızlık için)
        float deltaTime = GetFrameTime(); 

        // --------------------------------------------------
        // GÜNCELLEME (LOGIC) KISMI
        // --------------------------------------------------
        if (currentScreen == GAMEPLAY)
        {
            // Oyuncu kontrolü
            UpdatePlayer(&blackHole, deltaTime);
            
            // Düşman takibi
            UpdateEnemy(&whiteHole, &blackHole);
            
            // Yıldız hareketi
            UpdateStar(&star, deltaTime);

            // Müzik akışını her karede güncelle (Sürekli çalmasını sağlar)
            UpdateMusicStream(gameAssets.backgroundMusic);

            // Çarpışmaları kontrol et ve oyun durumunu güncelle
            currentScreen = CheckCollisions(&blackHole, &whiteHole, &star, &gameAssets, currentScreen);
        }
        else if (currentScreen == ENDING)
        {
            // Game Over ekranında yeniden başlama (Opsiyonel)
            if (IsKeyPressed(KEY_SPACE))
            {
                // TODO: Oyunu yeniden başlatan bir fonksiyon çağrılabilir
            }
        }

        // --------------------------------------------------
        // ÇİZİM (DRAW) KISMI
        // --------------------------------------------------
        // Tüm çizim görevlerini DrawGame fonksiyonuna devret
        DrawGame(currentScreen, &gameAssets, &blackHole, &whiteHole, &star);
    }

    // ======================================================
    // 5. TEMİZLEME VE KAPATMA
    // ======================================================
    UnloadGameAssets(&gameAssets);
    CloseWindow(); 

    return 0;
}
