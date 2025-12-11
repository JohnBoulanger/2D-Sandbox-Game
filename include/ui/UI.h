#include <SFML/Graphics.hpp>

class UI
{
public:
    UI();
    ~UI();

    void update();
    void draw(sf::RenderWindow &window);

private:
    sf::Font font;
    // HealthBar healthBar;
    // Inventory inventory;
    // PauseMenu pauseMenu;

};