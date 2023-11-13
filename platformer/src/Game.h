#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include "Constants.h"

class Player;
class Game;
class GameInput;
class Rectangle;
class Coin;
class Door;

namespace sf { class Clock; }

class Game : public sf::Drawable
{
public:
    
    enum class State
    {
        WAITING,
        ACTIVE,
        END,
    };
    
    Game();
    ~Game();
    
    bool initialise(sf::Vector2f pitchSize);
    void update(float deltaTime);
    void resetLevel(const int tileMap[GridSize * GridSize], bool restart);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    State getState() const { return m_state; }
    void setImgui();
    bool getImgui() { return m_isImguiEnabled; };
    bool getclearedLevels() { return m_clearedLevels; };
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
    void onButtonPressed(unsigned int button);
    void onButtonReleased(unsigned int button);
    int getPlayerLives() const;


    Door*                   getDoor();
    std::vector<Rectangle*> getRectangles() const;
    std::vector<Coin*>      getCoins();


private:
    bool m_isImguiEnabled = false;
    std::unique_ptr<Player> m_pPlayer;
    std::unique_ptr<Door> m_pDoor;

    std::vector<std::unique_ptr<Rectangle>> m_pRectangles;
    std::vector<std::unique_ptr<Coin>> m_pCoins;

    State m_state;
    std::unique_ptr<sf::Clock> m_pClock;
    std::unique_ptr<GameInput> m_pGameInput;

    int m_clearedLevels;
    int m_score;
    
    sf::Font m_font;
};
