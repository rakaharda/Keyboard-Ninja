#include <button.hpp>

Button::Button (int button_id, std::string button_name, const sf::Font& font, const sf::Texture& texture)
{
    id=button_id;
    margin=5.f;
    text.setFont (font);
    text.setCharacterSize(10);
    text.setString(button_name);
    sprite.setTexture(texture);
}
Button::~Button()
{

}
void Button::setTexture (const sf::Texture& texture)
{
    sprite.setTexture(texture);
}
void Button::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
    text.setPosition(x+margin, y+sprite.getTexture()->getSize().y/2.f-text.getCharacterSize()/2.f);
}
void Button::setPosition (sf::Vector2f pos)
{
    sprite.setPosition(pos);
    text.setPosition(pos.x+margin, pos.y+sprite.getTexture()->getSize().y/2.f-text.getCharacterSize()/2.f);
}
void Button::setMargin(float m)
{
    text.move(-margin+m, 0);
    margin=m;
}
int Button::isClicked (sf::Vector2i mousePos)
{
    int return_id=-1;
    if (sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) return_id=id;
    return return_id;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite);
    target.draw(text);
}

