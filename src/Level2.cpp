#include "Level.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "var.h"
#include <thread>
#include <iostream>
#include <string>
#include <cstdlib>
float oodx = 400.f;
float oody = 200.f;
std::string direction = "down";
bool RunLevel2()
{
    x = 10.f;
    y = 300.f;
    doorx = 300.f;
    showsettings = false;
    l1beat = false;

    sf::RenderWindow window2(sf::VideoMode({ 800,600 }), "Level 2");
    ImGui::SFML::Init(window2);
    sf::Clock deltaClock;

    ImVec4 clearColor(1.f, 1.f, 1.f, 1.f);
    window2.setFramerateLimit(60);

    // Shape 1 (player)
    sf::RectangleShape shape({ 50.f, 50.f });
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);
    shape.setPosition({ x, y });
    sf::FloatRect shapeBounds = shape.getGlobalBounds();

    // Shape 2 (button)
    sf::RectangleShape shape2({ 50.f, 50.f });
    shape2.setFillColor(sf::Color::Red);
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

    // Spawn point
    sf::RectangleShape spawn({ 75.f, 75.f });
    spawn.setFillColor(sf::Color::Green);
    spawn.setOutlineThickness(2.f);
    spawn.setOutlineColor(sf::Color::Black);
    spawn.setPosition({ 0.f, 290.f });

    // End button
    sf::RectangleShape end({ 75.f, 75.f });
    end.setFillColor(sf::Color::Green);
    end.setOutlineThickness(2.f);
    end.setOutlineColor(sf::Color::Black);
    end.setPosition({ 700.f, 290.f });
    sf::FloatRect endBounds = end.getGlobalBounds();

    while (window2.isOpen())
    {
        sf::Event event;
        while (window2.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window2, event);

            if (event.type == sf::Event::Closed)
            {
                window2.close();
                exit(EXIT_SUCCESS);
            }
        }

        ImGui::SFML::Update(window2, deltaClock.restart());

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

        // object of doom
        int speed = 25;
        sf::RectangleShape ood({ 50.f, 50.f });
        ood.setFillColor(sf::Color::Blue);
        ood.setOutlineThickness(2.f);
        ood.setOutlineColor(sf::Color::Black);
        ood.setPosition({ oodx, oody });

        if (direction == "down")
        {
            oody += speed;
            ood.setPosition({ oodx, oody });
            if (oody > 550.f)
                direction = "up";
        }
        else if (direction == "up")
        {
            oody -= speed;
            ood.setPosition({ oodx, oody });
            if (oody <= 0.f)
                direction = "down";
		}

        if (showsettings)
        {

            ImGuiIO& io = ImGui::GetIO();
            io.FontGlobalScale = 2.f;
            ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::Text("Background color");
            ImGui::ColorEdit3("clear color", (float*)&clearColor);
            ImGui::End();
        }

        if (shape.getGlobalBounds().intersects(shape2.getGlobalBounds()))
        {
            doorx += 1000.f;
            door.setPosition({ doorx, 0.f });
        }

        if (shape.getGlobalBounds().intersects(door.getGlobalBounds()))
        {
            x = 10.f; y = 300.f;
            shape.setPosition({ x, y });
        }

        if (shape.getGlobalBounds().intersects(end.getGlobalBounds()))
        {
            x = 10.f;
            y = 300.f;
            l1beat = true;
        }
        sf::Color bg(
            static_cast<uint8_t>(clearColor.x * 255),
            static_cast<uint8_t>(clearColor.y * 255),
            static_cast<uint8_t>(clearColor.z * 255)
        );

        if (l1beat)
            return true;
        window2.clear(bg);
        window2.draw(end);
        window2.draw(ood);
        window2.draw(spawn);
        window2.draw(shape2);
        window2.draw(shape);
        window2.draw(door);
        ImGui::SFML::Render(window2);
        window2.display();
    }
    ImGui::SFML::Shutdown();
    return true;
}
