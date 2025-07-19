#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>
#include<SDL_image.h>
#include<time.h>
#include<SDL_ttf.h>
#include "srcRects.h"
#include "structures.h"

SDL_Texture* background = NULL;


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
	for (int i = 0; i < nr_woods; i++)
	{
		updateGameObject(&gameObjects->wood[i]);
	}

	if (*gameState == GAMECOOP)
	{
		updateGameObject(&gameObjects->pig2);
	}
}

void renderGameObject(SDL_Renderer* renderer, GameObject* obj) {
	if (obj->sprite.texture != NULL) {
		SDL_Rect destRect = { obj->position.x, obj->position.y, obj->sprite.width, obj->sprite.height };
		SDL_RenderCopy(renderer, obj->sprite.texture, &obj->sourceRect, &destRect);
	}
}

void renderBackground(SDL_Renderer* renderer)
{
	SDL_Rect destRect = { 0,0,WIDTH,HEIGHT };
	SDL_RenderCopy(renderer, background, NULL, &destRect);
}

void renderAllGameObjects(SDL_Renderer* renderer, GameObjects* gameObjects, GameState* gameState) {
	renderGameObject(renderer, &gameObjects->pig);
	renderGameObject(renderer, &gameObjects->banana);
	renderGameObject(renderer, &gameObjects->apple);
	renderGameObject(renderer, &gameObjects->yellowapple);
	renderGameObject(renderer, &gameObjects->greenapple);
	renderGameObject(renderer, &gameObjects->tuica);
	renderGameObject(renderer, &gameObjects->shield);
	for (int i = 0; i < nr_woods; i++)
	{
		renderGameObject(renderer,&gameObjects->wood[i]);
	}

	if (*gameState == GAMECOOP)
	{
		renderGameObject(renderer, &gameObjects->pig2);
	}
	
}

