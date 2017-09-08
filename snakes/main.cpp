#include <SFML/Graphics.hpp>
#include <string>
#include "square.h"
#include "snake.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

#define WIDTH 38
#define HEIGHT 24
#define INITIAL_SNAKE_SIZE 5


Square *Board[WIDTH * HEIGHT];
int score = 0;

SnakePart *SnakeHead, *SnakeTail;
int snakeDirection = 0;
sf::RenderWindow window(sf::VideoMode(WIDTH * 10, HEIGHT * 10), "Snake");

void fillBoardWithEmptySquares();
void drawBoard(sf::RenderWindow &window);
Square * getSquare(int x, int y);
void updateBoard();

void createSnake(int x, int y, int size);
void moveSnake();
int extendSnake(int x, int y);
void addFruit();

int main()
{
  std::srand(std::time(0));
  fillBoardWithEmptySquares();
  createSnake(WIDTH / 2, HEIGHT / 2 + INITIAL_SNAKE_SIZE, INITIAL_SNAKE_SIZE);
  window.setFramerateLimit(20);

  while (window.isOpen()) {

    sf::Event event;

    while(window.pollEvent(event)) {

      if (event.type == sf::Event::Closed) {
        printf("CLOSE WINDOW\n");
        window.close();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snakeDirection != 2) 
      {
        snakeDirection = 0;
        break;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snakeDirection != 0) 
      {
        snakeDirection = 2;
        break;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snakeDirection != 1) 
      {
        snakeDirection = 3;
        break;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snakeDirection != 3) 
      {
        snakeDirection = 1;
        break;
      }        
    }

    moveSnake();
    addFruit();
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
    if (Board[i]->type != 1) {
      Board[i]->type = 0;
    }
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

void createSnake(int x, int y, int size)
{
  SnakeTail = new SnakePart(x, y, NULL); 
  SnakePart *lastMadeSnakePart = SnakeTail;
  int i;

  for (i = 0; i < size; i++) {
    SnakePart *newSnakePart = new SnakePart(x, y - i + 1, lastMadeSnakePart);
    lastMadeSnakePart = newSnakePart;
  }

  SnakeHead = lastMadeSnakePart;
}

void moveSnake()
{
  switch (snakeDirection) {
    case 0:
      extendSnake(0, -1);
      break;
    case 2:
      extendSnake(0, 1);
      break;
    case 3:
      extendSnake(-1, 0);
      break;
    case 1:
      extendSnake(1, 0);
      break;
    default:
      break;
  }
}

int extendSnake(int x, int y)
{
  if (
    SnakeHead->x + x > WIDTH - 1 || 
    SnakeHead->x + x < 0 ||
    SnakeHead->y + y > HEIGHT - 1||
    SnakeHead->y + y < 0 ||
    getSquare(SnakeHead->x + x, SnakeHead->y + y)->type == 2
    ) 
  {
    window.close();
    printf("GAME OVER\nSCORE: %d\n", score);
    return 0;
  }

  if (getSquare(SnakeHead->x + x, SnakeHead->y + y)->type == 0) {
    SnakePart *currentSnakePart = SnakeHead;
    while (1) {
      if (currentSnakePart->next->next == NULL) {
        currentSnakePart->next = NULL;
        SnakeTail = currentSnakePart;
        break;
      }
      currentSnakePart = currentSnakePart->next;
    }
  } else if (getSquare(SnakeHead->x + x, SnakeHead->y + y)->type == 1) {
    score++;
  }

  SnakePart *newHead = new SnakePart(SnakeHead->x + x, SnakeHead->y + y, SnakeHead);
  SnakeHead = newHead;
}

void addFruit()
{
  if (std::rand() % 30 == 1) {
    int randomX = std::rand() % WIDTH;
    int randomY = std::rand() % HEIGHT;
    Board[randomY * WIDTH + randomX]->type = 1;
  }
}
