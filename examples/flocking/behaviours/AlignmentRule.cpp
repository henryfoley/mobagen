#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood
  if (!neighborhood.empty())
  {
    for (auto i : neighborhood)
    {
      averageVelocity += i->getVelocity();
    }

    averageVelocity = averageVelocity/float(neighborhood.size());
  }
  return Vector2f::normalized(averageVelocity);
}