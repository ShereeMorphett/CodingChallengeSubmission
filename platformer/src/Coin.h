#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Rectangle;

class Coin : public sf::Drawable, public sf::Transformable
{
public:
    Coin(float radius, sf::Vector2f position = sf::Vector2f(0, 0));
    virtual ~Coin() {}
    
    bool collidesWith(Rectangle* other);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getCenter();

    void setCollected(bool isCollected);

    bool getCollected();

private:

    float   m_radius;
    
    bool    m_isCollected = false;
};
