#include <SFML/Graphics.hpp>
#include <string>
#include "square.h"
#include "snake.h"

#define WIDTH 64
#define HEIGHT 48

Square *Board[WIDTH * HEIGHT];

SnakePart *SnakeHead, *SnakeTail;
int snakeDirection = 0;

void fillBoardWithEmptySquares();
void drawBoard(sf::RenderWindow &window);
Square * getSquare(int x, int y);
void updateBoard();

void createSnake(int x, int y);
void moveSnake();

int main()
{
  fillBoardWithEmptySquares();
  createSnake(WIDTH / 2, HEIGHT / 2);
  sf::RenderWindow window(sf::VideoMode(WIDTH * 10, HEIGHT * 10), "Snake");
  window.setFramerateLimit(25);

  while (window.isOpen()) {

    sf::Event event;

    while(window.pollEvent(event)) {

      if (event.type == sf::Event::Closed) {
        printf("CLOSE WINDOW\n");
        window.close();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
      {
        snakeDirection = 0;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
      {
        snakeDirection = 2;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
      {
        snakeDirection = 3;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
      {
        snakeDirection = 1;
      }        
    }

    moveSnake();
    window.clear(sf::Color::Black);
    updateBoard();
    drawBoard(window);
    window.display();    
  }

  return 0;
}

void fillBoardWithEmptySquares()
{
  int i, x, y;
  int counter = 0;
  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
      Square *newSquare = new Square(0, x, y);
      Board[counter] = newSquare;
      counter++;
    }
  }
}

void drawBoard(sf::RenderWindow &window)
{
  int x, y;
  int counter = 0;
  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
      sf::RectangleShape rectangle(sf::Vector2f(10, 10));
      if (Board[counter]->type == 0) {
        rectangle.setFillColor(sf::Color(0, 0, 0));
      } else if (Board[counter]->type == 1) {
        rectangle.setFillColor(sf::Color(255, 0, 0));
      } else if (Board[counter]->type == 2) {
        rectangle.setFillColor(sf::Color(255, 255, 255));
      } else {
        printf("ERROR: UNKNOWN TPYE: %d\n", Board[counter]->type);
      }
      rectangle.setPosition(x * 10, y * 10);
      window.draw(rectangle);

      counter++;
    }
  }
}

void updateBoard() 
{
  int i;
  for (i = 0; i < WIDTH * HEIGHT; i++) {
    Board[i]->type = 0;
  }

  SnakePart *currentSnakePart = SnakeHead;
  while (currentSnakePart->next != NULL) {
    getSquare(currentSnakePart->x, currentSnakePart->y)->type = 2;
    currentSnakePart = currentSnakePart->next;
  }
}

Square * getSquare(int x, int y)
{
  return Board[y * WIDTH + x];
}

void createSnake(int x, int y)
{
  SnakeTail = new SnakePart(x, y, NULL);
  SnakePart *secondPart = new SnakePart(x, y + 1, SnakeTail);
  SnakePart *thirdPart = new SnakePart(x, y + 2, secondPart);
  SnakePart *fourthPart = new SnakePart(x, y + 3, thirdPart);
  SnakeHead = new SnakePart(x, y + 4, fourthPart);
}

void moveSnake()
{
  SnakePart *currentSnakePart = SnakeHead;
  while (currentSnakePart->next != NULL) {
    switch (snakeDirection) {
      case 0:
        currentSnakePart->y--;
        break;
      case 2:
        currentSnakePart->y++;
        break;
      case 3:
        currentSnakePart->x--;
        break;
      case 1:
        currentSnakePart->x++;
        break;
      default:
        break;
    }
    currentSnakePart = currentSnakePart->next;
  }
}