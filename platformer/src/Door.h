#pragma once

#include "Rectangle.h"

class Game;

class Door : public Rectangle
{
public:
    Door(Game* pGame);
    virtual ~Door() {}

    int getCoins() const { return m_coins; };

    void setTriggered(bool triggered) { m_isTriggered = triggered; } 
    bool isTriggered() const { return m_isTriggered; }

private:
    Game*   m_pGame;
    bool    m_isTriggered = false;
    int     m_coins = 0;
};
