#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <optional>
#include <chrono>
#include <thread>
#include <utility>
float x = 10.f;
float y = 300.f;
float doorx = 300.f;
bool showsettings = false;
std::pair<float, float> spawn() {
    x = 10.f;
    y = 300.f;
    return { x, y };
}  
int main() {
    float windowWidth = 800.f;
    float windowHeight = 600.f;


    sf::RenderWindow window(sf::VideoMode({800, 600}), "Worlds Hardest Game... but bad");
    ImGui::SFML::Init(window);
    window.setFramerateLimit(60);

    // Shape 1 (player)
    sf::RectangleShape shape({ 50.f, 50.f });
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);
    shape.setPosition({ x, y });
    sf::FloatRect shapeBounds = shape.getGlobalBounds();

    // Shape 2 (obstacle)
    sf::RectangleShape shape2({ 50.f, 50.f });
    shape2.setOutlineThickness(2.f);
    shape2.setOutlineColor(sf::Color::Black);
    shape2.setPosition({ 100.f, 100.f });
    sf::FloatRect shape2Bounds = shape2.getGlobalBounds();

    // Door
    sf::RectangleShape door({ 50.f, 600.f });
    door.setOutlineThickness(2.f);
    door.setOutlineColor(sf::Color::Black);
    door.setPosition({ doorx, -0.f });
    sf::FloatRect doorBounds = door.getGlobalBounds();

    sf::Clock deltaClock;
    ImVec4 clearColor(1.f, 1.f, 1.f, 1.f);
    while (window.isOpen())
    {
        while (std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        
        
        }
        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            y -= 5.f;
            shape.setPosition({ x, y });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            y += 5.f;
            shape.setPosition({ x, y });

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            x += 5.f;
            shape.setPosition({ x, y });

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            x -= 5.f;
            shape.setPosition({ x, y });
        }

        // Window collision
        if (shape.getPosition().x < 0)
        {
            x = 0.f;
            shape.setPosition({ x, y });
        }

        if (shape.getPosition().x > 750.f)
        {
            x = 750.f;
            shape.setPosition({ x, y });
        }

        if (shape.getPosition().y < 0)
        {
            y = 0.f;
            shape.setPosition({ x, y });
        }

        if (shape.getPosition().y > 550)
        {
            y = 550.f;
            shape.setPosition({ x, y });
        }
        // Settings menu
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            showsettings = !showsettings;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        if (showsettings)
        {
                ImGui::Begin("Settings");
                ImGui::Text("Background color");
                ImGui::ColorEdit3("clear color", (float*)&clearColor);
                ImGui::End();    
        }           

        // Always update bounds after movement, because they might have changed
        sf::FloatRect shapeBounds = shape.getGlobalBounds();
        sf::FloatRect shape2Bounds = shape2.getGlobalBounds();

        if (const std::optional intersection = shapeBounds.findIntersection(shape2Bounds))
        {
            doorx += 1000.f;
            door.setPosition({ doorx, -0.f });
            doorBounds = door.getGlobalBounds();
        }

        if (const std::optional intersection = shapeBounds.findIntersection(doorBounds))
        {
            spawn();
            shape.setPosition({ x, y });
        }
        sf::Color bg(
            static_cast<uint8_t>(clearColor.x * 255),
            static_cast<uint8_t>(clearColor.y * 255),
            static_cast<uint8_t>(clearColor.z * 255)
        );
        window.clear(bg);
        ImGui::SFML::Render(window);
        window.draw(shape);
        window.draw(shape2);
        window.draw(door);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
