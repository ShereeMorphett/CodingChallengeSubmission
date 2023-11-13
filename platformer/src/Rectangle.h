#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>

class Rectangle : public sf::Drawable, public sf::Transformable
{
public:
    Rectangle(sf::Vector2f size, sf::Vector2f position = sf::Vector2f(0, 0));
    virtual ~Rectangle() {}
    
    bool collidesWith(Rectangle* pOther);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getCenter();

    sf::Vector2f getSize() const { return m_size; }

    void setColor(sf::Color color) { m_color = color; }

private:
    sf::Color m_color = sf::Color::White;
    sf::Vector2f m_size;
};
