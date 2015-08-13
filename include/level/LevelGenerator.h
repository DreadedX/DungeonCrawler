#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

namespace LevelGenerator {

    uint *generate(vec2 size);

    uint getDirectionTile(uint direction);

    enum {
	genEmpty = 0,
	genDirNorth = 1,
	genDirEast = 2,
	genDirSouth = 4,
	genDirWest = 8,
	genDirNone = 16,
	genFilled = 32,
	genRoom = 64,
	genDoor = 128,
	genExit= 256
    };

};

#endif

