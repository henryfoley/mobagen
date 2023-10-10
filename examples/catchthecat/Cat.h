#ifndef CAT_H
#define CAT_H

#include "Agent.h"

class Cat : public Agent {
public:
  explicit Cat() : Agent(){};
  Point2D Move(World*) override;
  Point2D Seek(World*);
  Point2D GenerateTarget(World*);
};

#endif  // CAT_H
