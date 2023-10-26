#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  const Color32 greenColor = Color::Green;
  const Color32 redColor = Color::Red;
  const Color32 darkRedColor = Color::DarkRed;

  auto currentPoint = randomStartPoint(w);

  //For last step duration
  if(stack.empty() && currentPoint == Point2D{INT_MAX, INT_MAX}) {
    return false; // stop condition
  }
  if(stack.empty()) { //For starting
    w->SetNodeColor(currentPoint,greenColor);
    stack.push_back(currentPoint);
    return true;
  }

  currentPoint = stack.back();

  //Set Current Point to visited and get its Neighbors
  visited[currentPoint.x][currentPoint.y] = true;
  w->SetNodeColor(currentPoint, redColor);
  auto currentNeighbors = getVisitables(w,currentPoint);

  //Get delta of the point
  //Next - current
  // If delta x is positive break the east wall from the current
  // If delta x is negative break the west wall from the current
  // If delta y is positive break the north wall from the current
  // If delta y is negative break the south wall from the current

  if (!currentNeighbors.empty()){
    int random = Random::Range(0, currentNeighbors.size()-1);
    Point2D randomNeighbor = currentNeighbors[random];
    w->SetNodeColor(randomNeighbor, greenColor);
    Point2D delta = randomNeighbor - currentPoint;

    if(delta.x > 0 && w->GetEast(currentPoint)){
      //Gets rid of East wall
      w->SetEast(currentPoint,false);
    }
    if(delta.x < 0 && w->GetWest(currentPoint)){
      //Gets rid of West wall
      w->SetWest(currentPoint,false);
    }
    if(delta.y > 0 && w->GetNorth(currentPoint)){
      //Gets rid of North wall
      w->SetNorth(currentPoint,false);
    }
    if(delta.y < 0 && w->GetSouth(currentPoint)){
      //Gets rid of South wall
      w->SetSouth(currentPoint,false);
    }
    //Add Random Neighbor to Stack
    stack.push_back(randomNeighbor);
  }
  else{
    //Remove Last Element
    stack.pop_back();
    w->SetNodeColor(currentPoint, darkRedColor);
  }
  return true;
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

  //Point above
  if(p.Up().y>=-sideOver2 && !visited[p.Up().x][p.Up().y]){
    visitables.push_back(p.Up());
  }
  //Point below
  if(p.Down().y<=sideOver2 && !visited[p.Down().x][p.Down().y]){
    visitables.push_back(p.Down());
  }
  //Point to the left
  if(p.Left().x>=-sideOver2 && !visited[p.Left().x][p.Left().y]){
    visitables.push_back(p.Left());
  }
  //Point to the right
  if(p.Right().x<=sideOver2 && !visited[p.Right().x][p.Right().y]){
    visitables.push_back(p.Right());
  }
  return visitables;
}
