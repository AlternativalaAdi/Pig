#ifndef RENDER_H
#define RENDER_H
#include<SDL.h>

void displayeSkins(SDL_Renderer* renderer, GameObject* obj1, GameObject* obj2, GameObject* obj3, GameObject* obj4);
void renderGameObject(SDL_Renderer* renderer, GameObject* obj);
void renderBackground(SDL_Renderer* renderer,SDL_Texture* background);
void renderAllGameObjects(SDL_Renderer* renderer, GameObjects* gameObjects, GameState* gameState);
void displayMenu(SDL_Renderer* renderer, GameObject* obj);
void render_score(SDL_Renderer* renderer);
void render_score2(SDL_Renderer* renderer);
void render_health(SDL_Renderer* renderer, GameObject* obj);
void render_health2(SDL_Renderer* renderer, GameObject* obj);
void render_shield(SDL_Renderer* renderer, GameObject* obj1, GameObject* obj2);
void render_background(SDL_Renderer* renderer, SDL_Rect* sourceRect);



#endif
