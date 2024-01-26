#include <SFML/Graphics.hpp>

int main() {
    // Crear la ventana de renderizado
    sf::RenderWindow window(sf::VideoMode(640, 480), "Sprite Animation Example");

    // Cargar la textura del sprite sheet
    sf::Texture texture;
    if (!texture.loadFromFile("/home/southatoms/Escritorio/AO SMFL/graficos/732.png")) {
        // Manejar error
        return -1;
    }

    // Definir los rectángulos para cada frame de animación
    const int frameWidth = 43;
    const int frameHeight = 64;
    const int framesPerAnimation = 5;
    const float movementSpeed = 100.0f; // píxeles por segundo
    const float frameDuration = 0.1f; // segundos por frame

    sf::IntRect downFrames[framesPerAnimation];
    sf::IntRect upFrames[framesPerAnimation];
    sf::IntRect leftFrames[framesPerAnimation];
    sf::IntRect rightFrames[framesPerAnimation];

    for (int i = 0; i < framesPerAnimation; ++i) {
        downFrames[i] = sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight);
        upFrames[i] = sf::IntRect(i * frameWidth, frameHeight, frameWidth, frameHeight);
        leftFrames[i] = sf::IntRect(i * frameWidth, 2 * frameHeight, frameWidth, frameHeight);
        rightFrames[i] = sf::IntRect(i * frameWidth, 3 * frameHeight, frameWidth, frameHeight);
    }

    // Crear el sprite inicial (puedes comenzar con cualquier dirección que prefieras)
    sf::Sprite sprite(texture, downFrames[0]);

    // Posición inicial del sprite
    sf::Vector2f position(320, 240);

    // Para controlar el cambio de frames
    int currentFrame = 0;
    sf::Clock frameClock; // reloj para controlar la duración del frame

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualizar el sprite basado en la entrada del teclado
        float deltaTime = frameClock.restart().asSeconds(); // reiniciar el reloj y obtener el tiempo del último frame
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            position.y += movementSpeed * deltaTime;
            currentFrame = (currentFrame + 1) % framesPerAnimation;
            sprite.setTextureRect(downFrames[currentFrame]);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            position.y -= movementSpeed * deltaTime;
            currentFrame = (currentFrame + 1) % framesPerAnimation;
            sprite.setTextureRect(upFrames[currentFrame]);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            position.x -= movementSpeed * deltaTime;
            currentFrame = (currentFrame + 1) % framesPerAnimation;
            sprite.setTextureRect(leftFrames[currentFrame]);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            position.x += movementSpeed * deltaTime;
            currentFrame = (currentFrame + 1) % framesPerAnimation;
            sprite.setTextureRect(rightFrames[currentFrame]);
        }

        // Actualizar la posición del sprite
        sprite.setPosition(position);

        // Dibujar
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
