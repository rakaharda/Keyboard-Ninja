#include <blood.hpp>

Blood::Blood(sf::Vector2f sP, float a)
{
    clock.restart();
    srand(time(NULL));
    count=150;
    speed=600.f;
    angle.reserve(count);
    distance.reserve(count);
    startPos=sP;
    vertices=sf::VertexArray(sf::Points, count);
    for (short i=0; i<count-20; i++)
    {
        vertices[i].color=sf::Color(std::rand()%155+100, 0, 0);
        vertices[i].position=startPos;
        angle[i]=(a+(float)(std::rand()%40-20)*3.14f/180.f+3.14f);
        short r=std::rand()%3;
        if (r==2)
            distance[i]=std::rand()%50;
        else
            distance[i]=std::rand()%20;
    }
    for (short i=count-20; i<count-10; i++)
    {
        vertices[i].color=sf::Color(std::rand()%155+100, 0, 0);
        vertices[i].position=startPos;
        angle[i]=(a+(float)(std::rand()%80)*3.14f/180.f+3.14f);
        distance[i]=std::rand()%50;
    }
    for (short i=count-10; i<count; i++)
    {
        vertices[i].color=sf::Color(std::rand()%155+100, 0, 0);
        vertices[i].position=startPos;
        angle[i]=(a+(float)(std::rand()%80*(-1))*3.14f/180.f+3.14f);
        distance[i]=std::rand()%50;
    }
    //std::cout<<"Blood at "<<startPos.x<<','<<startPos.y<<" created!"<<std::endl;
}
Blood::~Blood()
{
    //std::cout<<"Blood destroyed!"<<std::endl;
}
void Blood::update(float elapsed)
{
    for (short i=0; i<count; i++)
    {
        sf::Vector2f currentPos=vertices[i].position;
        if (std::sqrt(pow(currentPos.x-startPos.x, 2)+pow(currentPos.y-startPos.y, 2))<distance[i])
            vertices[i].position+=sf::Vector2f(std::cos(angle[i])*elapsed*speed, std::sin(angle[i])*elapsed*speed*(-1));
        if (clock.getElapsedTime().asSeconds()>2.f)
        vertices[i].color.a=255-(clock.getElapsedTime().asSeconds()-2.f)*255/5;

    }
}
sf::VertexArray Blood::getArray()
{
    return vertices;
}

float Blood::getTime()
{
    return clock.getElapsedTime().asSeconds();
}
