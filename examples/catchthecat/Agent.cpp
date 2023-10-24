#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <map>
#include "World.h"

using namespace std;
/*std::vector<Point2D> Agent::generatePath(World* world){
  unordered_map<Point2D, Point2D> cameFrom; // to build the flowfield and build the path
  queue<Point2D> frontier; // to store next ones to visit
  unordered_set<Point2D> frontierSet; // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited; // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = world->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE; // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()){
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
      // for every neighbor set the cameFrom
      // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move

    return path;
}*/

vector<Point2D> Agent::generatePath(World* world)
{
  auto catPos = world->getCat();
  std::queue<Point2D> frontier;
  std::unordered_set<Point2D> frontierSet;
  std::unordered_set<Point2D> visited;
  std::map<int, std::map<int,Point2D>> cameFrom;
  std::vector<Point2D> path;
  cameFrom[catPos.y][catPos.x] = Point2D(0,0);

  //Add Cat's initial position to the open list and marked visited
  frontier.push(catPos);
  visited.insert(catPos);
  frontierSet.insert(catPos);

  Point2D ExitPoint = Point2D(INT_MAX, INT_MAX);

  //BFS Algorithm
  while(!frontier.empty()) {
    auto current = frontier.front();
    frontier.pop();
    frontierSet.erase(current);

    // If cat wins on space then break the loop
    if (world->catWinsOnSpace(current)) {
      ExitPoint = current;
      break;
    }
    // If current neighbor is valid, is not blocked,
    // is not cat, and has not been visited, add to queue and
    // record where it came from

    auto neighbors = world->neighbors(current);
    for (const auto& neighbor : neighbors) {
      if (world->isValidPosition(neighbor)             // Is on Map
          && !world->getContent(neighbor)              // Isn't Blocked
          && neighbor != world->getCat()                  // Is not cat
          && !frontierSet.contains(neighbor)       // Isn't on the frontier
          && !visited.contains(neighbor))          // Hasn't already been visited
      {
        frontier.push(neighbor);                      // Add neighbor to Queue
        frontierSet.insert(neighbor);                 // Add neighbor to frontier
        visited.insert(neighbor);                     // Add neighbor to visited
        cameFrom[neighbor.y][neighbor.x] = current;       // Record root

        if (world->catWinsOnSpace(neighbor)) {
          ExitPoint = neighbor;
          break;
        }
      }
    }
  }
  //Backtracking
  if(ExitPoint != Point2D(INT_MAX, INT_MAX)){
      while(ExitPoint != catPos) {
        path.push_back(ExitPoint);
        ExitPoint = cameFrom[ExitPoint.y][ExitPoint.x];
      }
  }
  return path;
}

struct AStarNode{
  Point2D pos;
  float accumulatedCost;
  float heuristic;
  bool operator < (const AStarNode& n) const{
      return this->accumulatedCost + this->heuristic > n.accumulatedCost + n.heuristic;
  }
};


}

vector<Point2D> Agent::generatePath(World* world)
{
  const auto catPos = world->getCat();
  vector<Point2D> path;
  priority_queue<AStarNode> frontier;
  std::map<int, std::map<int,Point2D>> cameFrom;

  Point2D exitPoint = catPos;
  frontier.push({catPos, 0, world.})
  cameFrom[catPos.y][catPos.x] = Point2D(0,0);
}