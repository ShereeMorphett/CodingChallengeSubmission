#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "InputHandler.h"
#include "Player.h"
#include "resources/Resources.h"
#include "Rectangle.h"
#include "Coin.h"
#include "Door.h"
//#include "MainMenu.h"

Game::Game() :
    m_state(State::WAITING),
    m_pClock(std::make_unique<sf::Clock>()),
    m_pPlayer(std::make_unique<Player>(this)),
    m_pDoor(std::make_unique<Door>(this)),
    m_score(0),
    m_clearedLevels(0)
{
    
    m_pGameInput = std::make_unique<GameInput>(this, m_pPlayer.get());
}

Game::~Game()
{
    
}
void Game::setImgui()
{
    if (m_isImguiEnabled == true)
        m_isImguiEnabled = false;
    else if (m_isImguiEnabled == false)
        m_isImguiEnabled = true;
}

int Game::getPlayerLives() const
{
    if (m_pPlayer)
    {
        return m_pPlayer->getLives();
    }
}

bool Game::initialise(sf::Vector2f pitchSize)
{
    m_pClock->restart();
    std::string assetPath = Resources::getAssetPath();
    if (!m_font.loadFromFile(assetPath + "Lavigne.ttf"))
    {
        std::cerr << "Unable to load font" << std::endl;
        return false;
    }
    //Initialize shapes from TileMap
    resetLevel(MapArray1, false);
    return true;
}




void Game::resetLevel(const int* tileMap, bool restart)
{
    if (restart == true)
    {
        m_pPlayer->setLives(3);
        m_pPlayer->setCoins(0);
        m_clearedLevels = 0;
    }
    m_pCoins.clear();
    m_pRectangles.clear();
    
    if (m_pPlayer->isDead())
    { 
        m_pPlayer->loseLife();
        if (m_pPlayer->isDead())
            m_state = State::END;
    }
    m_pPlayer->setIsDead(false);
    m_pDoor->setTriggered(false);

    const sf::Vector2f tileSize(TileSizeX, TileSizeY);

    for (int y = 0; y < GridSize; y++)
    {
        for (int x = 0; x < GridSize; x++)
        {
            int i = x + y * GridSize;

            const sf::Vector2f worldPos = sf::Vector2f(x * tileSize.x, y * tileSize.y);
            switch (tileMap[i])
            {
                case    eTile::eCoin:
                    m_pCoins.push_back(std::make_unique<Coin>(CoinRadius, worldPos));
                    break;
                case    eTile::eBlock:
                    m_pRectangles.push_back(std::make_unique<Rectangle>(tileSize, worldPos));
                    break;
                case    eTile::ePlayerSpawn :
                    m_pPlayer->setPosition(worldPos);
                    break;
                case    eTile::eDoor :
                    m_pDoor->setPosition(worldPos);
                    break;
                default:
                    break;
            }
        }
    }
}



