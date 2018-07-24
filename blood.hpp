#ifndef BLOODHPP
#define BLOODHPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
class Blood {
private:
    sf::Clock clock;
    sf::VertexArray vertices;
    sf::Vector2f startPos;
    std::vector<float> angle, distance;
    short unsigned speed, count;
public:
    Blood(sf::Vector2f sP, float a);
    ~Blood();
    void update (float elapsed);
    sf::VertexArray getArray();
    float getTime();
};
#endif //BLOODHPP
