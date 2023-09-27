//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
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
int HexagonGameOfLife::CountNeighbors(World& w, Point2D p) {
  return w.Get(p.Up()) +
         w.Get(p.Down());
}
