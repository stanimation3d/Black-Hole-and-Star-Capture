#include "game_draw.h"
#include <raylib.h>
#include <stdio.h> // TextFormat kullanmak için

// ======================================================
// ÇİZİM FONKSİYONU
// ======================================================

// Oyunun tüm bileşenlerini çizen ana fonksiyon
void DrawGame(GameScreen currentScreen, const Assets *assets, const Player *player, const Enemy *enemy, const Star *star)
{
    // Çizime Başla
    BeginDrawing();
    
    // 1. ARKA PLANI ÇİZ (blackground.jpg)
    // Arkaplanı ekranın sol üst köşesinden başlayarak çizer
    DrawTexture(assets->blackground, 0, 0, WHITE);

    // 2. OYUN DURUMUNA GÖRE ÇİZİM YAP
    if (currentScreen == GAMEPLAY)
    {
        // ======================================================
        // OYNANIŞ (GAMEPLAY) EKRANI ÇİZİMİ
        // ======================================================
        
        // Yıldızı Çiz (star.jpg)
        // DrawTextureV, Vector2 konumunu doğrudan kullanmaya izin verir
        DrawTextureV(assets->starTex, star->position, WHITE);

        // Beyaz Deliği (Düşmanı) Çiz (whitehole.png)
        DrawTextureV(assets->whiteHoleTex, enemy->position, WHITE);
        
        // Karadeliği (Oyuncuyu) Çiz (blackhole.png)
        DrawTextureV(assets->blackHoleTex, player->position, WHITE);
        
        // HUD (Head-Up Display) Çizimi (Puan ve Hız)
        
        // Puan
        DrawText(
            TextFormat("Puan: %i", player->points), 
            10, 10, 20, 
            RAYWHITE
        );
        
        // Hız (Düşmanın hareketini de etkileyen hız değişkeni)
        DrawText(
            TextFormat("Hız (Düşman Takip): %.2f", player->speed), 
            10, 35, 20, 
            RAYWHITE
        );
        
        // Debug amaçlı yarıçapları çiz (opsiyonel, görseller yüklenince kaldırılabilir)
        // DrawCircleLines((int)player->position.x, (int)player->position.y, player->radius, GREEN);
        // DrawCircleLines((int)enemy->position.x, (int)enemy->position.y, enemy->radius, RED);
        // DrawCircleLines((int)star->position.x, (int)star->position.y, star->radius, YELLOW);

    }
    else if (currentScreen == ENDING)
    {
        // ======================================================
        // OYUN BİTTİ (ENDING) EKRANI ÇİZİMİ
        // ======================================================

        // Game Over Resmini Çiz (gameover.png)
        // Resmi ekranın ortasına hizala
        int go_x = SCREEN_WIDTH/2 - assets->gameOverTex.width/2;
        int go_y = SCREEN_HEIGHT/2 - assets->gameOverTex.height/2;
        
        DrawTexture(assets->gameOverTex, go_x, go_y, WHITE);
        
        // Son Puanı Game Over resminin altına ortala
        const char* scoreText = TextFormat("SON PUAN: %i", player->points);
        int score_x = SCREEN_WIDTH/2 - MeasureText(scoreText, 30)/2;
        int score_y = go_y + assets->gameOverTex.height + 20;
        
        DrawText(scoreText, score_x, score_y, 30, WHITE);
    }
    
    // Çizimi Bitir
    EndDrawing();
}
