#pragma once
#include "Spaceship.h"
#include "Bullet.h"
#include <map>



/* 
		Game Class
*/
class Game
{
private:
	//Variables
	bool isGameOver;
	// Player 1
	Spaceship* player1;
	// Player 2
	Spaceship* player2;

	//SOUNDS
	SoundBuffer bgMusicBuffer;
	SoundBuffer fireBuffer;
	Music bgMusic;
	Sound fireSound;
	

	//GUI
	Font font;
	Font font2;
	Text playerOne;
	Text playerTwo;
	Text gameOverText;
	Text playerOneWin;
	Text playerTwoWin;
	Text playerTie;
	Text gameRestart;
	Text gameQuit;
	RectangleShape playerHpBar;
	RectangleShape playerHpBarBack;
	RectangleShape player2HpBar;
	RectangleShape player2HpBarBack;
	

	//World
	Texture worldBackgroundTex;
	Sprite worldBackground;


	//WIndows
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;
	bool isPaused;

	//Resources;
	map<string, Texture*> textures;
	vector<Bullet*> bullets;

	//Private functions
	void initVariables();
	void initWindow();
	void initPlayer1();
	void initPlayer2();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSoundBuffer();
	void initSound();
	void togglePause();

public:
	//Constructors & Destructors
	Game();
	virtual ~Game();

	//ACCESSORS
	const bool getWindowIsOpen() const;

	//Functions
	void pollEvents();
	void update();
	void updateBullets();
	void updateGUI();
	void updateWorld();
	void updateCombat();
	void updatePlayerState();
	void restart();
	void renderGUI();
	void renderWorld();
	void renderPlayerState();
	void render();
	void p1Movement();
	void p2Movement();
};

