#ifndef GAME_DRAW_H
#define GAME_DRAW_H

#include "game_structs.h" // Player, Enemy, Star yapılarını ve sabitleri kullanmak için

// Oyunun tüm bileşenlerini (Arkaplan, Varlıklar, HUD, Game Over ekranı) çizer.
void DrawGame(GameScreen currentScreen, const Assets *assets, const Player *player, const Enemy *enemy, const Star *star);

#endif // GAME_DRAW_H
