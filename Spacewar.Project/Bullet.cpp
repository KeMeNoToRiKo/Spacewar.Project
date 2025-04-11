#include "Bullet.h"

//Constructor & Destructor

Bullet::Bullet() 
{

}
Bullet::Bullet(Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, int owner)
{
    
    if (texture == nullptr || !texture->loadFromFile("Texture/Bullet.png")) {
        // Handle the error, perhaps print an error message
        cerr << "Error loading texture for Bullet" << endl;
        // You might set a default texture or take appropriate action here
    }
    else {
        this->shape.setTexture(*texture);
        this->shape.setPosition(pos_x, pos_y);
        this->direction.x = dir_x;
        this->direction.y = dir_y;
        this->movementSpeed = movement_speed;
        this->ownerID = owner;

        this->shape.scale(0.025f, 0.025f);
        FloatRect bounds = shape.getLocalBounds();
        this->shape.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    }
    
}

Bullet::~Bullet()
{

}




const FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

int Bullet::getOwnerID() const
{
    return this->ownerID;
}

//Function
void Bullet::update()
{
	//Movement
    this->shape.move(this->movementSpeed * this->direction.x, this->movementSpeed * this->direction.y);
    // Calculate rotation angle based on direction
    float angle = atan2(this->direction.y, this->direction.x); // Calculate angle in radians

    // Convert angle from radians to degrees and rotate once more clockwise
    float rotationAngle = (angle * (180.0f / 3.14159f)) + 90.0f; // Add 90 degrees for additional clockwise rotation

    // Set the rotation of the bullet sprite
    this->shape.setRotation(rotationAngle);
}

void Bullet::render(RenderTarget* target)
{
	target->draw(this->shape);
}
