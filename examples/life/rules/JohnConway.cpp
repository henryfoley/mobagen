#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {

  for(int y = 0; y<world.SideSize(); y++)
  {
    for(int x = 0; x<world.SideSize(); x++)
    {
      Point2D point = Point2D(x,y);
      int neighbors = CountNeighbors(world, point);
      bool isAlive = world.Get(point);
      //world.SetNext(point, isAlive);
      //rules go here
      //Get gets from the current buffer
      //Set sets to the next buffer
      //Rules 1 and 3


      if (isAlive && neighbors< 2 || neighbors>3)
      {
        world.SetNext({x,y},false);
      }
      //Rule 4
      if(!isAlive && neighbors == 3)
      {
        world.SetNext({x,y},true);
      }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int count = 0;
  int boardSize = world.SideSize();

  for (int a = -1; a <= 1; a++)
  {
    for(int b = -1; b <=1; b++)
    {
      bool isAlive = world.Get(Point2D(a, b));
      if((a + point.x >= 0 && a + point.x < boardSize && b + point.y >= 0 && b + point.y < boardSize )
          && (a!=0 || b!=0) && isAlive)
      {
        count++;
      }
    }
  }
  return count;


}
