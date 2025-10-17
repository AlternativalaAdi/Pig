#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <SDL.h>
#include <stdbool.h>
#define WIDTH 600
#define HEIGHT 800
#define nr_woods 3

extern int score;
extern int score2;
extern int livesCount;
extern int livesCount2;
extern int fallingSpeed;
extern bool pig2Initialized;
extern bool shieldEquiped;
extern const Uint32 tuicaSpawnInterval;
extern const Uint32 woodSpawnInterval;
extern const Uint32 shieldSpawnInterval;
extern const Uint32 shieldDuration;


typedef enum {
	MENU = 0,
	GAME,
	SKINS,
	GAMECOOP,
	GAMEOVER,
	PAUSED
}GameState;


typedef struct {
	int x, y;
} Position;

typedef struct {
	int width, height;
	SDL_Texture* texture;
} Sprite;

typedef struct {
	int velocityX, velocityY;
	int speed;
} Physics;


typedef struct {
	Position position;
	Sprite sprite;
	Physics physics;
	SDL_Rect sourceRect;
} GameObject;

typedef struct {
	GameObject pig;
	GameObject pig2;
	GameObject pig3;
	GameObject pig4;
	GameObject banana;
	GameObject apple;
	GameObject greenapple;
	GameObject yellowapple;
	GameObject wood[nr_woods];
	GameObject shield;
	GameObject lives;
	GameObject tuica;
	GameObject shieldRay;
} GameObjects;

GameObjects gameObjects;

#endif