#include "object_set.h"

class TA_Fire : public TA_Object {
private:
    const double waitTime = 6;

    void updateHitbox();

    double timer = 0;
    bool flip;

public:
    using TA_Object::TA_Object;
    void load(TA_Point position, bool flip = false);
    bool update() override;
    TA_CollisionType getCollisionType() override {return TA_COLLISION_DAMAGE;}
};