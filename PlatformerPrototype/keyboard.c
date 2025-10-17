#include<stdio.h>
#include<SDL.h>
#include "structures.h"
#include "keyboard.h"


void handleInput(GameObject* obj) {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);


	if (keystate[SDL_SCANCODE_A] && obj->position.x > 0) {
		obj->physics.velocityX = -1;
		obj->sourceRect.y = 64;
	}

	else if (keystate[SDL_SCANCODE_D] && obj->position.x < 500) {
		obj->physics.velocityX = 1;
		obj->sourceRect.y = 0;
	}

	else {
		obj->physics.velocityX = 0;
	}
}

void handleInput2(GameObject* obj) {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);


	if (keystate[SDL_SCANCODE_LEFT] && obj->position.x > 0) {
		obj->physics.velocityX = -1;
		obj->sourceRect.y = 64;
	}

	else if (keystate[SDL_SCANCODE_RIGHT] && obj->position.x < 500) {
		obj->physics.velocityX = 1;
		obj->sourceRect.y = 0;
	}
	else {
		obj->physics.velocityX = 0;
	}
}


void handleMenu(SDL_Event* event, GameState* gameState, GameObjects* objects, GameObject* obj)
{

	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			int mouseX = event->button.x;
			int mouseY = event->button.y;
			printf("Mouse clicked at: (%d, %d)\n", mouseX, mouseY);
			if (mouseX >= 200 && mouseX <= 200 + 200 &&
				mouseY >= 150 && mouseY <= 150 + 150)
			{

				*gameState = SKINS;
				printf("Switching to GAME state\n");
			}

			if (mouseX >= 200 && mouseX <= 200 + 200 &&
				mouseY >= 500 && mouseY <= 500 + 150)
			{
				*gameState = GAMECOOP;

			}

		}
	}
}



void handleSkins(SDL_Event* event, GameState* gameState, GameObjects* objects, GameObject* obj)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			int mouseX = event->button.x;
			int mouseY = event->button.y;
			printf("Mouse clicked at: (%d, %d)\n", mouseX, mouseY);
			if (mouseX >= 100 && mouseX <= 100 + 100 &&
				mouseY >= 100 && mouseY <= 100 + 100)
			{
				obj->sourceRect.x = 0;
				printf("%d\n", obj->sourceRect.x);
				*gameState = GAME;
			}
			if (mouseX >= 100 && mouseX <= 100 + 100 &&
				mouseY >= 250 && mouseY <= 250 + 100)
			{
				obj->sourceRect.x = 64;
				printf("%d\n", obj->sourceRect.x);
				*gameState = GAME;
			}
			if (mouseX >= 100 && mouseX <= 100 + 100 &&
				mouseY >= 400 && mouseY <= 400 + 100)
			{
				obj->sourceRect.x = 128;
				printf("%d\n", obj->sourceRect.x);
				*gameState = GAME;
			}
			if (mouseX >= 100 && mouseX <= 100 + 100 &&
				mouseY >= 550 && mouseY <= 550 + 100)
			{
				obj->sourceRect.x = 192;
				printf("%d\n", obj->sourceRect.x);
				*gameState = GAME;
			}


		}
	}
}



