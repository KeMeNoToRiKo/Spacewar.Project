#include "Game.h"


//Priv FUnctions
void Game::initVariables()
{
	this->window = nullptr;
	this->isPaused = false;
	this->isGameOver = false;
}

void Game::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1280;

	this->window = new RenderWindow(this->videoMode, "SpaceWar", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initPlayer1()
{
	this->player1 = new Spaceship(Vector2f(100.f, 300.f), Color::Blue);
}

void Game::initPlayer2()
{
	this->player2 = new Spaceship(Vector2f(1100.f, 300.f), Color::Red);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new Texture();
	this->textures["BULLET"]->loadFromFile("Texture/Bullet.png");
	if (!this->textures["BULLET"]->loadFromFile("Texture/Bullet.png")) {
		cerr << "Failed to load texture BULLET" << endl;
		// You might set a default texture or exit the game here
	}
}

void Game::initGUI()
{
	//Texts
	//FONT
	if (!font.loadFromFile("Font/Pixels.ttf")) {
		// Handle font loading failure
		std::cerr << "Failed to load font!" << endl;
	}
	if (!font2.loadFromFile("Font/dogica.ttf")) {
		// Handle font loading failure
		std::cerr << "Failed to load font!" << endl;
	}
	//TeXT
	gameOverText.setFont(font);
	gameOverText.setString("Game over");
	gameOverText.setCharacterSize(200);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition(325.f, 165.f);
	gameOverText.setOutlineColor(Color::Black);
	gameOverText.setOutlineThickness(2);
	gameOverText.setLetterSpacing(2);
	//p1
	playerOne.setFont(font);
	playerOne.setString("Player 1");
	playerOne.setCharacterSize(60);
	playerOne.setFillColor(sf::Color::White);
	playerOne.setPosition(20.f, -30.f);
	playerOne.setOutlineColor(Color::Black);
	playerOne.setOutlineThickness(2);
	playerOne.setLetterSpacing(2);
	//p2
	playerTwo.setFont(font);
	playerTwo.setString("Player 2");
	playerTwo.setCharacterSize(60);
	playerTwo.setFillColor(sf::Color::White);
	playerTwo.setPosition(1085.f, -30.f);
	playerTwo.setOutlineColor(Color::Black);
	playerTwo.setOutlineThickness(2);
	playerTwo.setLetterSpacing(2);
	//p1 win
	playerOneWin.setFont(font2);
	playerOneWin.setString("PLAYER 1 WINS!");
	playerOneWin.setCharacterSize(20);
	playerOneWin.setFillColor(Color::White);
	playerOneWin.setPosition(500.f, 390.f);
	playerOneWin.setOutlineColor(Color::Black);
	playerOneWin.setOutlineThickness(2);
	//p2 win
	playerTwoWin.setFont(font2);
	playerTwoWin.setString("Player 2 WINS!");
	playerTwoWin.setCharacterSize(20);
	playerTwoWin.setFillColor(Color::White);
	playerTwoWin.setPosition(500.f, 390.f);
	playerTwoWin.setOutlineColor(Color::Black);
	playerTwoWin.setOutlineThickness(2);
	//Tie
	playerTie.setFont(font2);
	playerTie.setString("TIE!");
	playerTie.setCharacterSize(20);
	playerTie.setFillColor(Color::White);
	playerTie.setPosition(615.f, 390.f);
	playerTie.setOutlineColor(Color::Black);
	playerTie.setOutlineThickness(2);

	//RESTART
	gameRestart.setFont(font2);
	gameRestart.setString("Restart");
	gameRestart.setCharacterSize(40);
	gameRestart.setFillColor(Color::White);
	gameRestart.setPosition(500.f, 450.f);
	gameRestart.setOutlineColor(Color::Black);
	gameRestart.setOutlineThickness(2);
	//QUIT
	gameQuit.setFont(font2);
	gameQuit.setString("Quit");
	gameQuit.setCharacterSize(40);
	gameQuit.setFillColor(Color::White);
	gameQuit.setPosition(565.f, 525.f);
	gameQuit.setOutlineColor(Color::Black);
	gameQuit.setOutlineThickness(2);

	//init player GUI
	this->playerHpBar.setSize(Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(Color::Red);
	this->playerHpBar.setPosition(Vector2f(20.f, 40.f));


	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(Color(25, 25, 25, 200));
	this->playerHpBarBack.setOutlineColor(Color::White);
	this->playerHpBarBack.setOutlineThickness(2);

	//p2
	//init player GUI
	this->player2HpBar.setSize(Vector2f(300.f, 25.f));
	this->player2HpBar.setFillColor(Color::Red);
	this->player2HpBar.setPosition(Vector2f(950.f, 40.f));


	this->player2HpBarBack = this->player2HpBar;
	this->player2HpBarBack.setFillColor(Color(25, 25, 25, 200));
	this->player2HpBarBack.setOutlineColor(Color::White);
	this->player2HpBarBack.setOutlineThickness(2);
	//this->player2HpBarBack.setPosition(Vector2f(800.f, 20.f));
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Texture/Background2.jpg") )
	{
		cerr << "ERROR Background Texture" << endl;
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSoundBuffer()
{
	if (!fireBuffer.loadFromFile("Sound/blaster.mp3")) {
		cerr << "ERROR SOUND PEW" << endl;
	}
	if (!bgMusic.openFromFile("Sound/BackgroundMusic.mp3")) {
		cerr << "ERROR SOUND Background Music" << endl;
	}
}

void Game::initSound()
{
	//Fire
	fireSound.setBuffer(fireBuffer);
	fireSound.setVolume(50); // Set volume level (0 to 100)
	fireSound.setPitch(1.5f); // Set pitch (1.0 is normal)
	fireSound.setLoop(false); // Set whether the sound should loop

	//Background Music
	//bgMusic.setBuffer(bgMusicBuffer);
	bgMusic.setVolume(10); // Set volume level (0 to 100)
	//bgMusic.setPitch(1.f); // Set pitch (1.0 is normal)
	bgMusic.setLoop(true); // Set whether the sound should loop
}

void Game::togglePause()
{
	isPaused = !isPaused;
}


//Constructors & Destructors

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initGUI();
	this->initPlayer1();
	this->initPlayer2();
	this->initTextures();
	this->initWorld();
	this->initSoundBuffer();
	this->initSound();
}

Game::~Game()
{
	delete this->window;
	delete this->player1;
	delete this->player2;

	//textures
	for (auto &i : this->textures) 
	{
		delete i.second;
	}

	//bullets
	for (auto *i : this->bullets)
	{
		delete i;
	}

	


}



//ACCESSORS
const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

//FUCNTIONS

void Game::update()
{
	
	this->updateWorld();
	this->pollEvents();
	this->updateBullets();
	this->updateCombat();
	this->updateCollision();
	this->updateGUI();
	this->player1->update();
	this->player2->update();
	this->updatePlayerState();
	


}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Remove non-visible bullets
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			//Test to ensure bullets are deleted
			//cout << this->bullets.size() << endl;
		}
		++counter;
	}
}

