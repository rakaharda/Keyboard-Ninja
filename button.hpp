#ifndef BUTTONHPP
#define BUTTONHPP
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
class Button : public sf::Drawable
{
private:
    sf::Text text;
    sf::Sprite sprite;
    int id;
    float margin;
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Button (int button_id, std::string button_name, const sf::Font& font, const sf::Texture& texture);
    ~Button();
    void setTexture (const sf::Texture& texture);
    void setPosition(float x, float y);
    void setPosition(sf::Vector2f pos);
    void setMargin (float m);
    int isClicked (sf::Vector2i mousePos);
};
#endif // BUTTONHPP


