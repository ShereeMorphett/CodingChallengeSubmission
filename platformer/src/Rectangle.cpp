
#include "Rectangle.h"
#include <SFML/Graphics.hpp>

Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f position) : m_size(size)
{
    sf::Transformable::setPosition(position);
}

bool Rectangle::collidesWith(Rectangle* pOther)
{
    sf::Vector2f thisPosition = getPosition();
    sf::Vector2f thisSize = getSize();

    sf::Vector2f otherPosition = pOther->getPosition();
    sf::Vector2f otherSize = pOther->getSize();

    float thisLeft = thisPosition.x;
    float thisRight = thisPosition.x + thisSize.x;
    float thisTop = thisPosition.y;
    float thisBottom = thisPosition.y + thisSize.y;

    float otherLeft = otherPosition.x;
    float otherRight = otherPosition.x + otherSize.x;
    float otherTop = otherPosition.y;
    float otherBottom = otherPosition.y + otherSize.y;

    if (thisLeft < otherRight && thisRight > otherLeft &&
        thisTop < otherBottom && thisBottom > otherTop) {
        // Rectangles overlap
        return true;
    }
    return false;
}

void Rectangle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape graphicsRect(m_size);
    graphicsRect.setFillColor(m_color);
    graphicsRect.setPosition(getPosition());
    target.draw(graphicsRect);
}

sf::Vector2f Rectangle::getCenter()
{
    return getPosition() + (m_size * 0.5f);
}
