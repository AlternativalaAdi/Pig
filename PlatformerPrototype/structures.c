#include<stdio.h>
#include<stdbool.h>
#include<SDL.h>


int score = 0;
 int score2 = 0;
 int livesCount = 5;
 int livesCount2 = 5;
 int fallingSpeed = 10;
 bool pig2Initialized = false;
bool shieldEquiped = false;
const Uint32 tuicaSpawnInterval = 10000;
const Uint32 woodSpawnInterval = 15000;
const Uint32 shieldSpawnInterval = 10000;
const Uint32 shieldDuration = 5000;