#include <enemy.hpp>

Enemy::Enemy()
{

}
Enemy::Enemy(sf::Vector2f sP, sf::Texture &texture, sf::Font &font, sf::Vector2f tP, float s, std::string n)
{
    speed=s;
    targetPos=tP;
    startPos=sP;
    name=n;
    rotationAngle=0.f;
    angle=atan2(startPos.y-targetPos.y, targetPos.x-startPos.x);
    sprite.setTexture(texture);
    sprite.setPosition(startPos);
    text.setFont (font);
    text.setPosition (sf::Vector2f(startPos.x,startPos.y+20));
    text.setString(name);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(12);
}
Enemy::~Enemy()
{

}
float Enemy::getAngle()
{
    return angle;
}
std::string Enemy::getName()
{
    return name;
}
sf::Sprite Enemy::getSprite()
{
    return sprite;
}
sf::Sprite* Enemy::getSpritePointer()
{
    return &sprite;
}
sf::Text Enemy::getTextbox()
{
    return text;
}
void Enemy::setPos(sf::Vector2f sP)
{
    startPos=sP;
}bool f=true;
void Enemy::movePos(sf::Vector2f sP)
{
    startPos+=sP;
}

void Enemy::setName (std::string n)
{
    name=n;
    text.setString(name);
}
void Enemy::setSpeed(float s)
{
    speed=s;
}
void Enemy::update(float time)
{
    sprite.move (sf::Vector2f (std::cos(angle)*time*speed, std::sin(angle)*time*speed*(-1)));
    text.move (sf::Vector2f (std::cos(angle)*time*speed, std::sin(angle)*time*speed*(-1)));
    //if (rotationAngle!=0.f) sprite.rotate(rotationAngle*time);
}
void Enemy::setRotation(float a){
    rotationAngle=a;
}
bool Enemy::checkCollision(sf::Sprite *t)
{
    bool f=false;
    if (sprite.getGlobalBounds().intersects(t->getGlobalBounds())) f=true;
    return f;
}

bool Enemy::checkString(std::string s)
{
    bool f=false;
    if (s==name)
        f=true;
    return f;
}

sf::Vector2f Enemy::getPos(){
    return sprite.getPosition();
}
