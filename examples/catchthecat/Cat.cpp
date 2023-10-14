#include "Cat.h"
#include "World.h"

Point2D Cat::Move(World* world) {
  auto pos = world->getCat();

  // Create variable to determine if the cat has a route
  std::vector<Point2D> path = Agent::generatePath(world);
  if (!path.empty()) {
    return path.back();
  } else {
    std::vector<Point2D> neighbors = world->neighbors(pos);
    // Shuffle Neighbors
    for (int i = 0; i < neighbors.size(); i++) {
      int j = Random::Range(0, neighbors.size()-1);
      std::swap(neighbors[i], neighbors[j]);
    }
    for (auto neighbor : neighbors) {
      if (!world->getContent(neighbor)) {
        return neighbor;
      }
    }
    // If no available options
    return neighbors[0];
  }
}