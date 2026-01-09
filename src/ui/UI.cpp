#include <ui/UI.h>
#include <config/TileConstants.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

UI::UI()
{

}

UI::~UI()
{

}

void UI::update()
{

}

void UI::draw(sf::RenderWindow& window, sf::Vector2f mousePos)
{
    healthBar.draw(window);
    inventory.draw(window);
    tgui::Gui gui(window);
    auto testButton = tgui::Button::create("Test");
    testButton->setSize({200, 60});
    testButton->setPosition({"50% - 100", "40%"});

    testButton->onPress([&] {
        std::cout << "Play pressed\n";
    });

    gui.add(testButton);
    gui.draw();
}