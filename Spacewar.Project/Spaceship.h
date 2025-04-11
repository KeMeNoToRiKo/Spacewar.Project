#pragma once
#include "Bullet.h"
#include <SFML/Graphics/Rect.hpp>

class Spaceship
{
private:
    Sprite destructionSprite;
    Sprite sprite;
    Texture texture;
    Texture destructionTexture;
    SoundBuffer explodeBuffer;
    Sound explodeSound;

    //ANIMATION
    IntRect currentFrame;
    
    Vector2i destructionFrameSize;
    Clock destructionClock;
    float destructionFrameDuration;
    bool destroying;
    bool explosionSoundPlayed;

    //Atrributes
    int hp;
    int hpMax;
    bool destroyed;
    //Locomotor

    float rotateSpeed;
    float rotation;
    float Speed;
    float attackCooldown;
    float attackCooldownMax;
    Vector2f position;

    //Physics
    Vector2f velocity;
    float velocityMax;
    float velocityMin;
    float acceleration;
    float deceleration;
    bool active;

    //private functions
    //inits
    void initVariables();
    void initTexture();
    void initSprite(Color shipColor);
    void initTextureDestroy();
    void initSpriteDestroy();
    void PosInit(Vector2f startPos);
    void initPhysics();
    void initAnimation();
    void initSoundBuffer();
    void initSound();

public:
    Spaceship(Vector2f startPos, Color shipColor);
    virtual ~Spaceship();

    //Accessor
    const Vector2f& getPos() const;
    Sprite& getSprite();
    float getRotation() const;
    const FloatRect getBounds() const;
    const int getHp() const;
    const int getHpMax() const;
    bool getActive();
    bool isDestroyed();

    //modifier
    void setPosition(const Vector2f pos);
    void setPosition(const float x, const float y);
    void setHp(const int hp);
    void loseHp(const int value);
    void setActive(bool newActive);
    void replaceColor(Image& image, const Color& targetColor, const Color& replacementColor);

    //FUNCTION
    void rotateClockwise();
    void rotateCounterClockwise();
    void moveForward();
    void moveBackward();
    const bool canAttack();
    bool isColliding (const FloatRect& otherBounds) const;
    void destroy();

    void update();
    
    void updatePhysics();
    void updateAttack();
    void updateAnimation();
    void updateDestruction();
    void render(RenderTarget& target);
    void renderDestruction();

    
   
    //POS GETTER
    Vector2f getPosition() const;

};