void collisions(GameObjects* gameObjects, GameState* gameState)
{


	for (int i = 0; i < nr_woods; i++)
	{
		if (checkCollision(&gameObjects->pig, &gameObjects->wood[i]))
		{
			livesCount--;
			randomPosition(&gameObjects->wood[i]);
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

	if (*gameState == GAMECOOP)
	{

		for (int i = 0; i < nr_woods; i++)
		{
			if (checkCollision(&gameObjects->pig2, &gameObjects->wood[i]))
			{
				livesCount2--;
				randomPosition(&gameObjects->wood[i]);
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
			if (livesCount < 5)
			{
				livesCount2++;
			}
			gameObjects->tuica.position.x = -100;
			gameObjects->tuica.position.y = -100;
		}
	}
	if (livesCount <= 0 || livesCount2 <= 0) {
		*gameState = GAMEOVER; // Transition to GAMEOVER if any player's lives are 0
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

void displayeSkins(SDL_Renderer* renderer, GameObject* obj1, GameObject* obj2, GameObject* obj3, GameObject* obj4)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Clear screen with black
	SDL_RenderClear(renderer);

	SDL_Rect destRect = { 100, 100, 100, 100 };
	SDL_RenderCopy(renderer, obj1->sprite.texture, &obj1->sourceRect, &destRect);
	SDL_Rect destRect2 = { 100, 250, 100, 100 };
	SDL_RenderCopy(renderer, obj2->sprite.texture, &obj2->sourceRect, &destRect2);
	SDL_Rect destRect3 = { 100, 400, 100, 100 };
	SDL_RenderCopy(renderer, obj3->sprite.texture, &obj3->sourceRect, &destRect3);
	SDL_Rect destRect4 = { 100, 550, 100, 100 };
	SDL_RenderCopy(renderer, obj4->sprite.texture, &obj4->sourceRect, &destRect4);

	

	SDL_RenderPresent(renderer);
}

void handleSkins(SDL_Event* event, GameState* gameState, GameObjects* objects, GameObject* obj)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			int mouseX = event->button.x;
			int mouseY = event->button.y;
			printf("Mouse clicked at: (%d, %d)\n", mouseX, mouseY); // Debugging line
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

void displayMenu(SDL_Renderer* renderer, GameObject* obj)
{
	SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);  // Clear screen with black
	SDL_RenderClear(renderer);

	
	if (obj->sprite.texture != NULL) {
		SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);  
		SDL_Rect rect1 = { 200, 150, 200, 150 };
		SDL_Rect rect2 = { 200, 500, 200, 150 };
		SDL_Rect rect3 = { 400,700,50,50 };
		SDL_RenderFillRect(renderer, &rect1);
		SDL_RenderFillRect(renderer, &rect2);

		SDL_Rect destRect = { 250, 170, 100, 100 };
		SDL_RenderCopy(renderer, obj->sprite.texture, &obj->sourceRect, &destRect);

		for (int i = 1; i <= 2; i++)
		{
			SDL_Rect destRect = { 100 + 100*i, 500, 100, 100 };
			SDL_RenderCopy(renderer, obj->sprite.texture, &obj->sourceRect, &destRect);
		}

	}
	else {
		printf("Lives texture not loaded properly!\n");
	}

	SDL_RenderPresent(renderer);
}



void handleMenu(SDL_Event* event, GameState* gameState, GameObjects* objects,GameObject* obj)
{
	
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			int mouseX = event->button.x;
			int mouseY = event->button.y;
			printf("Mouse clicked at: (%d, %d)\n", mouseX, mouseY); // Debugging line
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


void handleInput(GameObject* obj) {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);  // Get the state of all keys

	// Check for left arrow key (SDL_SCANCODE_LEFT)
	if (keystate[SDL_SCANCODE_A]&&obj->position.x>0) {
		obj->physics.velocityX = -1; // Move left
		obj->sourceRect.y = 64;
	}
	// Check for right arrow key (SDL_SCANCODE_RIGHT)
	else if (keystate[SDL_SCANCODE_D]&&obj->position.x<500) {
		obj->physics.velocityX = 1; // Move right
		obj->sourceRect.y = 0;
	}
	
	else {
		obj->physics.velocityX = 0; // Stop moving if no key is pressed
	}
}

void handleInput2(GameObject* obj) {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);  // Get the state of all keys

	// Check for left arrow key (SDL_SCANCODE_LEFT)
	if (keystate[SDL_SCANCODE_LEFT] && obj->position.x > 0) {
		obj->physics.velocityX = -1; // Move left
		obj->sourceRect.y = 64;
	}
	// Check for right arrow key (SDL_SCANCODE_RIGHT)
	else if (keystate[SDL_SCANCODE_RIGHT] && obj->position.x < 500) {
		obj->physics.velocityX = 1; // Move right
		obj->sourceRect.y = 0;
	}
	else {
		obj->physics.velocityX = 0; // Stop moving if no key is pressed
	}
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filePath) {
	SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
	if (texture == NULL) {
		printf("Unable to load texture: %s\n", IMG_GetError());
	}
	return texture;
}

void render_score(SDL_Renderer* renderer)
{
	TTF_Font* font = TTF_OpenFont("atop.ttf", 70);  // Adjust font path and size
	if (!font) {
		printf("Font loading error: %s\n", TTF_GetError());
		return;
	}

	SDL_Color textColor = { 255,255,0,255 };
	char scoreStr[10];
	sprintf(scoreStr, "%d", score);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreStr, textColor);
	if (!textSurface) {
		printf("Text surface creation error: %s\n", TTF_GetError());
		TTF_CloseFont(font);
		return;
	}
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!textTexture) {
		printf("Text texture creation error: %s\n", SDL_GetError());
		SDL_FreeSurface(textSurface);
		TTF_CloseFont(font);
		return;
	}

	SDL_Rect textRect = { 50, 50, 50, 80 };


	// Render the texture
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	// Free resources
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);

}
void render_score2(SDL_Renderer* renderer)
{
	TTF_Font* font2 = TTF_OpenFont("atop.ttf", 70);  // Adjust font path and size
	if (!font2) {
		printf("Font loading error: %s\n", TTF_GetError());
		return;
	}

	SDL_Color textColor2 = { 255,255,0,255 };
	char scoreStr2[10];
	sprintf(scoreStr2, "%d", score2);
	SDL_Surface* textSurface2 = TTF_RenderText_Solid(font2, scoreStr2, textColor2);
	if (!textSurface2) {
		printf("Text surface creation error: %s\n", TTF_GetError());
		TTF_CloseFont(font2);
		return;
	}
	SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
	if (!textTexture2) {
		printf("Text texture creation error: %s\n", SDL_GetError());
		SDL_FreeSurface(textSurface2);
		TTF_CloseFont(font2);
		return;
	}

	SDL_Rect textRect2 = { 450, 50, 50, 80 };

	// Render the texture
	SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

	// Free resources
	SDL_DestroyTexture(textTexture2);
	SDL_FreeSurface(textSurface2);
	TTF_CloseFont(font2);

}


