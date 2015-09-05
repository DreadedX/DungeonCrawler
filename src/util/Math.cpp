#include "Standard.h"

float Math::pointAngle(glm::vec4 position1, glm::vec4 position2) {

    // TODO: Check if this still works with other scales
    float dx = position2.x - position1.x;
    float dy = position1.y - position2.y;

    // #define TYPE 360
    #define TYPE 2*3.1415
    float angle = atan2(dy, dx) * (TYPE/(2*3.1415));

    return (angle < 0 ? angle+TYPE : angle);
}
