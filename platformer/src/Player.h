#pragma once

#include "Rectangle.h"


struct InputData;

class Game;

class Player : public Rectangle
{
public:
    Player(Game* pGame);
    virtual ~Player() {}
    
    bool initialise(){};
    void move(InputData inputData, float deltaTime);
    void updatePhysics(float deltaTime);
    void update(float deltaTime);

    int getCoins() const { return m_coins; };
    void setCoins(int coin) { m_coins = coin; };
    int getLives() const { return m_lives; };
    void setLives(int lives) { m_lives = lives; };

    bool isDead() const { return m_isDead; };
    void loseLife();
    void setIsDead(bool isDead) { m_isDead = isDead; };
    float getJumpTimer() const { return m_jumpTimer; };
    //float setJumpTimer() {};

private:
    bool    m_isGrounded;
    bool    m_isDead = false;
    float   m_jumpTimer = 0.0f;
    Game*   m_pGame;
    int     m_coins = 0;
    int     m_lives = 3;
};
