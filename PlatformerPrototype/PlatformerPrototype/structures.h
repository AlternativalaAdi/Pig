#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <SDL.h>
#define WIDTH 600
#define HEIGHT 800
#define nr_woods 3

int score = 0;
int score2 = 0;
int livesCount = 5;
int livesCount2 = 5;
int fallingSpeed = 10;
int pig2Initialized = 0;
int shield = 0;



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
} GameObjects;

GameObjects gameObjects;

#endif