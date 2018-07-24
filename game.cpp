#include <game.hpp>

int game ()
{
    srand(time(NULL));
    sf::Font font;
    sf::Texture kasa_texture;
    sf::Texture background_texture;
    sf::Texture textbox_texture;
    sf::Texture postgame_texture;
    std::string *input=new std::string;
    sf::Clock clock;
    sf::Clock spawnClock;
    sf::Sprite player;
    sf::Sprite background;
    sf::Sprite textbox_bg;
    sf::Sprite postgame;
    sf::Text textbox;
    sf::Vector2f startPos[]=
    {
        sf::Vector2f(80.f,-20.f),sf::Vector2f(400.f,-20.f),sf::Vector2f(720.f,-20.f),
        sf::Vector2f(820.f, 300.f),sf::Vector2f(720.f,620.f),sf::Vector2f(400.f,620.f),
        sf::Vector2f(80,620),sf::Vector2f(-20,300)
    };
    unsigned int score=0;
    float angle[]= {M_PI*7/4, 3*M_PI/2, M_PI*5/4, M_PI, M_PI*3/4, M_PI/2, M_PI/4, 0};
    float enemySpeed=50.f;
    std::string words3[]= {"fox", "dog", "cat", "sea", "sky", "low", "son", "sun", "wet", "red", "can", "car", "bed", "bag", "air", "sit"};
    short unsigned int enemysSpawned=0;
    bool gameover=false;
    //loading files
    font.loadFromFile("./resources/sansation.ttf");
    kasa_texture.loadFromFile("./resources/kasa.png");
    background_texture.loadFromFile ("./resources/background.png");
    textbox_texture.loadFromFile("./resources/textbox.png");
    postgame_texture.loadFromFile("./resources/postgame.png");
    //textbox
    textbox.setFont (font);
    textbox.setFillColor(sf::Color::White);
    textbox.setPosition(sf::Vector2f(10, 570));
    textbox.setCharacterSize (20);
    textbox_bg.setTexture(textbox_texture);
    textbox_bg.setPosition(5, 570);
    //windows sprites
    postgame.setTexture(postgame_texture);
    Enemy **enemyArray=new Enemy*[NOE];
    for (int i=0; i<NOE; i++)
    {
        enemyArray[i]=NULL;
    }
    //Setting up the game board
    player.setTexture(kasa_texture);
    player.setPosition(390,290);

    background.setTexture(background_texture);

    sf::RenderWindow window (sf::VideoMode(800,600), "Keyboard Ninja");

    while (window.isOpen()&&gameover==false)
    {
        sf::Event event;
        float deltaTime=clock.restart().asSeconds();
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                return 0;
                break;
            case sf::Event::Resized:
                sf::Vector2u(800,600);
                break;
            case sf::Event::LostFocus:
                clock.restart();
                continue;
            case sf::Event::TextEntered:
                if (event.text.unicode>96&&event.text.unicode<123&&input->length()<10)
                {
                    *input+=(char)event.text.unicode;
                    textbox.setString(*input);
                }
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Enter:
                    if (input->size()!=0)
                    {
                        for (int i=0; i<NOE; i++)
                        {
                            if (enemyArray[i]!=NULL)
                            {
                                if(killenemy(enemyArray[i], *input))
                                {
                                    enemyArray[i]=NULL;
                                    enemysSpawned--;
                                    score++;
                                    i=NOE;
                                }
                            }
                        }
                        delete(input);
                        input=new std::string;
                        textbox.setString(*input);
                    }
                    break;
                case sf::Keyboard::Backspace:
                    if (input->size()!=0)
                    {
                        input->erase(input->length()-1, 1);
                        textbox.setString(*input);
                    }
                    break;
                default:
                    break;
                }
                break;

            default:
                break;
            }
        }//while event
        if (spawnClock.getElapsedTime().asSeconds()>=2.f)
        {
            spawnClock.restart();
            if (enemysSpawned<11)
            {
                int i=0;
                while (enemyArray[i]!=NULL&&i!=NOE)
                    i++;
                if (i!=NOE)
                {
                    short int r=rand()%9, r2=rand()%16;
                    enemyArray[i]=new Enemy(words3[r2], kasa_texture, font);
                    enemysSpawned++;
                }
            }
        }
        for (int i=0; i<NOE; i++)
        {
            if (enemyArray[i]!=NULL)
                if (enemyArray[i]->checkCollision())
                    gameover=true;
        }
        float factor = enemySpeed*deltaTime;
        for (int i=0; i<NOE; i++)
        {
            if (enemyArray[i]!=NULL)
            {
                enemyArray[i]->move(factor);
            }
        }
        window.clear();
        //layer1
        window.draw(background);
        //layer2
        for (int i=0; i<NOE; i++)
        {
            if (enemyArray[i]!=NULL)
            {
                window.draw(enemyArray[i]->getSprite());
                window.draw(enemyArray[i]->getTextbox());
            }
        }
        window.draw (player);
        //layer3
        window.draw(textbox_bg);
        //layer4
        window.draw(textbox);
        window.display();
    }
    postscreen(window, postgame, font, score);
    return 0;
}
