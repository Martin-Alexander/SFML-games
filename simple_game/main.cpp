#include <SFML/Graphics.hpp>

void renderRedSquare(sf::RenderWindow &window, float x, float y) 
{
  sf::RectangleShape rectangle(sf::Vector2f(10, 10));
  rectangle.setFillColor(sf::Color(255, 0, 0));
  rectangle.setPosition(x, y);
  window.draw(rectangle);
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(640, 480), "");

  float squareXPosition = 20;
  float squareYPosition = 20;

  while (window.isOpen())
  {

    // Event Handling
    sf::Event event;
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
        case sf::Event::Closed:
          window.close();
          break;
        default:
          break;
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
    {
      squareYPosition -= 0.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
    {
      squareYPosition += 0.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
    {
      squareXPosition -= 0.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
    {
      squareXPosition += 0.1;
    }    


    // Rendering
    window.clear(sf::Color::Black);
    renderRedSquare(window, squareXPosition, squareYPosition);
    window.display();
  }

  return 0;
}