#include "InputHandler.h"
#include "Player.h"
#include <iostream>

GameInput::GameInput(Game* pGame, Player* pPlayer) :
    m_pGame(pGame), m_pPlayer(pPlayer)
{}

GameInput::~GameInput()
{}

void GameInput::update(float deltaTime)
{
    if (m_inputData.hasInputs())
    {
        m_pPlayer->move(m_inputData, deltaTime);
    }
}

void GameInput::onButtonPressed(unsigned key)
{
    if (key == 0)
    {
        m_inputData.m_movingUp = true;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_movingDown = true;
    }
    else if (key == 4)
    {
        m_inputData.m_movingLeft = true;
    }
    else if (key == 5)
    {
        m_inputData.m_movingRight = true;
    }
}


void GameInput::onButtonReleased(unsigned key)
{
    if (key == 0)
    {
        m_inputData.m_movingUp = false;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_movingDown = true;
    }   
    else if (key == 4)
    {
        m_inputData.m_movingLeft = false;
    }
    else if (key == 5)
    {
        m_inputData.m_movingRight = false;
    }
    else
    {
        m_inputData.m_movingRight = false;
        m_inputData.m_movingLeft = false;
        m_inputData.m_movingUp = false;

    }

}

void GameInput::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up || key == sf::Keyboard::Space)
    {
        m_inputData.m_movingUp = true;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_movingDown = true;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_movingLeft = true;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_movingRight = true;
    }
}

void GameInput::onKeyReleased(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up || key == sf::Keyboard::Space)
    {
        m_inputData.m_movingUp = false;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_movingDown = false;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_movingLeft = false;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_movingRight = false;
    }
}
