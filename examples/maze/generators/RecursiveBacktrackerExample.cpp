#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  if(stack.empty())
  {
    //random start point
    stack.push_back({0,0});
  }
  else
  {

  }
  //Iterate through visitables

  //Gets rid of wall
  w->SetNorth();
return 0;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}
Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[x][y]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  //Check Up, Down, Left, Right to see if they are visitable
  //Check if Neighbors are within world space

  //Check if neighbors have been visited

  //If neighbor is visitable add it to the visitables vector



  //Point above
  if(!visited[p.Up().x][p.Up().y] && p.Up().y>=-sideOver2)
  {
    visitables.push_back(p.Up());
  }
  //Point below
  if(!visited[p.Down().x][p.Down().y] && p.Down().y<=sideOver2)
  {
    visitables.push_back(p.Down());
  }
  //Point to the left
  if(!visited[p.Left().x][p.Left().y] && p.Left().x>=-sideOver2)
  {
    visitables.push_back(p.Left());
  }
  //Point to the right
  if(!visited[p.Right().x][p.Right().y] && p.Right().x<=sideOver2)
  {
    visitables.push_back(p.Right());
  }
  return visitables;
}
