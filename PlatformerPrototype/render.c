#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<SDL.h>
#include<SDL_ttf.h>
#include "structures.h"
#include "ttf.h"
#include "collisions.h"


void displayeSkins(SDL_Renderer* renderer, GameObject* obj1, GameObject* obj2, GameObject* obj3, GameObject* obj4)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
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

void renderGameObject(SDL_Renderer* renderer, GameObject* obj) {
	if (obj->sprite.texture != NULL) {
		SDL_Rect destRect = { obj->position.x, obj->position.y, obj->sprite.width, obj->sprite.height };
		SDL_RenderCopy(renderer, obj->sprite.texture, &obj->sourceRect, &destRect);
	}
}

void renderBackground(SDL_Renderer* renderer,SDL_Texture* background)
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
	if(!shieldEquiped)renderGameObject(renderer, &gameObjects->shield);

	for (int i = 0; i < nr_woods; i++)
	{
		renderGameObject(renderer, &gameObjects->wood[i]);
	}

	if (*gameState == GAMECOOP)
	{
		renderGameObject(renderer, &gameObjects->pig2);
	}

}

void displayMenu(SDL_Renderer* renderer, GameObject* obj)
{
	SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
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
			SDL_Rect destRect = { 100 + 100 * i, 500, 100, 100 };
			SDL_RenderCopy(renderer, obj->sprite.texture, &obj->sourceRect, &destRect);
		}

	}
	else {
		printf("Lives texture not loaded properly!\n");
	}

	SDL_RenderPresent(renderer);
}

void render_score(SDL_Renderer* renderer)
{
	TTF_Font* font = TTF_OpenFont("atop.ttf", 70);
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



	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);


	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);

}
void render_score2(SDL_Renderer* renderer)
{
	TTF_Font* font2 = TTF_OpenFont("atop.ttf", 70);
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


	SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);


	SDL_DestroyTexture(textTexture2);
	SDL_FreeSurface(textSurface2);
	TTF_CloseFont(font2);

}


void render_health(SDL_Renderer* renderer, GameObject* obj)
{
	for (int i = 1; i <= livesCount; i++) {
		SDL_Rect destRect = { obj->position.x + i * 30, obj->position.y, obj->sprite.width, obj->sprite.height };
		SDL_RenderCopy(renderer, obj->sprite.texture, &obj->sourceRect, &destRect);
	}
}

void render_health2(SDL_Renderer* renderer, GameObject* obj)
{
	for (int i = 1; i <= livesCount2; i++) {
		SDL_Rect destRect = { obj->position.x + 400 + i * 30, obj->position.y, obj->sprite.width, obj->sprite.height };
		SDL_RenderCopy(renderer, obj->sprite.texture, &obj->sourceRect, &destRect);
	}
}

void render_shield(SDL_Renderer* renderer, GameObject* obj1, GameObject* obj2)
{
	SDL_SetTextureBlendMode(obj1->sprite.texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(obj1->sprite.texture, 100);
	SDL_Rect destRect = { obj2->position.x - 60, obj2->position.y - 60,obj2->sprite.width * 2, obj2->sprite.height * 2 };
	SDL_RenderCopy(renderer, obj1->sprite.texture, &obj1->sourceRect, &destRect);
	SDL_SetTextureAlphaMod(obj1->sprite.texture, 255);

}

void render_background(SDL_Renderer* renderer, SDL_Rect* sourceRect)
{
	SDL_Rect destRect = { 0,0,WIDTH,HEIGHT };
	SDL_RenderCopy(renderer, sourceRect, 0, &destRect);
}
