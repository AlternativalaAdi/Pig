#include "structures.h"
#include<stdio.h>
#include<SDL.h>
#include "collisions.h"



void collisions(GameObjects* gameObjects, GameState* gameState)
{

	if (!shieldEquiped)
	{
		for (int i = 0; i < nr_woods; i++)
		{
			if (checkCollision(&gameObjects->pig, &gameObjects->wood[i]))
			{
				livesCount--;
				randomPosition(&gameObjects->wood[i]);
			}
		}
	}


	if (checkCollision(&gameObjects->pig, &gameObjects->banana))
	{
		score++;
		randomPosition(&gameObjects->banana);
	}
	if (checkCollision(&gameObjects->pig, &gameObjects->apple))
	{
		score++;
		randomPosition(&gameObjects->apple);
	}
	if (checkCollision(&gameObjects->pig, &gameObjects->greenapple))
	{
		score++;
		randomPosition(&gameObjects->greenapple);
	}
	if (checkCollision(&gameObjects->pig, &gameObjects->yellowapple))
	{
		score++;
		randomPosition(&gameObjects->yellowapple);
	}

	if (checkCollision(&gameObjects->pig, &gameObjects->tuica))
	{
		if (livesCount < 5)
		{
			livesCount++;
		}
		gameObjects->tuica.position.x = -100;
		gameObjects->tuica.position.y = -100;
	}

	if (checkCollision(&gameObjects->pig, &gameObjects->shield))
	{
		shieldEquiped = true;
	}

	if (*gameState == GAMECOOP)
	{
		if (!shieldEquiped)
		{
			for (int i = 0; i < nr_woods; i++)
			{
				if (checkCollision(&gameObjects->pig2, &gameObjects->wood[i]))
				{
					livesCount2--;
					randomPosition(&gameObjects->wood[i]);
				}
			}
		}

		if (checkCollision(&gameObjects->pig2, &gameObjects->banana))
		{
			score2++;
			randomPosition(&gameObjects->banana);
		}
		if (checkCollision(&gameObjects->pig2, &gameObjects->apple))
		{
			score2++;
			randomPosition(&gameObjects->apple);
		}
		if (checkCollision(&gameObjects->pig2, &gameObjects->greenapple))
		{
			score2++;
			randomPosition(&gameObjects->greenapple);
		}
		if (checkCollision(&gameObjects->pig2, &gameObjects->yellowapple))
		{
			score2++;
			randomPosition(&gameObjects->yellowapple);
		}

		if (checkCollision(&gameObjects->pig2, &gameObjects->tuica))
		{
			if (livesCount2 < 5)
			{
				livesCount2++;
			}
			gameObjects->tuica.position.x = -100;
			gameObjects->tuica.position.y = -100;
		}
		if (checkCollision(&gameObjects->pig2, &gameObjects->shield))
		{
			shieldEquiped = true;
		}
	}
	if (livesCount <= 0 || livesCount2 <= 0) {
		*gameState = GAMEOVER;
	}

}

int checkCollision(GameObject* obj1, GameObject* obj2)
{

	if (obj1->position.x + obj1->sprite.width > obj2->position.x &&
		obj1->position.x <obj2->position.x + obj2->sprite.width &&
		obj1->position.y + obj1->sprite.height > obj2->position.y &&
		obj1->position.y < obj2->position.y + obj2->sprite.height)
	{
		return 1;
	}
	return 0;

}