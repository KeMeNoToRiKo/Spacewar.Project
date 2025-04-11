#include "Spaceship.h"

void Spaceship::initVariables()
{
	this->attackCooldownMax = 20.f;
	this->attackCooldown = this->attackCooldownMax;
	this->Speed = 2.f;
	this->rotateSpeed = 2.5f;

	this->hpMax = 10;
	this->hp = this->hpMax;

	this->destroying = false;
	this->destroyed = false;
	this->explosionSoundPlayed = false;
}

void Spaceship::initTexture()
{
	if (!this->texture.loadFromFile("Texture/Spaceship.png"))
	{
		cerr << "ERROR: Spaceship sprite" << endl;
	}
}

void Spaceship::initTextureDestroy()
{
	if (!this->destructionTexture.loadFromFile("Texture/Explode.png"))
	{
		cerr << "ERROR EXPLODE SPRITE" << endl;
	}
}

void Spaceship::initSprite(Color shipColor)
{
	this->sprite.setTexture(this->texture);
	///this->sprite.scale(0.5f, 0.5f);
	//Orig
	this->sprite.scale(0.25f, 0.25f);

	// Define the target and replacement colors
	Color targetColor(246, 172, 109); // Replace blue color (adjust as needed)
	Color replacementColor(shipColor); // Replace with green color (adjust as needed)

	// Replace the specific color in the sprite's texture
	Image spriteImage = this->texture.copyToImage();
	replaceColor(spriteImage, targetColor, replacementColor);
	this->texture.loadFromImage(spriteImage);

	sf::FloatRect bounds = this->sprite.getLocalBounds();
	this->sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

}



void Spaceship::initSpriteDestroy()
{
	this->destructionSprite.setTexture(this->destructionTexture);
	this->currentFrame = IntRect(0, -5, 100, 100);
	//this->destructionSprite.setScale(1.5f, 1.5f);
	this->destructionSprite.setTextureRect(IntRect(this->currentFrame));
	//this->destructionSprite.setTexture(this->destructionTexture);
	FloatRect bounds = destructionSprite.getLocalBounds();
	this->destructionSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f); // Match with spaceship origin


}

void Spaceship::PosInit(Vector2f startPos)
{
	this->position = startPos;
	this->sprite.setPosition(this->position);
}

void Spaceship::initPhysics()
{
	this->velocityMax = 3.f;
	this->velocityMin = 0.5f;
	this->acceleration = 1.f;
	this->deceleration = 0.98f;
}

void Spaceship::initAnimation()
{
	this->destructionClock.restart();
}

void Spaceship::initSoundBuffer()
{
	if (!explodeBuffer.loadFromFile("Sound/Explode.mp3")) {
		cerr << "ERROR EXPLODE SOUND" << endl;
	}
}

void Spaceship::initSound()
{
	explodeSound.setBuffer(explodeBuffer);

}

//Constructor & Destructor

Spaceship::Spaceship(Vector2f startPos, Color shipColor)
{
	this->initVariables();
	this->initTexture();
	this->initTextureDestroy();
	this->initSprite(shipColor);
	this->initSpriteDestroy();
	this->PosInit(startPos);
	this->initPhysics();
	this->initAnimation();
	this->initSoundBuffer();
	this->initSound();

	//this->sprite.setColor(shipColor);
}

