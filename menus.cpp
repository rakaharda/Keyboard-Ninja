#include <menus.hpp>

int postscreen(sf::RenderWindow &window, sf::Font &font, unsigned int &score)
{
    sf::Clock clock;
    sf::Text text1, text2;
    sf::Sprite sprite;
    sf::Texture postgame_texture;
    std::string str;
    std::stringstream ss;
    postgame_texture.loadFromFile("./resources/postgame.png");
    sprite.setTexture(postgame_texture);
    ss<<score;
    str=ss.str();
    text1.setPosition(sf::Vector2f(20,200));
    text1.setCharacterSize(20);
    text1.setString("Score: "+str);
    text1.setFont(font);
    ss.clear();
    text2.setPosition(sf::Vector2f(20,540));
    text2.setCharacterSize(20);
    text2.setString("To restart press any key");
    text2.setFont(font);
    window.clear();
    window.draw(sprite);
    window.draw(text1);
    window.draw(text2);
    window.display();
    while (clock.getElapsedTime().asSeconds()<1.0f)
    {

    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                return 1;
                break;
            case sf::Event::Resized:
                sf::Vector2u(800,600);
                break;
            case sf::Event::KeyPressed:
                return 0;
            default:
                break;
            }
        }
    }
    return 0;
}

short pausemenu (sf::RenderWindow &window, sf::Font &font)
{
    sf::Sprite sprite;
    sf::Texture texture;
    texture.loadFromFile("./resources/pause.png");
    sprite.setTexture(texture);
    sprite.setPosition((window.getSize().x-texture.getSize().x)/2, (window.getSize().y-texture.getSize().y)/2.f);
    window.draw(sprite);
    window.display();
    while (true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
        case sf::Event::Closed:
            return 1;
            break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    return 0;
                    break;
                default:
                    break;
                }//switch(event.key.code)
                break;
            default:
                break;
            }//switch (event.type)
        } //while(window.pollEvent(event))
    }
    return 0;
}
