
#include "Coin.h"
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "MathUtils.h"
#include "Constants.h"

Coin::Coin(float radius, sf::Vector2f position) : m_radius(radius)
{
    float rOffset = CoinRadius;
    position -= sf::Vector2f(rOffset, rOffset);
    position += sf::Vector2f(TileSizeX, TileSizeY) * 0.5f;
    sf::Transformable::setPosition(position);
}

bool Coin::collidesWith(Rectangle* other)
{
    sf::Vector2f position = other->getPosition();
    sf::Vector2f size = other->getSize();

    sf::Vector2f topLeft = position;
    sf::Vector2f topRight = position + sf::Vector2f(size.x, 0);
    sf::Vector2f botLeft = position + sf::Vector2f(0, size.y);
    sf::Vector2f botRight = position + size;

    return VecLength(topRight - getCenter()) < m_radius ||
        VecLength(topLeft - getCenter()) < m_radius ||
        VecLength(botRight - getCenter()) < m_radius ||
        VecLength(botLeft - getCenter()) < m_radius;
}

void Coin::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::CircleShape graphicsCircle(m_radius);

    graphicsCircle.setFillColor(sf::Color::Yellow);
    graphicsCircle.setPosition(getPosition());
    target.draw(graphicsCircle);
}

sf::Vector2f Coin::getCenter()
{
    float rOffset = m_radius * 0.5f;

    return getPosition() + sf::Vector2f(rOffset, rOffset);
}

void Coin::setCollected(bool isCollected)
{
    m_isCollected = isCollected;
}

bool Coin::getCollected()
{
    return m_isCollected;
}