Spaceship::~Spaceship()
{
}
const Vector2f& Spaceship::getPos() const
{
	return this->sprite.getPosition();
}
Sprite& Spaceship::getSprite()
{
	return sprite;
}
float Spaceship::getRotation() const
{
	return rotation;
}
const FloatRect Spaceship::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
const int Spaceship::getHp() const
{
	return this->hp;
}
const int Spaceship::getHpMax() const
{
	return this->hpMax;
}
bool Spaceship::getActive()
{
	return getActive();
}
bool Spaceship::isDestroyed()
{
	if (this->hp <= 0)
	{
		return true; 
	}
	else
	{
		return false;
	}
}
//modifiers
void Spaceship::setPosition(const Vector2f pos)
{
	this->sprite.setPosition(pos);
}
void Spaceship::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}
void Spaceship::setHp(const int hp)
{
	this->hp = hp;
}
void Spaceship::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}
void Spaceship::setActive(bool newActive)
{
	active = newActive;
}
void Spaceship::replaceColor(Image& image, const Color& targetColor, const Color& replacementColor)
{
	unsigned int width = image.getSize().x;
	unsigned int height = image.getSize().y;

	for (unsigned int y = 0; y < height; ++y) {
		for (unsigned int x = 0; x < width; ++x) {
			if (image.getPixel(x, y) == targetColor) {
				image.setPixel(x, y, replacementColor);
			}
		}
	}
}
//move
void Spaceship::rotateClockwise()
{
	if (!this->isDestroyed())
		this->sprite.rotate(-rotateSpeed);
}
void Spaceship::rotateCounterClockwise()
{
	if (!this->isDestroyed())
		this->sprite.rotate(rotateSpeed);
}
void Spaceship::moveForward()
{
	//acceleration
	if (!this->isDestroyed())
	{
		this->velocity.x += this->acceleration;
		this->velocity.y += this->acceleration;
		//velocityLimit
		if (abs(this->velocity.x) > this->velocityMax)
		{
			this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
		}

		float angle = sprite.getRotation() * (3.14159f / 180); // Convert to radians
		float moveX = velocity.x * sin(angle);
		float moveY = -velocity.x * cos(angle);
		this->sprite.move(moveX, moveY);
	}
}

void Spaceship::moveBackward()
{
	if (!this->isDestroyed())
	{
		float angle = sprite.getRotation() * (3.14159f / 180); // Convert to radians
		float moveX = -Speed * sin(angle);
		float moveY = Speed * cos(angle);
		this->sprite.move(moveX, moveY);
	}
}

const bool Spaceship::canAttack()
{
	if ((this->attackCooldown >= this->attackCooldownMax) && !this->isDestroyed())
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

bool Spaceship::isColliding(const FloatRect& otherBounds) const
{
	return this->sprite.getGlobalBounds().intersects(otherBounds);
}

void Spaceship::destroy()
{
	this->destroyed = true;
}

//FUNCTION

void Spaceship::update()
{
	this->updateAttack();
	this->updatePhysics();
	this->updateAnimation();
	this->updateDestruction();
	
}

void Spaceship::updatePhysics()
{
	// Calculate the angle in radians
	float angle = sprite.getRotation() * (3.14159f / 180);

	// Decelerate the velocity
	this->velocity *= this->deceleration;

	// Limit deceleration
	if (abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	// Calculate movement based on the updated velocity and angle
	float moveX = this->velocity.x * sin(angle);
	float moveY = -this->velocity.x * cos(angle);

	// Move the sprite
	this->sprite.move(moveX, moveY);
}

void Spaceship::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Spaceship::updateAnimation()
{
	if (this->destroying) {
		if (this->destructionClock.getElapsedTime().asSeconds() >= 0.025f) {
			this->currentFrame.left += 100; // Update frame width (899 / 9)
			// Update 'totalWidthOfSpritesheet' and 'totalHeightOfSpritesheet' to the entire dimensions of your sprite sheet
			const int totalWidthOfSpritesheet = 899;
			const int totalHeightOfSpritesheet = 857;
			const float heightIncrement = 100.f;

			if (this->currentFrame.left >= totalWidthOfSpritesheet) 
			{
				this->currentFrame.left = 0;
				//this->destroying = false;

				this->currentFrame.top += heightIncrement; // Update frame height (857 / 8)
				
				if (this->currentFrame.top >= totalHeightOfSpritesheet) {
					//this->currentFrame.top = 0;
					this->destroying = false; // End of destruction animation
				}
			}

			this->destructionSprite.setTextureRect(this->currentFrame);
			this->destructionClock.restart();
		}
	}
}

void Spaceship::updateDestruction()
{
	if (this->isDestroyed() == true && !explosionSoundPlayed) {
		explodeSound.play();
		this->destroying = true;
		//cout << "SOUND" << endl; TEST IF SOUND IS PLAYED
		explosionSoundPlayed = true;
		//this->initAnimation();
	}
}

void Spaceship::render(RenderTarget& target)
{
	if (this->isDestroyed()) {
		this->destructionSprite.setPosition(this->getPosition());
		target.draw(this->destructionSprite);
	}
	else {
		target.draw(this->sprite);
	}

}

void Spaceship::renderDestruction()
{
	
}

Vector2f Spaceship::getPosition() const
{
	return this->sprite.getPosition();
}