void Game::updateGUI()
{
	//update player GUI
	
	float hpPercent = static_cast<float>(this->player1->getHp()) / this->player1->getHpMax();
	this->playerHpBar.setSize(Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));

	float hpPercent2 = static_cast<float>(this->player2->getHp()) / this->player2->getHpMax();
	this->player2HpBar.setSize(Vector2f(300.f * hpPercent2, this->player2HpBar.getSize().y));
}

void Game::updateWorld()
{
	if (bgMusic.getStatus() != Sound::Playing) {
		bgMusic.play();
	}
}



void Game::updateCombat()
{
	// Loop through bullets
	for (size_t i = 0; i < this->bullets.size(); ++i) {
		auto* bullet = this->bullets[i];
		bullet->update();

		// Check collision with player1's bullets and player2
		if (this->player1->isColliding(bullet->getBounds()) && bullet->getOwnerID() != 1) {
			this->player1->loseHp(1);
			// Remove bullet
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin() + i);
			--i; // Move back one index since we erased an element
			continue; // Move to the next bullet
		}

		if (this->player2->isColliding(bullet->getBounds()) && bullet->getOwnerID() != 2) {
			this->player2->loseHp(1);
			// Remove bullet
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin() + i);
			--i; // Move back one index since we erased an element
			continue; // Move to the next bullet
		}


	}
}

void Game::updatePlayerState()
{
	this->player1->update();
	this->player2->update();
}

