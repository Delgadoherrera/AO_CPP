#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int main()
{
    // Configuración del área de juego y baldosas
    const int tileSize = 32; // Tamaño de la baldosa en píxeles
    const int tilesPerRow = 99;
    const int tilesPerColumn = 99;
    const int windowWidth = tileSize * tilesPerRow;
    const int windowHeight = tileSize * tilesPerColumn;

    // Crear la ventana de renderizado
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sprite Animation Example");

    // Cargar la textura del sprite sheet
    sf::Texture texture;
    if (!texture.loadFromFile("/home/southatoms/Escritorio/AO SMFL/graficos/732.png"))
    {
        // Manejar error
        return -1;
    }

    // Cargar la textura de la baldosa
    sf::Texture tileTexture;
    if (!tileTexture.loadFromFile("/home/southatoms/Escritorio/AO SMFL/graficos/pisos/8154.png"))
    {
        // Manejar error
        return -1;
    }

    // Definir los rectángulos para cada frame de animación
    const int frameWidth = 43;
    const int frameHeight = 64;
    const int framesPerAnimation = 5;

    sf::IntRect downFrames[framesPerAnimation];
    sf::IntRect upFrames[framesPerAnimation];
    sf::IntRect leftFrames[framesPerAnimation];
    sf::IntRect rightFrames[framesPerAnimation];

    for (int i = 0; i < framesPerAnimation; ++i)
    {
        downFrames[i] = sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight);
        upFrames[i] = sf::IntRect(i * frameWidth, frameHeight, frameWidth, frameHeight);
        leftFrames[i] = sf::IntRect(i * frameWidth, 2 * frameHeight, frameWidth, frameHeight);
        rightFrames[i] = sf::IntRect(i * frameWidth, 3 * frameHeight, frameWidth, frameHeight);
    }

    // Crear el sprite inicial (puedes comenzar con cualquier dirección que prefieras)
    sf::Sprite sprite(texture, downFrames[0]);
    sprite.setScale(0.5f, 0.5f); // Reducir el tamaño del sprite a la mitad para ajustar a una baldosa

    // Crear un sprite para la baldosa
    sf::Sprite tileSprite(tileTexture);

    // Crear una fuente para el número en el centro de cada baldosa
    sf::Font font;
    if (!font.loadFromFile("/home/southatoms/Escritorio/AO SMFL/NotoSerifCJK-Bold.ttc"))
    {
        // Manejar error
        return -1;
    }

    // Posición inicial del sprite (centrado en una baldosa)
    sf::Vector2f position(tileSize / 2, tileSize / 2); // Iniciar en el centro de la primera baldosa

    // Para controlar el cambio de frames
    int currentFrame = 0;
    sf::Clock frameClock; // reloj para controlar la duración del frame

    // Bucle principal del juego
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Guardar la posición anterior para verificar los límites del mapa
        sf::Vector2f previousPosition = position;

        // Obtener el tiempo transcurrido desde la última actualización
        float deltaTime = frameClock.restart().asSeconds();

        // Movimiento del jugador en baldosas
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            position.y += 7 * deltaTime; // Ajusta la velocidad según tus preferencias
            currentFrame = (currentFrame + 1) % framesPerAnimation;
            sprite.setTextureRect(downFrames[currentFrame]);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            position.y -= 7 * deltaTime;
            currentFrame = (currentFrame + 1) % framesPerAnimation;
            sprite.setTextureRect(upFrames[currentFrame]);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            position.x -= 7 * deltaTime;
            currentFrame = (currentFrame + 1) % framesPerAnimation;
            sprite.setTextureRect(leftFrames[currentFrame]);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            position.x += 7 * deltaTime;
            currentFrame = (currentFrame + 1) % framesPerAnimation;
            sprite.setTextureRect(rightFrames[currentFrame]);
        }

        // Verificar los límites del mapa
        if (position.x < 0 || position.x >= tilesPerRow || position.y < 0 || position.y >= tilesPerColumn)
        {
            // Restaurar la posición anterior si el jugador se sale de los límites
            position = previousPosition;
        }

        // Centrar la cámara en el jugador
        sf::View view = window.getView();
        view.setCenter(position.x * tileSize + tileSize / 2, position.y * tileSize + tileSize / 2);
        window.setView(view);

        // Dibujar
        window.clear();

        // Dibujar el patrón de baldosas con números en el centro
        int uniqueTileNumber = 0; // Nuevo índice único

        for (int x = 0; x < tilesPerRow; ++x)
        {
            for (int y = 0; y < tilesPerColumn; ++y)
            {
                tileSprite.setPosition(x * tileSize, y * tileSize);
                window.draw(tileSprite);

                // Dibujar el número en el centro de la baldosa
                sf::Text tileNumber;
                tileNumber.setFont(font);
                tileNumber.setCharacterSize(12);
                tileNumber.setFillColor(sf::Color::Black);
                tileNumber.setString(std::to_string(uniqueTileNumber++)); // Utilizar el índice único
                tileNumber.setPosition(x * tileSize + tileSize / 2 - 6, y * tileSize + tileSize / 2 - 8);
                window.draw(tileNumber);
            }
        }

        // Actualizar la posición del sprite
        sprite.setPosition(position.x * tileSize, position.y * tileSize);

        window.draw(sprite);
        window.display();
    }

    return 0;
}
