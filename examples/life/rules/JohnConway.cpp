#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {

  for(int i = 0; i<world.SideSize(); i++)
  {
    for(int j = 0; j<world.SideSize(); j++)
    {
      Point2D point = Point2D(i,j);
      int neighbors = CountNeighbors(world, point);
      bool isAlive = world.Get(point);
      //world.SetNext(point, isAlive);
      //rules go here
      //Get gets from the current buffer
      //Set sets to the next buffer
      //Rules 1 and 3
      if (isAlive && neighbors<2 || neighbors>3)
      {
        world.SetNext({i,j},false);
      }
      //Rule 4
      if(!isAlive && neighbors == 3)
      {
        world.SetNext({i,j},true);
      }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int count = 0;
  const int boardSize = world.SideSize();

  for (int i = -1; i <= 1; i++)
  {
    for(int j = -1; j <=1; j++)
    {
      int x = i + point.x;
      int y = j + point.y;
      bool isAlive = world.Get(Point2D(x,y));
      if((x >= 0 && x < boardSize && y >= 0 && y < boardSize)
          && (i!=0 || j!=0) && isAlive)
      {
        count++;
      }
    }
  }
  return count;
}