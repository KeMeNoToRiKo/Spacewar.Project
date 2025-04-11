#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Bullet
{
private:
	Sprite shape;
	Texture* texture;

	Vector2f direction;
	float movementSpeed;
	int ownerID;


public:
	Bullet();
	Bullet(Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, int owner);
	virtual ~Bullet();

	//accessor
	const FloatRect getBounds() const;
	int getOwnerID() const;

	void update();

	
	void render(RenderTarget* target);
};

