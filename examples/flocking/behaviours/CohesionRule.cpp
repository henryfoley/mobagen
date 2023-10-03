#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  Vector2f combinedPos = Vector2f(0,0);
  if (!neighborhood.empty())
  {
    // find center of mass
    for (auto i : neighborhood)
    {
      combinedPos += i->getPosition();
    }

    Vector2f centerOfMass = combinedPos/float(neighborhood.size());

    cohesionForce = centerOfMass - boid->getPosition();

    cohesionForce = cohesionForce/boid->getDetectionRadius();

    if (cohesionForce.getMagnitude() <= boid->getDetectionRadius())
    {
      return cohesionForce;
    }
    else
    {
      cohesionForce = Vector2f::zero();
    }
  }
  return 2*cohesionForce/boid->getDetectionRadius();
}