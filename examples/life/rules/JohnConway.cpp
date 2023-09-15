#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {

  for(int y = 0; y<world.SideSize(); y++)
  {
    for(int x = 0; x<world.SideSize(); x++)
    {
      Point2D point = Point2D(x,y);
      int neighbor = CountNeighbors(world, point);
      //rules go here
      // world.setnext({x,y}, true/false
    }
  }
  
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int boardSize = world.SideSize();
  int count = 0;
  world. ;
  point. ;
  //int pointSize = point;

  for (int a = -1; a <= 1; a++)
  {
    for(int b = -1; b <-1; b++)
    {
      if(a!=0 && b!=0 && world.Get({p.b+b, p.a+a}))
      {
        count++;
      }
    }
  }
  return count;


}
