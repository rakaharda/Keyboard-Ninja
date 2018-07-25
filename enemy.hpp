#ifndef ENEMYHPP
#define ENEMYHPP
#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Enemy : public sf::Drawable
{
private:
    sf::Vector2f startPos;
    float angle;
    bool isMoving;
    std::string name;
    sf::Sprite sprite;
    sf::Vector2f targetPos;
    sf::Text text;
    float speed;
    float rotationAngle;
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Enemy();
    Enemy(sf::Vector2f sP, sf::Texture &texture, sf::Font &font, sf::Vector2f tP, float s=50.f, std::string n=" ");
    ~Enemy();
    sf::Vector2f getPos();
    float getPosY();
    float getAngle();
    sf::Sprite getSprite();
    sf::Sprite* getSpritePointer();
    sf::Text getTextbox();
    std::string getName();
    void setPos(sf::Vector2f sP);
    void movePos(sf::Vector2f sP);
    void setName(std::string n);
    void setSpeed (float s);
    void update(float time);
    void setRotation(float a);
    bool checkCollision(sf::Sprite *t);
    bool checkString(std::string s);
};
#endif // ENEMYHPP