void render_health(SDL_Renderer* renderer, GameObject* obj)
{
	for (int i = 1; i <= livesCount; i++) {
		SDL_Rect destRect = { obj->position.x+i*30, obj->position.y, obj->sprite.width, obj->sprite.height };
		SDL_RenderCopy(renderer, obj->sprite.texture, &obj->sourceRect, &destRect);
	}
}

void render_health2(SDL_Renderer* renderer, GameObject* obj)
{
	for (int i = 1; i <= livesCount2; i++) {
		SDL_Rect destRect = { obj->position.x+400 + i * 30, obj->position.y, obj->sprite.width, obj->sprite.height };
		SDL_RenderCopy(renderer, obj->sprite.texture, &obj->sourceRect, &destRect);
	}
}


int initTTF()
{
	if (TTF_Init() == -1)
	{
		printf("ttf error:%s\n", TTF_GetError());
		return -1;
	}
	return 0;
}


int main()
{
	
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
	const Uint32 shieldDuration = 10000;

	Uint32 lastTuicaSpawnTime = startTime;
	Uint32 lastShieldSpawnTime = startTime;
	Uint32 lastShieldActivation = startTime;
	//Uint32 lastWoodSpawnTime = startTime;

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
		

		if (gameState == GAME)
		{
			collisions(&gameObjects,&gameState);
			handleInput(&gameObjects.pig);

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
			
			/*
			if (SDL_GetTicks() - lastShieldSpawnTime >= shieldSpawnInterval) {
				printf("Shiled spawned\n");
				randomPosition(&gameObjects.shield);
				lastShieldSpawnTime = SDL_GetTicks();
				lastShieldActivation = SDL_GetTicks();
				
			}
			if (shield==1 &&(SDL_GetTicks()-lastShieldActivation>=shieldDuration))
			{
				shield = 0;
				printf("Shield despawned\n");
			}
			*/
			
			if (livesCount <= 0)
			{
				gameState = GAMEOVER;
				printf("%d\n", elapsedTime);
			}
			
			SDL_RenderClear(renderer);

			
			renderAllGameObjects(renderer, &gameObjects,&gameState);
			render_health(renderer, &gameObjects.lives);
			render_score(renderer);


			SDL_RenderPresent(renderer);
		}

		if (gameState == GAMECOOP)
		{

			collisions(&gameObjects,&gameState);
			handleInput(&gameObjects.pig);
			handleInput2(&gameObjects.pig2);

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
				printf("Tuica spawned\n");
				lastTuicaSpawnTime = SDL_GetTicks();
			}

			if (livesCount <= 0 || livesCount2<=0)
			{
				gameState = GAMEOVER;
				printf("%d\n", elapsedTime);
			}
			
			SDL_RenderClear(renderer);

			renderAllGameObjects(renderer, &gameObjects,&gameState);
			render_health(renderer, &gameObjects.lives);
			render_health2(renderer, &gameObjects.lives);
			render_score(renderer);
			render_score2(renderer);

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
