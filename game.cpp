#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

// Set the screen size
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main()
{
    // Seed the random number generator
    srand(time(NULL));

    // Create the window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "My Game");

    // Create the player rectangle shape
    sf::RectangleShape player(sf::Vector2f(100, 100));
    player.setFillColor(sf::Color::Red);
    player.setOrigin(50, 50);
    player.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);

    // Set the player speed
    const float PLAYER_SPEED = 10;

    // Create the enemy circle shape
    sf::CircleShape enemy(50);
    enemy.setFillColor(sf::Color::Blue);
    enemy.setOrigin(50, 50);
    enemy.setPosition(rand() % SCREEN_WIDTH, 0);

    // Set the enemy speed
    const float ENEMY_SPEED = 5;

    // Set the score
    int score = 0;

    // Set the font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Error loading font\n";
        return -1;
    }

    // Set the score text
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    // Start the game loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Move the player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player.move(-PLAYER_SPEED, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player.move(PLAYER_SPEED, 0);
        }

        // Move the enemy
        enemy.move(0, ENEMY_SPEED);

        // Check for collision
        float distance = std::sqrt(std::pow(player.getPosition().x - enemy.getPosition().x, 2) + std::pow(player.getPosition().y - enemy.getPosition().y, 2));
        if (distance < 75)
        {
            score -= 1;
            enemy.setPosition(rand() % SCREEN_WIDTH, 0);
        }

        // Draw the screen
        window.clear(sf::Color::Black);
        window.draw(player);
        window.draw(enemy);
        window.draw(scoreText);
        window.display();

        // Update the score
        score += 1;
        scoreText.setString("Score: " + std::to_string(score));

        // Check if the enemy has reached the bottom of the screen
        if (enemy.getPosition().y >= SCREEN_HEIGHT)
        {
            score += 1;
            enemy.setPosition(rand() % SCREEN_WIDTH, 0);
            ENEMY_SPEED += 0.5;
        }
    }

    return 0;
}
