#pragma once

enum ScreenState {
	NONE,
	EXIT_APPLICATION,
	CHANGE_NEXT,
	CHANGE_PREVIOUS
};

class Game;
class IGameScreen {
protected:
	int _screenIndex = 1;
	ScreenState _currentState = ScreenState::NONE;
	Game* _game = nullptr;
public:
	virtual void checkInput() = 0;
	virtual void initSystem() = 0;
	virtual void build() = 0;
	virtual void destroy() = 0;
	virtual void onExit() = 0;
	virtual void onEntry() = 0;
	virtual void draw() = 0; 
	virtual void update() = 0;
	virtual void getNextScreen() = 0; 
	virtual void getPreviousScreen() = 0;
};