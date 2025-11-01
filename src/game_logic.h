#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "game_structs.h" // Player, Enemy, Star yapılarını ve sabitleri kullanmak için

// Oyuncu hareketini yönetir (WASD ve Ok tuşları)
void UpdatePlayer(Player *player, float deltaTime);

// Düşman (Beyaz Delik) takibini yönetir
void UpdateEnemy(Enemy *enemy, const Player *player);

// Yıldızın rastgele hareket animasyonunu yönetir
void UpdateStar(Star *star, float deltaTime);

// Çarpışmaları kontrol eder ve oyun durumunu günceller
GameScreen CheckCollisions(Player *player, Enemy *enemy, Star *star, Assets *assets, GameScreen currentScreen);

#endif // GAME_LOGIC_H
