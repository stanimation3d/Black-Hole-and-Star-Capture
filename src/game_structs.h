#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

// Raylib kütüphanesini dahil et (Vector2, Texture2D, Sound vb. tipleri için gereklidir)
#include <raylib.h>

// ======================================================
// OYUN SABİTLERİ
// ======================================================
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// ======================================================
// OYUN DURUMU (GameScreen)
// ======================================================

// Scratch kodundaki 'GameOver haberi' ve 'durdur tümü' komutlarını yönetmek için
typedef enum GameScreen {
    GAMEPLAY,  // Oyun oynanıyor
    ENDING     // Game Over ekranı
} GameScreen;


// ======================================================
// OYUNCU YAPISI (Karadelik)
// ======================================================

typedef struct Player {
    Texture2D texture; // blackhole.png (Dokusu)
    Vector2 position;  // Konumu (x, y)
    float speed;       // Hız değişkeni (Beyaz Deliğin takip hızı olarak da kullanılıyor)
    int points;        // Puan değişkeni
    float radius;      // Çarpışma için yarıçap
    float captureTimer; // Yıldıza sürekli değme süresini sayar (Hedef: 0.25 saniye)
    bool isTouchingStar; // Yıldıza şu an değiyor mu?
} Player;


// ======================================================
// DÜŞMAN YAPISI (Beyaz Delik)
// ======================================================

typedef struct Enemy {
    Texture2D texture; // whitehole.png (Dokusu)
    Vector2 position;  // Konumu (x, y)
    float radius;      // Çarpışma için yarıçap
} Enemy;


// ======================================================
// YILDIZ YAPISI (Yakalanacak Nesne)
// ======================================================

typedef struct Star {
    Texture2D texture;       // star.jpg (Dokusu)
    Vector2 position;        // Mevcut konumu (x, y)
    Vector2 targetPosition;  // Gideceği hedef konum (Rastgele hareket için)
    float moveTime;          // 1.0 saniyelik hareket süresi
    float moveTimer;         // Hareket için geçen süre sayacı
    float radius;            // Çarpışma için yarıçap
} Star;


// ======================================================
// Varlık YÖNETİM YAPISI (Assets)
// ======================================================

// Oyunda kullanılan tüm görsel ve ses dosyalarını içerir
typedef struct Assets {
    Texture2D blackground;  // blackground.jpg
    Texture2D blackHoleTex; // blackhole.png
    Texture2D whiteHoleTex; // whitehole.png
    Texture2D starTex;      // star.jpg
    Texture2D gameOverTex;  // gameover.png
    Sound boomCloudSound;   // Game Over sesi ("Boom Cloud")
    Sound coinSound;        // Yıldız yakalama sesi ("Coin")
    Music backgroundMusic;
} Assets;


#endif // GAME_STRUCTS_H
