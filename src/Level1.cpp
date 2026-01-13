#include "Level.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "var.h"
#include <thread>
#include <iostream>

bool RunLevel1()
{
    x = 10.f;
    y = 300.f;
    doorx = 500.f;
    showsettings = false;
    l1beat = false;
    sf::RenderWindow window1(sf::VideoMode({ 800,600 }), "Level 1");
    ImGui::SFML::Init(window1);
    sf::Clock deltaClock;

    ImVec4 clearColor(1.f, 1.f, 1.f, 1.f);
    window1.setFramerateLimit(60);

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
    shape2.setPosition({ 295.f, 10.f });
    sf::FloatRect shape2Bounds = shape2.getGlobalBounds();

    // Door
    sf::RectangleShape door({ 50.f, 600.f });
    door.setOutlineThickness(2.f);
    door.setOutlineColor(sf::Color::Black);
    door.setPosition({ doorx, -0.f });
    sf::FloatRect doorBounds = door.getGlobalBounds();

    // Corridor
    sf::RectangleShape wall({ 50.f, 400.f });
    wall.setOutlineThickness(2.f);
    wall.setOutlineColor(sf::Color::Black);
    wall.setPosition({ 240.f, -0.f });
    sf::FloatRect wallBounds = wall.getGlobalBounds();

    sf::RectangleShape wall2({ 50.f, 400.f });
    wall2.setOutlineThickness(2.f);
    wall2.setOutlineColor(sf::Color::Black);
    wall2.setPosition({ 350.f, -0.f });
    sf::FloatRect wallBounds2 = wall2.getGlobalBounds();

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

    while (window1.isOpen())
    {
        sf::Event event;
        while (window1.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window1, event);

            if (event.type == sf::Event::Closed)
            {
                window1.close();
                return 0;
            }
        }

        ImGui::SFML::Update(window1, deltaClock.restart());

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

		if (shape.getGlobalBounds().intersects(wall.getGlobalBounds()) or shape.getGlobalBounds().intersects(wall2.getGlobalBounds()))
        {
            x = 10.f; y = 300.f;
            shape.setPosition({ x, y });
        }

        if (shape.getGlobalBounds().intersects(end.getGlobalBounds()))
        {
            l1beat = true;
            ImGui::SFML::Shutdown();
            return true;
        }
        sf::Color bg(
            static_cast<uint8_t>(clearColor.x * 255),
            static_cast<uint8_t>(clearColor.y * 255),
            static_cast<uint8_t>(clearColor.z * 255)
        );

        if (l1beat)
            return true;
        // render shit
        window1.clear(bg);
        window1.draw(wall);
        window1.draw(wall2);
        window1.draw(end);
        window1.draw(spawn);
        window1.draw(shape2);
        window1.draw(door);
        window1.draw(shape);
        ImGui::SFML::Render(window1);
        window1.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
        {
			window1.close();
            RunLevel2();
        }
    }
    ImGui::SFML::Shutdown();
    return true;
}
