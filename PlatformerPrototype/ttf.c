#include<stdio.h>
#include<SDL.h>
#include<SDL_ttf.h>

int initTTF()
{
	if (TTF_Init() == -1)
	{
		printf("ttf error:%s\n", TTF_GetError());
		return -1;
	}
	return 0;
}