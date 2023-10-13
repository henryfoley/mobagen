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
  std::queue<Point2D> queue;
  std::unordered_set<Point2D> visited;
  std::map<int, std::map<int,Point2D>> cameFrom;
  std::vector<Point2D> path;
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
      if(world->isValidPosition(neighbor) && //Is on Map
          world->getContent(neighbor)     && //Isn't Blocked
          neighbor != world->getCat()        && //Is not cat
          !visited.contains(neighbor)){  //Hasn't already been visited
        queue.push(neighbor);                     //Add neighbor to Queue
        visited.insert(neighbor);                 //Add neighbor to visited
        cameFrom[neighbor.y][neighbor.x] = current;   //Record root
      }
    }

    //Backtracking
    while(current != catPos) {
      path.push_back(current);
      current = cameFrom[current.y][current.x];
    }
  }
  return path;
}