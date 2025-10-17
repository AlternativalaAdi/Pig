#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <SDL_ttf.h>
#include "srcRects.h"
#include "structures.h"
#include "render.h"
#include "ttf.h"
#include "collisions.h"
#include "objects.h"

initTTF();

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filePath) {
	SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
	if (texture == NULL) {
		printf("Unable to load texture: %s\n", IMG_GetError());
	}
	return texture;
}

int main()
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Multiple GameObjects from Sprite Sheet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	initTTF();

	Uint32 startTime = SDL_GetTicks();
	Uint32 elapsedTime = 0;

	const Uint32 tuicaSpawnInterval = 10000;
	const Uint32 woodSpawnInterval = 15000;
	const Uint32 shieldSpawnInterval = 10000;
	const Uint32 shieldDuration = 5000;

	Uint32 lastTuicaSpawnTime = startTime;
	Uint32 lastShieldSpawnTime = startTime;
	Uint32 lastShieldActivation = startTime;


	printf("%d\n", startTime);

	SDL_Texture* spriteSheet = loadTexture(renderer, "imagini.png");
	SDL_Texture* background = loadTexture(renderer, "back.png");

	initGameObject(&gameObjects.pig, 250, 680, 100, 100, 0, 0, 10, pigSource1);
	initGameObject(&gameObjects.pig2, 450, 680, 100, 100, 0, 0, 10, pig2Source1);
	initGameObject(&gameObjects.pig3, 250, 680, 100, 100, 0, 0, 10, pig3Source1);
	initGameObject(&gameObjects.pig4, 450, 680, 100, 100, 0, 0, 10, pig4Source1);
	initGameObject(&gameObjects.banana, 0, 0, 50, 50, 0, 1, 0, bananaSource);
	initGameObject(&gameObjects.apple, 0, 0, 50, 50, 0, 1, 0, appleSource);
	initGameObject(&gameObjects.shield, -69, -60, 50, 50, 0, 1, 0, shieldSource);
	initGameObject(&gameObjects.greenapple, 0, 0, 50, 50, 0, 1, 0, greenappleSource);
	initGameObject(&gameObjects.yellowapple, 0, 0, 50, 50, 0, 1, 0, yellowappleSource);
	initGameObject(&gameObjects.shieldRay, 0, 0, 0, 0, 0, 1, 0, shieldRaySource);

	for (int i = 0; i < nr_woods; i++)
	{
		initGameObject(&gameObjects.wood[i], rand() % 500, -(rand() % 600), 50, 50, 0, 1, 0, woodSource);
	}
	initGameObject(&gameObjects.lives, 10, 10, 50, 50, 0, 0, 0, livesSource);
	initGameObject(&gameObjects.tuica, 0, -70, 50, 50, 0, 1, 0, tuicaSource);
	

	randomPosition(&gameObjects.banana);
	randomPosition(&gameObjects.apple);
	randomPosition(&gameObjects.greenapple);
	randomPosition(&gameObjects.yellowapple);
	for (int i = 0; i < nr_woods; i++)
	{
		randomPosition(&gameObjects.wood[i]);
	}

	gameObjects.pig.sprite.texture = spriteSheet;
	gameObjects.pig2.sprite.texture = spriteSheet;
	gameObjects.pig3.sprite.texture = spriteSheet;
	gameObjects.pig4.sprite.texture = spriteSheet;
	gameObjects.banana.sprite.texture = spriteSheet;
	gameObjects.apple.sprite.texture = spriteSheet;
	gameObjects.yellowapple.sprite.texture = spriteSheet;
	gameObjects.greenapple.sprite.texture = spriteSheet;
	gameObjects.shield.sprite.texture = spriteSheet;
	gameObjects.shieldRay.sprite.texture = spriteSheet;
	for (int i = 0; i < nr_woods; i++) {
		gameObjects.wood[i].sprite.texture = spriteSheet;
	}
	gameObjects.lives.sprite.texture = spriteSheet;
	gameObjects.tuica.sprite.texture = spriteSheet;
	

	int quit = 0;
	SDL_Event e;

	GameState gameState = MENU;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = 1;
			}
			elapsedTime = SDL_GetTicks() - startTime;

			
			if (gameState == GAMEOVER)
			{
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
					gameState = MENU;
					livesCount = 5;
					livesCount2 = 5;
					score = 0;
					score2 = 0;
					gameObjects.pig.position.x = 250;
					gameObjects.pig.position.y = 680;
					gameObjects.pig2.position.x = 350;
					gameObjects.pig2.position.y = 680;
					randomPosition(&gameObjects.banana);
					randomPosition(&gameObjects.apple);
					randomPosition(&gameObjects.greenapple);
					randomPosition(&gameObjects.yellowapple);
					for (int i = 0; i < nr_woods; i++)
					{
						randomPosition(&gameObjects.wood[i]);
					}
					startTime = SDL_GetTicks();
				}

			}
			if (gameState == MENU)
			{
				displayMenu(renderer,&gameObjects.lives);
				handleMenu(&e, &gameState,&gameObjects,&gameObjects.pig);
			}
			if (gameState == SKINS)
			{
				displayeSkins(renderer, &gameObjects.pig, &gameObjects.pig2, &gameObjects.pig3, &gameObjects.pig4);
				handleSkins(&e, &gameState, &gameObjects, &gameObjects.pig);
			}
		}
		
		if (gameState == GAME || gameState == GAMECOOP)
		{
			collisions(&gameObjects,&gameState);
			handleInput(&gameObjects.pig);
			if(gameState == GAMECOOP)handleInput2(&gameObjects.pig2);

			if (gameObjects.banana.position.y > HEIGHT) randomPosition(&gameObjects.banana);
			if (gameObjects.apple.position.y > HEIGHT) randomPosition(&gameObjects.apple);
			if (gameObjects.greenapple.position.y > HEIGHT) randomPosition(&gameObjects.greenapple);
			if (gameObjects.yellowapple.position.y > HEIGHT) randomPosition(&gameObjects.yellowapple);
			for (int i = 0; i < nr_woods; i++)
			{
				if (gameObjects.wood[i].position.y > HEIGHT) randomPosition(&gameObjects.wood[i]);
			}
			
			updateAllGameObjects(&gameObjects,&gameState);

			if (SDL_GetTicks() - lastTuicaSpawnTime >= tuicaSpawnInterval) {
				randomPosition(&gameObjects.tuica);
				lastTuicaSpawnTime = SDL_GetTicks();
			}
			
			if (SDL_GetTicks() - lastShieldSpawnTime >= shieldSpawnInterval) {
				printf("Shiled spawned\n");
				randomPosition(&gameObjects.shield);
				lastShieldSpawnTime = SDL_GetTicks();
				lastShieldActivation = SDL_GetTicks();
				
			}
			if (shieldEquiped &&(SDL_GetTicks()-lastShieldActivation>=shieldDuration))
			{
				shieldEquiped = false;
				printf("Shield despawned\n");
			}
			
			if (livesCount <= 0)
			{
				gameState = GAMEOVER;
				printf("%d\n", elapsedTime);
			}
			if (livesCount2 <= 0)
			{
				gameState = GAMEOVER;
				printf("%d\n", elapsedTime);
			}
			
			SDL_RenderClear(renderer);

			render_background(renderer,background);
			renderAllGameObjects(renderer, &gameObjects,&gameState);
			render_health(renderer, &gameObjects.lives);
			render_score(renderer);
			if(shieldEquiped)render_shield(renderer,&gameObjects.shieldRay, &gameObjects.pig);
			if (gameState == GAMECOOP)
			{
				render_health2(renderer, &gameObjects.lives);
				render_score2(renderer);
			}
			SDL_RenderPresent(renderer);
		}
		SDL_Delay(1000 / 60);
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(spriteSheet);
	TTF_Quit();
	SDL_Quit();

	return 0;
}
