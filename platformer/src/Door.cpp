#include "Door.h"
#include "Rectangle.h"
#include "Constants.h"

#include <SFML/Graphics/Drawable.hpp>

Door::Door(Game* pGame) :
    Rectangle(sf::Vector2f(PlayerWidth, PlayerHeight)),
    m_pGame(pGame)
{
    Rectangle::setColor(sf::Color::Green);
}