void Game::update(float deltaTime)
{
    switch (m_state)
    {
        case State::WAITING:
        {
            if (m_pClock->getElapsedTime().asSeconds() >= 3.f)
            {
                m_state = State::ACTIVE;
            }
        }
        break;
        case State::ACTIVE:
        {
            m_pGameInput->update(deltaTime);
            m_pPlayer->updatePhysics(deltaTime);
            m_pPlayer->update(deltaTime);

            if (m_pPlayer->isDead())
            { 
                if (m_pPlayer->getLives() < 0)
                {
                    resetLevel(MapArray1, true);
                }
                else
                    resetLevel(MapArray1, false);

            }
                
            if (m_pDoor->isTriggered())
            {
                m_clearedLevels++;
                if (m_clearedLevels > LevelCount)
                {
                    m_state = State::END;
                    m_pClock->restart();
                    resetLevel(MapArray1, false);
                }
                else
                {
                    m_clearedLevels++;
                    resetLevel(MapArray2, false);
                }
            }
        }
        break;
    }
    int i = 0;
    while (i < m_pCoins.size())
    {
        if (m_pCoins[i]->getCollected())
        {
            std::swap(m_pCoins[i], m_pCoins.back());
            m_pCoins.pop_back();
            continue;
        }
        i++;
    }

    
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //  Draw texts.
    if (m_state == State::WAITING)
    {
        sf::Text startText;
        sf::Text debugText;
        startText.setFont(m_font);
        startText.setString("Game Start!");
        debugText.setFont(m_font);
        debugText.setString("press F1 for dev tools");
        debugText.setCharacterSize(35);
        debugText.setFillColor(sf::Color::White);
        startText.setFillColor(sf::Color::White);
        startText.setPosition(80.0f, 80.0f);
        startText.setStyle(sf::Text::Bold);
        if (m_clearedLevels == 0)
            target.draw(startText);
    }
    else if (m_state == State::END)
    {
        sf::Text lostText;
        sf::Text coinText;
        coinText.setFont(m_font);
        lostText.setFont(m_font);
        lostText.setString("Game Over! Press Enter to Restart");
        if (getPlayerLives() > 0)
            lostText.setFillColor(sf::Color::Green);
        else
            lostText.setFillColor(sf::Color::Red);
        lostText.setPosition(80.0f, 80.0f);
        coinText.setFillColor(sf::Color::White);
        coinText.setString("Score: " + std::to_string(m_pPlayer->getCoins()));
        coinText.setColor(sf::Color::Yellow);
        coinText.setPosition(sf::Vector2f((ScreenWidth - 25) - coinText.getLocalBounds().getSize().x, 0));        lostText.setStyle(sf::Text::Bold);
        target.draw(lostText);
        target.draw(coinText);
    }
    else
    {
        sf::Text coinText;
        sf::Text lifeText;
        lifeText.setString("Lives: " + std::to_string(m_pPlayer->getLives()));
        lifeText.setFont(m_font);
        lifeText.setFillColor(sf::Color::Red);
        lifeText.setPosition(sf::Vector2f( 25 - coinText.getLocalBounds().getSize().x, 0));
        coinText.setFont(m_font);
        coinText.setFillColor(sf::Color::White);
        coinText.setStyle(sf::Text::Bold);
        coinText.setString("Score: " + std::to_string(m_pPlayer->getCoins()));
        coinText.setColor(sf::Color::Yellow);
        coinText.setPosition(sf::Vector2f((ScreenWidth - 25) - coinText.getLocalBounds().getSize().x, 0));
        target.draw(coinText);
        target.draw(lifeText);
    }

    // Draw player.
    m_pPlayer->draw(target, states);

    //  Draw world.
    for (auto& temp : m_pCoins)
    {
        temp->draw(target, states);
    }
    for (auto& temp : m_pRectangles)
    {
        temp->draw(target, states);
    }

    m_pDoor->draw(target, states);
}

void Game::onButtonPressed(unsigned int button)
{
    m_pGameInput->onButtonPressed(button);
}
void Game::onButtonReleased(unsigned int button)
{
    m_pGameInput->onButtonReleased(button);
}

void Game::onKeyPressed(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyPressed(key);
}

void Game::onKeyReleased(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::F1)
        setImgui();
    else if (key == sf::Keyboard::Enter && getState() == State::END)
    {
        resetLevel(MapArray1, true);
        m_state = State::ACTIVE;
    }
    else
        m_pGameInput->onKeyReleased(key);
}

std::vector<Coin*> Game::getCoins()
{
    std::vector<Coin*> pCoins;

    for (auto& temp : m_pCoins)
    {
        pCoins.push_back(temp.get());
    }
    return pCoins;
}

std::vector<Rectangle*> Game::getRectangles() const
{
    std::vector<Rectangle*> pRectangles;

    for (auto& pRectangle : m_pRectangles)
    {
        pRectangles.push_back(pRectangle.get());
    }
    return (pRectangles);
}

Door* Game::getDoor()
{
    return m_pDoor.get();
}
