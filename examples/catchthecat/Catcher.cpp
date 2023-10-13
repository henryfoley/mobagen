#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  std::vector<Point2D> path = Agent::generatePath(world);
  if(!path.empty()){
    return path.front();
  }
  for (;;) {
    auto neighbors = world->neighbors(world->getCat());
    int index = Random::Range(0,neighbors.size());
    Point2D p = neighbors[index];
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) {
      return p;
    }
  }
}

Point2D Catcher::Catch(World* world){

  //Easy Solution
      //Conduct a Breadth First Search Algorithm from the cat
      //Whatever the last point is place a blocker
  std::vector<Point2D> path = Agent::generatePath(world);
  return path.front();
  //Complex Solution
      //Give weights to each position that the cat may take
      //Score corresponds to the amount of moves it would take for the cat to reach
      //Calculate number of potential routes
      //Block routes based on amount of moves it takes to get to them
          //Routes with the least amount of moves gets blocked first


  //Do these solutions if the cat has a route to follow
    //If no route then place nodes by the cat
}