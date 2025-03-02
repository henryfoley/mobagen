#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;
  int countCloseFlockmates = 0;

// todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  if (!neighborhood.empty())
  {
    Vector2f position = boid->transform.position;
    for (auto i : neighborhood)
    {
      Vector2f distance = position - i->getPosition();
       if(distance.getMagnitude() > 0 && distance.getMagnitude() <= desiredDistance)
       {
         Vector2f difference = boid->getPosition() - i->getPosition();
         difference.normalized();
         distance /= desiredDistance;
         separatingForce = distance.normalized()/distance.getMagnitude();
         countCloseFlockmates ++;
       }
    }

    if(countCloseFlockmates > 0)
    {
       separatingForce/=countCloseFlockmates;
    }

  }
  // todo: find and apply force only on the closest mates


  separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
