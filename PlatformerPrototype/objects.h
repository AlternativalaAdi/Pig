#ifndef OBJECTS_H
#define OBJECTS_H

void initGameObject(GameObject* obj, int x, int y, int width, int height, int velocityX, int velocityY, int speed, SDL_Rect sourceRect);
void updateGameObject(GameObject* obj);
void randomPosition(GameObject* obj);
void updateAllGameObjects(GameObjects* gameObjects, GameState* gameState);

#endif