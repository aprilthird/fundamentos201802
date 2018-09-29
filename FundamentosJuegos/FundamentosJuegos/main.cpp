
#include <SDL\SDL.h>
#include "MainGame.h"
#include "Engine.h"

int main(int argc, char** argv) {
	FD08::init();
	MainGame maingame;
	maingame.run();
	system("pause");
	return 0;
}