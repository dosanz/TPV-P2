#pragma once
#include <iostream>
#include <fstream>
#include <new>
#include <string>
#include <list>
#include "checkML.h"
#include "Utilities.h"
#include "Texture.h"
#include "Ball.h"
#include "BlocksMap.h"
#include "Paddle.h"
#include "Wall.h"
#include "InfoBar.h"
#include "PlayerDataManager.h"
#include "ArkanoidObject.h"
#include "Reward.h"

typedef list<ArkanoidObject*>::iterator itArkObjList;
class Game {
// --------------------- variables------------------------------------------------------
private: 
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	list<ArkanoidObject*> gameObjects;
	itArkObjList firstReward;
	int numRewards = 0;

	Wall* walls[NUM_WALLS];
	Texture* textures[NUM_TEXTURES]; 
	BlocksMap* map = nullptr;
	Ball* ball = nullptr;
	Paddle* paddle = nullptr;
	InfoBar* infoBar = nullptr;
	// PlayerDataManager* playerInfoManager = nullptr;

	bool end = false;
	bool gameOver = false;
	bool levelClear = false;

	uint lives = 3;
	uint currentLevel = 1;
	uint seconds = 0, minutes = 0;
	uint lastTicks = 0, currentTicks = 0;
	uint score = 0;

	uint cellHeight = 20, cellWidth = 60;
	uint mapHeight, mapWidth;

// ---------------------- methods ------------------------------------------------------
public:
	Game ();
	~Game ();

	// getter functions
	uint getMapWidth () const { return mapWidth; }
	uint getMapHeight () const { return mapHeight; }
	Texture* getTexture (TextureNames textureName) const { return textures[textureName]; }
	SDL_Renderer* getRenderer () const { return renderer; }

	// setter functions
	void setLevelClear () { levelClear = true; }
	void setGameOver () { gameOver = true; }
	void increaseLives () { lives++; }

	// takes in the map dimensions calculated in BlocksMap::load() and scales the walls and window to fit accordingly
	void scaleObjects (uint newMapWidth, uint newMapHeight);
	// main game loop, runs until a quit event is detected
	void run ();
	// returns wether the ball collides with an object or not, and if it does, returns the collision vector
	bool collides (SDL_Rect ballRect, Vector2D ballSpeed, Vector2D &collVector);
	

private:
	// initializes SDL 
	void iniSDL ();
	// initializes all textures
	void iniTextures ();
	// gives the ball and paddle their initial positions, calculated from the map dimensions
	void positionObjects ();

	// renders the walls
	void renderBackground () const;
	// polls events, and checks for quit events. also calls Paddle::handleEvents(SDL_Event &e), which handles keyboard events
	void handleEvents ();
	// if the control bool levelClear is true, deletes the old BlocksMap, creates a new one and reads all the corresponding info
	void handleLevelUp ();
	// keeps track of the time elapsed since starting a level
	void handleTime ();
	// calls the respective render methods from ball, paddle and map and then draws 
	void render () const;
	// calls the update methods from ball and paddle
	void update ();
	
	// destroys both renderer and window and quits SDL
	void quitSDL ();

	void saveToFile(string code);
};

