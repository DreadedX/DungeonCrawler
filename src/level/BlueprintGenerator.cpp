# include "Standard.h"

uint mazePiece[][25] = {
    {
	// N
	tileWallBottomLeft, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomRight,
	tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallRightCenter
    }, {
	// E
	tileWallBottomLeft, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter,
	tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileFloor,
	tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileFloor,
	tileWallLeftCenter, tileWallSide, tileWallSide, tileWallSide, tileWallSide,
	tileWallTopLeft, tileWallTopCenter, tileWallTopCenter, tileWallTopCenter, tileWallTopCenter
    }, {
	// S
	tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	tileWallLeftCenter, tileWallSide, tileWallSide, tileWallSide, tileWallRightCenter,
	tileWallTopLeft, tileWallTopCenter, tileWallTopCenter, tileWallTopCenter, tileWallTopRight
    }, {
	// W
	tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomRight,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallRightCenter,
	    tileWallTopCenter, tileWallTopCenter, tileWallTopCenter, tileWallTopCenter, tileWallTopRight
    }, {
	// NE
	tileWallBottomLeft, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallSide,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallTopRightInner
    }, {
	// NS
	tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallRightCenter
    }, {
	// NW
	tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomRight,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileWallSide, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileWallTopLeftInner, tileFloor, tileFloor, tileFloor, tileWallRightCenter
    }, {
	// ES
	tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallBottomRightInner,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileWallLeftCenter, tileWallSide, tileWallSide, tileWallSide, tileWallSide,
	    tileWallTopLeft, tileWallTopCenter, tileWallTopCenter, tileWallTopCenter, tileWallTopCenter
    }, {
	// EW
	tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide,
	    tileWallTopCenter, tileWallTopCenter, tileWallTopCenter, tileWallTopCenter, tileWallTopCenter
    }, {
	// SW
	tileWallBottomLeftInner, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallRightCenter,
	    tileWallTopCenter, tileWallTopCenter, tileWallTopCenter, tileWallTopCenter, tileWallTopRight
    }, {
	// NES
	tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallBottomRightInner,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallSide,
	    tileWallLeftCenter, tileFloor, tileFloor, tileFloor, tileWallTopRightInner
    }, {
	// NEW
	tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter, tileWallBottomCenter,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileWallSide, tileFloor, tileFloor, tileFloor, tileWallSide,
	    tileWallTopLeftInner, tileFloor, tileFloor, tileFloor, tileWallTopRightInner
    }, {
	// NSW
	tileWallBottomLeftInner, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileWallSide, tileFloor, tileFloor, tileFloor, tileWallRightCenter,
	    tileWallTopLeftInner, tileFloor, tileFloor, tileFloor, tileWallRightCenter
    }, {
	// ESW
	tileWallBottomLeftInner, tileFloor, tileFloor, tileFloor, tileWallBottomRightInner,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide,
	    tileWallTopCenter, tileWallTopCenter, tileWallTopCenter, tileWallTopCenter, tileWallTopCenter
    }, {
	// NESW
	tileWallBottomLeftInner, tileFloor, tileFloor, tileFloor, tileWallBottomRightInner,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileFloor, tileFloor, tileFloor, tileFloor, tileFloor,
	    tileWallSide, tileFloor, tileFloor, tileFloor, tileWallSide,
	    tileWallTopLeftInner, tileFloor, tileFloor, tileFloor, tileWallTopRightInner
    }
};

uint *BlueprintGenerator::generate(uint *prototype, glm::ivec2 size, glm::ivec2 levelSize) {

    uint *blueprint = new uint[levelSize.x * levelSize.y];

    for (int i = 0; i < levelSize.x * levelSize.y; i++) {

	blueprint[i] = 0;
    }

    for (int y = 0; y < size.y; y++) {

	for (int x = 0; x < size.x; x++) {

	    for (int iy = 0; iy < 5; iy++) {

		for (int ix = 0; ix < 5; ix++) {
		    // N
		    if (prototype[x + y * size.x] == genDirNorth) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[0][ix+iy*5];
		    }

		    // E
		    if (prototype[x + y * size.x] == genDirEast) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[1][ix+iy*5];
		    }

		    // S
		    if (prototype[x + y * size.x] == genDirSouth) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[2][ix+iy*5];
		    }

		    // W
		    if (prototype[x + y * size.x] == genDirWest) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[3][ix+iy*5];
		    }

		    // NE
		    if (prototype[x + y * size.x] == (genDirNorth | genDirEast)) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[4][ix+iy*5];
		    }

		    // NS
		    if (prototype[x + y * size.x] == (genDirNorth | genDirSouth)) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[5][ix+iy*5];
		    }

		    // NW
		    if (prototype[x + y * size.x] == (genDirNorth | genDirWest)) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[6][ix+iy*5];
		    }

		    // ES
		    if (prototype[x + y * size.x] == (genDirEast | genDirSouth)) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[7][ix+iy*5];
		    }

		    // EW
		    if (prototype[x + y * size.x] == (genDirEast | genDirWest)) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[8][ix+iy*5];
		    }

		    // SW
		    if (prototype[x + y * size.x] == (genDirSouth | genDirWest)) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[9][ix+iy*5];
		    }

		    // NES
		    if (prototype[x + y * size.x] == (genDirNorth | genDirEast | genDirSouth)) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[10][ix+iy*5];
		    }

		    // NEW
		    if (prototype[x + y * size.x] == (genDirNorth | genDirEast | genDirWest)) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[11][ix+iy*5];
		    }

		    // NSW
		    if (prototype[x + y * size.x] == (genDirNorth | genDirSouth | genDirWest)) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[12][ix+iy*5];
		    }

		    // ESW
		    if (prototype[x + y * size.x] == (genDirEast | genDirSouth | genDirWest)) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[13][ix+iy*5];
		    }

		    // NESW
		    if (prototype[x + y * size.x] == (genDirNorth | genDirEast | genDirSouth | genDirWest)) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = mazePiece[14][ix+iy*5];
		    }

		    // Empty / Filled
		    if ((prototype[x + y * size.x] == genEmpty) || (prototype[(x + y * size.x)] == genFilled)) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = tileFilled;
		    }

		    if ((prototype[x + y * size.x] & genRoom) == genRoom) {
			int index = ((x*5+ix)+(y*5+iy)*levelSize.x); 
			blueprint[index] = 0;
		    }
		}
	    }
	}
    }

    delete[] prototype;

    return blueprint;
}

uint BlueprintGenerator::getTile(int type) {

    switch (type) {

	case tileFloor:
	    return 2;
	    break;

	case tileFilled:
	    return 3;
	    break;

	case tileStairLeft:
	    return 4;
	    break;

	case tileStairRight:
	    return 5;
	    break;

	case tileWallTopLeft:
	    return 9;
	    break;

	case tileWallTopRight:
	    return 10;
	    break;

	case tileWallTopCenter:
	    return 11;
	    break;

	case tileWallBottomLeft:
	    return 6;
	    break;

	case tileWallBottomRight:
	    return 7;
	    break;

	case tileWallBottomCenter:
	    return 8;
	    break;

	case tileWallLeftCenter:
	    return 12;
	    break;

	case tileWallRightCenter:
	    return 13;
	    break;

	case tileWallSide:
	    return 14;
	    break;

	case tileWallBottomLeftInner:
	    return 15;
	    break;

	case tileWallBottomRightInner:
	    return 16;
	    break;

	case tileWallTopLeftInner:
	    return 17;
	    break;

	case tileWallTopRightInner:
	    return 18;
	    break;
    }

    return 1;
}
