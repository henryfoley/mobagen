#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <queue>
#include <map>
#include <unordered_set>

Point2D Cat::Move(World* world) {
  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();

  //If nowhere to go, use random position
  switch (rand) {
    case 0:
      return World::NE(pos);
    case 1:
      return World::NW(pos);
    case 2:
      return World::E(pos);
    case 3:
      return World::W(pos);
    case 4:
      return World::SW(pos);
    case 5:
      return World::SE(pos);
    default:
      throw "random out of range";
  }
}

/*Point2D Cat::Seek(World* world)
{
  auto catPos = world->getCat();
  const int NUM_POTENTIAL_DIRECTIONS = 6;
  const int movementCost = 1;
  int heuristic = 0;
  int distanceToTarget = 0;
  std::priority_queue<Point2D> openList;
  std::priority_queue<Point2D> closedList;
  std::vector<Point2D> visitablePoints;

  //Add Cat's initial position to the open list
  openList.push(catPos);

  while(!openList.empty())
  {
    openList.pop();
    closedList.push(catPos);

    //Calculate number of options cat has
    for(int i = 0; i < World::neighbors(closedList.top()).size(); i++){
      Point2D currentNeighbor = World::neighbors(closedList.top())[i];
      // todo:If current neighbor is not blocked add it to visitable points
      if(World::isValidPosition(currentNeighbor)){
        visitablePoints.push_back(currentNeighbor);
      }
    }

    for(int i = 0; i < visitablePoints.size(); i++){
      // todo:Check if visitable point is in the closed list, if so ignore it
      /*for(int j = 0; j < openList.size(); j++){
        if(visitablePoints[i] == openList[j]){
          break;
        }
      // todo:Check if visitable point is in the open list, if not add it
      }
    }
    //Calculate Heuristic
    // todo:Get closest distance from grid
    Point2D target = Cat::GenerateTarget(world);
    distanceToTarget = abs(catPos.x-target.x) + abs(catPos.y-target.y);
    heuristic = movementCost + distanceToTarget;

    // todo:Find the node with lowest heuristic
    for()
    {

    }
  }


  //Placeholder
  return World::NE(catPos);
}*/

Point2D Cat::GenerateTarget(World* world)
{
  auto catPos = world->getCat();
  std::queue<Point2D> queue;
  std::unordered_set<Point2D> visited;
  std::map<int, std::map<int,Point2D>> cameFrom;
  cameFrom[catPos.y][catPos.x] = Point2D(0,0);

  //Add Cat's initial position to the open list and marked visited
  queue.push(catPos);
  visited.insert(catPos);

  //BFS Algorithm
  while(!queue.empty()){
    auto current = queue.front();
    queue.pop();

    //If cat wins on space then break the loop
    if(world->catWinsOnSpace(current)){
      break;
    }

    //If current neighbor is valid, is not blocked,
    //is not cat, and has not been visited, add to queue and
    //record where it came from

    // todo:Is neighbor.y the right key value for cameFrom.contains()?
    auto neighbors = world->neighbors(current);
    for(const auto & neighbor : neighbors){
      if(world->isValidPosition(neighbor) &&
          world->getContent(neighbor)     &&
          neighbor != world->getCat()        &&
          !cameFrom.contains(neighbor.y)){
        queue.push(neighbor);
        cameFrom[neighbor.y][neighbor.x] = current;
      }
    }

    //Backtracking
    std::vector<Point2D> path;
    while(current != catPos) {
      path.push_back(current);
      current = cameFrom[current.y][current.x];
    }
  }
}