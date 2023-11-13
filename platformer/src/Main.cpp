#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Game.h"
#include <memory>
#include <iostream>
#include "imgui-SFML.h"
#include "imgui.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Platformer");
    window.setKeyRepeatEnabled(false);

    std::unique_ptr<Game> pGame = std::make_unique<Game>();
    if (!pGame->initialise(window.getView().getSize()))
    {
        std::cerr << "Game Failed to initialise" << std::endl;
        return 1;
    }

    sf::Clock clock;
    sf::Color color = sf::Color::Black;
    bool check = false;
    // run the program as long as the window is open
    ImGui::SFML::Init(window);
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    // "close requested" event: we close the window
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    pGame->onKeyPressed(event.key.code);
                    break;
                case sf::Event::KeyReleased:
                    pGame->onKeyReleased(event.key.code);
                    break;
                default:
                    break;
            }

            if (sf::Joystick::isConnected(0))
            {
                if (event.type == sf::Event::JoystickButtonPressed)
                {
                    pGame->onButtonPressed(event.joystickButton.button);
                }
                if (event.type == sf::Event::JoystickButtonReleased)
                {
                    pGame->onButtonReleased(event.joystickButton.button);
                }
            }
        }

        if (pGame->getImgui())
            ImGui::SFML::ProcessEvent(event);
    
    sf::Time elapsedTime = clock.getElapsedTime();
    pGame->update(elapsedTime.asSeconds());
    if (pGame->getImgui())
    {
        ImGui::SFML::Update(window, clock.restart());
        ImGui::Begin("Developer Tools");
        ImGui::Text("Current state: %i", pGame->getState());
        ImGui::Text("Gravity: %f", Gravity);
        ImGui::Text("Jump Velocity: %f", JumpYVelocity);
        ImGui::Text("Current Live: %i", pGame->getPlayerLives());
        ImGui::Text("Current Levels Passed: %i", pGame->getclearedLevels());
        ImGui::Checkbox("Backgroud: Cyan", &check);
        if (check == true)
            color = sf::Color::Cyan;
        else
            color = sf::Color::Black;
        if (ImGui::Button("Level Reset"))
        {
            pGame->resetLevel(MapArray1, false);
        }
        if (ImGui::Button("Game Reset"))
        {
            pGame->resetLevel(MapArray1, true);
        }
        ImGui::End();
    }
    else
        clock.restart();

    window.clear(color);

    window.draw(*pGame.get());
    if (pGame->getImgui())
    {
        ImGui::SFML::Render(window);
    }
    // end the current frame
    window.display();
}
    if(pGame->getImgui())
        ImGui::SFML::Shutdown();

    return 0;
}
