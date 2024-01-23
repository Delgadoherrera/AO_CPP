#include <SFML/Graphics.hpp>

int main() {
    // Crear una ventana en modo ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego SFML", sf::Style::Default);

    // Crear un cuadrado (jugador)
    sf::RectangleShape player(sf::Vector2f(50, 50));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(window.getSize().x / 2 - player.getSize().x / 2, window.getSize().y / 2 - player.getSize().y / 2);

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Manejar la entrada del teclado para mover al jugador
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x > 0) {
            player.move(-5, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x < window.getSize().x - player.getSize().x) {
            player.move(5, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getPosition().y > 0) {
            player.move(0, -5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.getPosition().y < window.getSize().y - player.getSize().y) {
            player.move(0, 5);
        }

        // Limpiar la pantalla
        window.clear(sf::Color::Black);

        // Dibujar fondos (rectángulos y líneas de diferentes colores ocres)
        // Puedes personalizar y agregar más elementos según tus necesidades

        // Dibujar el jugador
        window.draw(player);

        // Mostrar la pantalla
        window.display();
    }

    return 0;
}
