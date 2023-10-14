#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  Point2D cat = world->getCat();
  std::vector<Point2D> path = Agent::generatePath(world);
  if(!path.empty()){
    return path.front();
  }
  else{
    std::vector<Point2D> neighbors = world->neighbors(cat);
    // Shuffle Neighbors
    for (int i = 0; i < neighbors.size(); i++) {
      int j = Random::Range(0, neighbors.size()-1);
      std::swap(neighbors[i], neighbors[j]);
    }
    for (auto neighbor : neighbors) {
      if (neighbor != cat && !world->getContent(neighbor))
      {
        return neighbor;
      }
   }
   return neighbors[0];
  }
}