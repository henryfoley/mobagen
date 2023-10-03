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
      world.SetNext(point, isAlive);
      if(isAlive){
        if(neighbors<2 || neighbors>3){
          world.SetNext({i,j},false);
        }
        if(neighbors==2 || neighbors==3) {
          world.SetNext({i,j},true);
        }
      }
      else
      {
        if(neighbors == 3){
          world.SetNext({i,j},true);
        }
      }
    }
  }
}

int JohnConway::CountNeighbors(World& w, Point2D p) {
    return w.Get(p.Up()) +
         w.Get(p.Right().Up()) +
         w.Get(p.Right()) +
         w.Get(p.Right().Down()) +
         w.Get(p.Down()) +
         w.Get(p.Left().Down()) +
         w.Get(p.Left()) +
         w.Get(p.Left().Up());
}