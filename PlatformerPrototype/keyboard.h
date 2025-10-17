#ifndef KEYBOARD_H
#define KEYBOARD_H

void handleInput(GameObject* obj);
void handleInput2(GameObject* obj);
void handleMenu(SDL_Event* event, GameState* gameState, GameObjects* objects, GameObject* obj);
void handleSkins(SDL_Event* event, GameState* gameState, GameObjects* objects, GameObject* obj);

#endif
