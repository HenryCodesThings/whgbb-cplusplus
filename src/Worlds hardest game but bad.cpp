                                //////////////////////////////////////////
                                //                                      //
                                // This is my first EVER C++ project :D //
                                //                                      //
                                //    - Carr0t35 (HenryCodesThings)     //
                                //                                      //
                                //////////////////////////////////////////
                                
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include "var.h"
#include <fstream>
#include <string>
#include <optional>
#include <iomanip>

int level1();
int level2();

int main() {
    level1();
    if (l1beat) {
        level2();
    }
    return 0;
}
int level1() {

        sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Worlds Hardest Game... but bad");
        if (ImGui::SFML::Init(window)) {
            std::cout << "ImGui-SFML initialized successfully." << std::endl;
        }
        else {
            std::cout << "Failed to initialize ImGui-SFML." << std::endl;
            return -1;
        }
        ImVec4 clearColor(1.f, 1.f, 1.f, 1.f);
        window.setFramerateLimit(60);

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

        sf::Clock deltaClock;
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

                ImGuiIO& io = ImGui::GetIO();
                io.FontGlobalScale = 2.f;
                ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
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
                x = 10.f;
                y = 300.f;
                shape.setPosition({ x, y });
            }

            if (const std::optional intersection = shapeBounds.findIntersection(endBounds))
            {
                l1beat = true;
                window.close();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            sf::Color bg(
                static_cast<uint8_t>(clearColor.x * 255),
                static_cast<uint8_t>(clearColor.y * 255),
                static_cast<uint8_t>(clearColor.z * 255)
			);
            window.clear(bg);
            window.draw(end);
            window.draw(spawn);
            window.draw(shape);
            window.draw(shape2);
            window.draw(door);
            ImGui::SFML::Render(window);
            window.display();
        }
        ImGui::SFML::Shutdown();
        return 0;
    }

// LEVEL 2 
int level2() {
        if (l1beat) {
            sf::RenderWindow window2(sf::VideoMode({ 800, 600 }), "Worlds Hardest Game... but bad (Level 2)");
            if (ImGui::SFML::Init(window2)) {
                std::cout << "ImGui-SFML initialized successfully." << std::endl;
			}
            else {
                std::cout << "Failed to initialize ImGui-SFML." << std::endl;
                return -1;
            }
			window2.setFramerateLimit(60);
            sf::Clock deltaClock;

            window2.setFramerateLimit(60);
            ImVec4 clearColor(1.f, 1.f, 1.f, 1.f);
            sf::Color bg(
                static_cast<uint8_t>(clearColor.x * 255),
                static_cast<uint8_t>(clearColor.y * 255),
                static_cast<uint8_t>(clearColor.z * 255)
            );
            while (window2.isOpen())
            {
                while (std::optional event = window2.pollEvent())
                {
                    ImGui::SFML::ProcessEvent(window2, *event);
                    if (event->is<sf::Event::Closed>())
                    {
                        window2.close();
                    }
                    ImGui::SFML::Update(window2, deltaClock.restart());
                    if (showsettings)
                    {
                        ImGuiIO& io = ImGui::GetIO();
                        io.FontGlobalScale = 2.f;
                        ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
                        ImGui::Text("Background color");
                        ImGui::ColorEdit3("clear color", (float*)&clearColor);
                        ImGui::End();
                        sf::Color bg(
                            static_cast<uint8_t>(clearColor.x * 255),
                            static_cast<uint8_t>(clearColor.y * 255),
                            static_cast<uint8_t>(clearColor.z * 255)
						);

                    }
                    bg = sf::Color(
                        static_cast<uint8_t>(clearColor.x * 255),
                        static_cast<uint8_t>(clearColor.y * 255),
                        static_cast<uint8_t>(clearColor.z * 255)
                    );
                    // Settings menu
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    {
                        showsettings = !showsettings;
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                    ImGui::SFML::Update(window2, deltaClock.restart());

                    if (showsettings)
                    {

                        ImGuiIO& io = ImGui::GetIO();
                        io.FontGlobalScale = 2.f;
                        ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
                        ImGui::Text("Background color");
                        ImGui::ColorEdit3("clear color", (float*)&clearColor);
                        ImGui::End();
                    }
                    window2.clear(bg);
                    ImGui::SFML::Render(window2);
                    window2.display();
                }
            }
        }
        ImGui::SFML::Shutdown();
        return 0;
    }
