class SnakePart
{
public:
  int x;
  int y;
  SnakePart *next;

  SnakePart(int x, int y, SnakePart *next);
};

SnakePart::SnakePart(int x, int y, SnakePart *next)
{
  this -> x = x;
  this -> y = y;
  this -> next = next;
}