void Game::restart()
{
	this->player1->setPosition(Vector2f(100.f, 300.f)); // Set the initial position for player 1
	this->player2->setPosition(Vector2f(1100.f, 300.f)); // Set the initial position for player 2
	this->player1->setHp(10); // Reset player 1's health
	this->player2->setHp(10); // Reset player 2's health

	// Clear bullets
	for (auto* bullet : this->bullets) {
		delete bullet;
	}
	this->bullets.clear();

	// Reset any other game-specific variables or states

	// Restart background music if needed
	if (bgMusic.getStatus() != Sound::Playing) {
		bgMusic.play();
	}
}


void Game::renderGUI()
{
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
	this->window->draw(this->player2HpBarBack);
	this->window->draw(this->player2HpBar);
	this->window->draw(playerOne);
	this->window->draw(playerTwo);

	if (this->player1->isDestroyed() || this->player2->isDestroyed()) {
		this->window->draw(gameOverText);
		//this->window->draw(gameRestart);
		//this->window->draw(gameQuit);
		if (this->player1->isDestroyed() && this->player2->isDestroyed())
			this->window->draw(playerTie);
		if (this->player1->isDestroyed() && !this->player2->isDestroyed())
			this->window->draw(playerTwoWin);
		if (this->player2->isDestroyed() && !this->player1->isDestroyed())
			this->window->draw(playerOneWin);
	}
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::renderPlayerState()
{
	if (!this->player1->isDestroyed()) {
		this->player1->render(*this->window);
	}

	if (!this->player2->isDestroyed()) {
		this->player2->render(*this->window);
	}
}

	void Game::pollEvents()
	{
		while (this->window->pollEvent(this->ev))
		{
			switch (this->ev.type) 
			{
				case Event::Closed:
					this->window->close();
					break;
				case Event::KeyPressed:
					if (this->ev.key.code == Keyboard::Escape)
					this->window->close();
					break;
			}
		}
		
		// Move only if both players are not destroyed
		if (!this->player1->isDestroyed() && !this->player2->isDestroyed()) {
			p1Movement();
			p2Movement();
		}
		
			
	}

	void Game::render()
{
		this->window->clear();
		//World
		this->renderWorld();
		
		//draw
		// 
		// //bullets
		for (auto* bullet : this->bullets)
		{
			bullet->render(this->window);
		}
		//p1
		this->player1->render(*this->window);
		this->player2->render(*this->window);

		this->renderGUI();
		this->window->display();
}

	void Game::p1Movement()
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
			this->player1->rotateClockwise();
		if (Keyboard::isKeyPressed(Keyboard::D))
			this->player1->rotateCounterClockwise();
		if (Keyboard::isKeyPressed(Keyboard::W))
			this->player1->moveForward();
		if (Keyboard::isKeyPressed(Keyboard::S))
			this->player1->moveBackward();
		if (Keyboard::isKeyPressed(Keyboard::Space) && this->player1->canAttack()) {
			//SOUND
			fireSound.play();
			// Get the current rotation of player 1's spaceship
			float rotation = (this->player1->getSprite().getRotation() - 90);

			// Calculate direction based on spaceship's orientation
			float dirX = cos(rotation * (3.14159f / 180));
			float dirY = sin(rotation * (3.14159f / 180));

			// Create a new bullet with the updated direction
			this->bullets.push_back(new Bullet(this->textures["BULLET"],
				this->player1->getPos().x,
				this->player1->getPos().y,
				dirX,
				dirY,
				10.0f,
				1)); // Adjust movement speed as needed
		}
	}

	void Game::p2Movement()
	{
		if (Keyboard::isKeyPressed(Keyboard::Left))
			this->player2->rotateClockwise();
		if (Keyboard::isKeyPressed(Keyboard::Right))
			this->player2->rotateCounterClockwise();
		if (Keyboard::isKeyPressed(Keyboard::Up))
			this->player2->moveForward();
		if (Keyboard::isKeyPressed(Keyboard::Down))
			this->player2->moveBackward();
		

		if (Keyboard::isKeyPressed(Keyboard::Enter) && this->player2->canAttack()) {
			//SOUND
			fireSound.play();
			// Get the current rotation of player 1's spaceship
			float rotation = (this->player2->getSprite().getRotation() - 90);

			// Calculate direction based on spaceship's orientation
			float dirX = cos(rotation * (3.14159f / 180));
			float dirY = sin(rotation * (3.14159f / 180));

			// Create a new bullet with the updated direction
			this->bullets.push_back(new Bullet(this->textures["BULLET"],
				this->player2->getPos().x,
				this->player2->getPos().y,
				dirX,
				dirY,
				10.0f,
				2)); // Adjust movement speed as needed
		}
	}

