class Square 
{
public:
  int type;
  int x;
  int y;

  Square(int type, int x, int y);
};

Square::Square(int type, int x, int y)
{
  this -> type = type;
  this -> x = x;
  this -> y = y;
}