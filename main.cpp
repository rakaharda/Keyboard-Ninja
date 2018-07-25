#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <cstdio>
#include <ctime>
#include <vector>
#include <enemy.hpp>
#include <menus.hpp>
#include <blood.hpp>
#define NOE 100
sf::Vector2f genRandomCoords ();
int main ()
{
    srand(time(NULL));
    sf::Font font;
    sf::Texture kasa_texture;
    sf::Texture background_texture;
    sf::Texture textbox_texture;
    sf::Texture shuriken_texture;
    sf::Texture heart_texture;
    sf::Clock clock;
    sf::Sprite player;
    sf::Sprite background;
    sf::Sprite textbox_bg;
    sf::Sprite heart;
    sf::Text textbox;
    sf::Text fpsCounter;
    sf::Music ingameMusic;
    sf::SoundBuffer keyboardBuffer;
    sf::SoundBuffer playerDeathBuffer;
    sf::SoundBuffer throwBuffer;
    sf::SoundBuffer bloodBuffer;
    sf::SoundBuffer swordBuffer;
    sf::Sound keyboardSound;
    sf::Sound playerDeathSound;
    sf::Sound throwSound;
    sf::Sound bloodSound;
    sf::Sound swordSound;
    std::string words3[]= {"fox", "dog", "cat", "sea", "sky", "low", "son", "sun", "wet", "red", "can", "car", "bed", "bag", "air", "sit", "job", "jug", "joy", "max", "mix", "hex"};
    std::string powerups[]={"dd"};
    std::string *input=new std::string;
    //Загружаем файлы
    font.loadFromFile("./resources/sansation.ttf");
    kasa_texture.loadFromFile("./resources/kasa.png");
    background_texture.loadFromFile ("./resources/background.png");
    textbox_texture.loadFromFile("./resources/textbox.png");
    shuriken_texture.loadFromFile("./resources/shuriken.png");
    heart_texture.loadFromFile("./resources/heart.png");
    ingameMusic.openFromFile("./resources/ingame.ogg");
    keyboardBuffer.loadFromFile("./resources/keyboard.wav");
    playerDeathBuffer.loadFromFile("./resources/death.wav");
    throwBuffer.loadFromFile("./resources/throw.ogg");
    bloodBuffer.loadFromFile("./resources/blood.wav");
    swordBuffer.loadFromFile("./resources/sword.wav");

    //Подготавливаем поле для ввода текста
    textbox.setFont (font);
    textbox.setFillColor(sf::Color::White);
    textbox.setPosition(sf::Vector2f(10, 570));
    textbox.setCharacterSize (20);
    textbox_bg.setTexture(textbox_texture);
    textbox_bg.setPosition(5, 570);

    //Подготавливаем поле
    player.setTexture(kasa_texture);
    player.setPosition(390,290);
    background.setTexture(background_texture);
    heart.setTexture(heart_texture);
    //Привязываем к звукам адреса звуков в памяти
    keyboardSound.setBuffer(keyboardBuffer);
    playerDeathSound.setBuffer(playerDeathBuffer);
    throwSound.setBuffer(throwBuffer);
    bloodSound.setBuffer(bloodBuffer);
    swordSound.setBuffer(swordBuffer);
    //Настраиваем звук
    swordSound.setVolume(70);
    keyboardSound.setVolume(70);
    ingameMusic.setLoop(true);
    ingameMusic.setVolume(50);
    fpsCounter.setPosition(10.f, 10.f);
    fpsCounter.setFont(font);
    fpsCounter.setCharacterSize(10);
    sf::RenderWindow window (sf::VideoMode(800,600), "Keyboard Ninja");

    while(true)
    {
        unsigned int score=0;
        float spawnRate=2.0f;
        float enemySpeed=50.f;
        float timer=0.f;
        float spawnTime=0.f;
        float powerupTime=0.f;
        short unsigned int enemysSpawned=0;
        float doubleDamage=0.f;
        float fps=0.f;
        float fpsTimer=0.f;
        bool gameover=false;
        short health=3;
        delete(input);
        input=new std::string;
        //Выделяем память для объектов
        std::vector<Enemy> enemy;
        std::vector<Blood> blood;
        std::vector<Enemy> shuriken;
        std::vector<Enemy> powerup;
        std::vector<float> powerupLifetime;
        ingameMusic.play();
        clock.restart();

        //Начало цикла игры
        while (window.isOpen()&&gameover==false)
        {
            sf::Event event;
            float deltaTime=clock.restart().asSeconds();
            timer+=deltaTime;
            spawnTime+=deltaTime;
            powerupTime+=deltaTime;
            enemySpeed+=deltaTime;
            spawnRate-=deltaTime*0.08f/timer;
            //Расчет FPS
            fpsTimer+=deltaTime;
            fps++;
            if (fpsTimer>0.5f)
            {
                std::stringstream ss;
                ss<<fps/fpsTimer;
                fpsCounter.setString(ss.str());
                fps=fpsTimer=0.f;
                ss.clear();
            }
            if (doubleDamage>0.f) doubleDamage-=deltaTime;
            //std::cout<<"Delta time: "<<deltaTime<<" Spawn time: "<<powerupTime<<" Spawn rate: "<<spawnRate<<std::endl;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    return 0;
                    break;
                //Блокируем изменение размера окна (фуллскрин все еще работает)
                case sf::Event::Resized:
                    window.setSize(sf::Vector2u(800,600));
                    break;
                case sf::Event::LostFocus:
                        ingameMusic.pause();
                        if (pausemenu(window, font)) return 0;
                        ingameMusic.play();
                        clock.restart();
                        break;
                //Ввод текста
                case sf::Event::TextEntered:
                    if (event.text.unicode>96&&event.text.unicode<123&&input->length()<33)
                    {
                        keyboardSound.play();
                        *input+=(char)event.text.unicode;
                        textbox.setString(*input);
                    }
                    break;
                //Обработка нажатий Enter и Backspace
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Enter:
                        if (input->size()!=0)
                        {
                            throwSound.play();
                            for (unsigned short i=0; i<enemy.size(); i++)
                            {
                                if(enemy[i].checkString(*input))
                                {
                                    std::string s=" ";
                                    shuriken.push_back(Enemy(player.getPosition(), shuriken_texture, font, enemy[i].getPos(), 600.f));
                                    if (doubleDamage>0.f&&enemy.size()!=1) {
                                        if (i!=0) shuriken.push_back(Enemy(player.getPosition(), shuriken_texture, font, enemy[0].getPos(), 600.f));
                                        else shuriken.push_back(Enemy(player.getPosition(), shuriken_texture, font, enemy[1].getPos(), 600.f));
                                    }

                                    i=enemy.size();
                                }
                            }
                            for (unsigned short i=0; i<powerup.size(); i++)
                            {
                                if(powerup[i].checkString(*input))
                                {
                                    std::string s=" ";
                                    shuriken.push_back(Enemy(player.getPosition(), shuriken_texture, font, powerup[i].getPos(), 600.f));
                                    i=powerup.size();
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
                        keyboardSound.play();
                        break;
                    case sf::Keyboard::Escape:
                        ingameMusic.pause();
                        if (pausemenu(window, font)) return 0;
                        ingameMusic.play();
                        clock.restart();
                        break;
                    default:
                        break;
                    }
                    break;

                default:
                    break;
                }
            }//while event

            //Если прошло больше 2х секунд, то создается новый враг, а счетчик обнуляется
            if (spawnTime>=spawnRate)
            {
                spawnTime=0.f;
                if (enemysSpawned<11)
                {
                    short  r;
                    bool f=true;
                    do
                    {
                        f=false;
                        r=rand()%22;
                        for (unsigned short i=0; i<enemy.size(); i++)
                        {
                            if (enemy[i].checkString(words3[r]))
                                f=true;
                        }
                    }
                    while (f);
                    enemy.push_back(Enemy(genRandomCoords(), kasa_texture, font, player.getPosition(), enemySpeed, words3[r]));
                    enemysSpawned++;
                }
            }
            //Каждые 10 секунд - бонусы
            if (powerupTime>=10.f)
            {
                powerupTime=0.f;
                powerup.push_back(Enemy(sf::Vector2f(300, 100), kasa_texture, font, sf::Vector2f(300, 200), 0.f, powerups[0]));
            }
            //Проверка столкновения с игроком каждого врага
            for (unsigned short i=0; i<enemy.size(); i++)
            {
                if (enemy[i].checkCollision(&player))
                {
                    health--;
                    if  (health==0)
                    {
                        gameover=true;
                        swordSound.play();
                        playerDeathSound.play();
                        ingameMusic.stop();
                    } else
                    {
                        swordSound.play();
                        enemy.erase(enemy.begin()+i);
                    }
                }
            }

            //Проверка столкновения сюрикенов и врагов
            for (unsigned short i=0; i<shuriken.size(); i++)
            {
                for (unsigned short j=0; j<enemy.size(); j++)
                    if (shuriken[i].checkCollision(enemy[j].getSpritePointer()))
                    {
                        blood.push_back(Blood(enemy[j].getPos(), enemy[j].getAngle()));
                        bloodSound.play();
                        enemy.erase(enemy.begin()+j);
                        enemysSpawned--;
                        score++;
                    }
                for (unsigned short j=0; j<powerup.size();j++){
                    if (shuriken[i].checkCollision(powerup[j].getSpritePointer()))
                    {
                        powerup.erase(powerup.begin()+j);
                        doubleDamage=10.0f;
                    }
                }
            }

            //Движение врагов
            for (unsigned short i=0; i<enemy.size(); i++)
            {
                enemy[i].update(deltaTime);
            }

            //Движение крови
            for (unsigned short i=0; i<blood.size(); i++)
            {
                blood[i].update(deltaTime);
            }

            //Движение сюрикенов
            for (unsigned short i=0; i<shuriken.size(); i++)
            {
                if (shuriken[i].getPos().x>810||shuriken[i].getPos().x<-10)
                {
                    shuriken.erase(shuriken.begin()+i);
                }
                else
                    shuriken[i].update(deltaTime);
            }
            window.clear();
            //layer1
            window.draw(background);
            //Рисование и удаление крови
            for (unsigned short i=0; i<blood.size(); i++)
            {
                if (blood[i].getTime()<7.f)
                    {
                        window.draw(blood[i]);
                    }
                else
                {
                    blood.erase(blood.begin()+i);
                }
            }
            //Рисование сюрикенов
            for (unsigned short i=0; i<shuriken.size(); i++)
            {
                window.draw(shuriken[i]);
            }
            //layer2
            //Рисование врагов и текста к ним
            for (unsigned short i=0; i<enemy.size(); i++)
            {
               window.draw (enemy[i]);
            }
            //Рисование бонусов
            for (unsigned short i=0; i<powerup.size(); i++)
            {
                window.draw(powerup[i]);
            }
            window.draw (player);
            //Рисование здоровья
            for (unsigned short i=0; i<health; i++)
            {
                heart.setPosition(window.getSize().x-heart_texture.getSize().x*(i+1)-10, 10);
                window.draw(heart);
            }
            //layer3
            window.draw(textbox_bg);
            //layer4
            window.draw(textbox);
            window.draw(fpsCounter);
            window.display();
        }
        if(postscreen(window, font, score))
            return 0;
    }
}

sf::Vector2f genRandomCoords ()
{
    sf::Vector2f pos;
    short r = rand()%4;
    if (r==0)
        pos=sf::Vector2f((float)(std::rand()%800), -10.f);
    else if (r==1)
        pos=sf::Vector2f(std::rand()%800, 610.f);
    else if (r==2)
        pos=sf::Vector2f(-10.f, rand()%600);
    else if (r==3)
        pos=sf::Vector2f(810.f, rand()%600);
    return pos;
}
