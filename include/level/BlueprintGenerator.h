#ifndef BLUEPRINTGENERATOR_H
#define BLUEPRINTGENERATOR_H

namespace BlueprintGenerator {

    uint *generate(uint *prototpye, glm::ivec2 size, glm::ivec2 levelSize);

    uint getTile(int type);

};

enum {
    tileUnused = 0,

    tileFloor,
    tileFilled,

    tileStairLeft,
    tileStairRight,

    tileWallTopLeft,
    tileWallTopRight,
    tileWallTopCenter,

    tileWallBottomLeft,
    tileWallBottomRight,
    tileWallBottomCenter,

    tileWallLeftCenter,
    tileWallRightCenter,

    tileWallBottomLeftInner,
    tileWallBottomRightInner,
    tileWallTopLeftInner,
    tileWallTopRightInner,

    tileWallSide
};

#endif

