#include<SDL.h>
#include<stdio.h>
#include"structures.h"
#include "objects.h"

void initGameObject(GameObject* obj, int x, int y, int width, int height, int velocityX, int velocityY, int speed, SDL_Rect sourceRect) {
	obj->position.x = x;
	obj->position.y = y;
	obj->sprite.width = width;
	obj->sprite.height = height;
	obj->sprite.texture = NULL;
	obj->physics.velocityX = velocityX;
	obj->physics.velocityY = velocityY;
	obj->physics.speed = speed;
	obj->sourceRect = sourceRect;
}

void updateGameObject(GameObject* obj) {
	obj->position.x += obj->physics.velocityX * obj->physics.speed;
	obj->position.y += obj->physics.velocityY * obj->physics.speed;
}

void randomPosition(GameObject* obj)
{
	int indexX = -600;
	int indexY = -600;
	obj->position.x = (rand() % 540);
	obj->position.y = -(rand() % 600);
	obj->physics.speed = fallingSpeed;

}

void updateAllGameObjects(GameObjects* gameObjects, GameState* gameState) {
	updateGameObject(&gameObjects->pig);
	updateGameObject(&gameObjects->banana);
	updateGameObject(&gameObjects->apple);
	updateGameObject(&gameObjects->yellowapple);
	updateGameObject(&gameObjects->greenapple);
	updateGameObject(&gameObjects->tuica);
	updateGameObject(&gameObjects->shield);
	updateGameObject(&gameObjects->shieldRay);
	for (int i = 0; i < nr_woods; i++)
	{
		updateGameObject(&gameObjects->wood[i]);
	}

	if (*gameState == GAMECOOP)
	{
		updateGameObject(&gameObjects->pig2);
	}
}
