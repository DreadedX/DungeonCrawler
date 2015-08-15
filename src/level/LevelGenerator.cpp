# include "Standard.h"

namespace LevelGenerator {

    struct Room {
	int x;
	int y;
	int width;
	int height;
    };

    struct Cell {
	int x;
	int y;
	byte direction;
    };

    void createRoom(uint *prototype, vec2 size, Room room);
    bool placeExit(uint *prototype, vec2 size);

    void carveMaze(uint *prototype, vec2 size, Cell cell, byte previousDirection);
    void connectMaze(uint *prototype, vec2 size);
    void sparseMaze(uint *prototype, vec2 size);

    void findRooms(uint *prototype, vec2 size);

    // static long seedLayout = time(NULL);
    static long seedLayout = 26101997;

    int mazeCounter = 0;

    uint *generate(vec2 size) {

	uint *prototype = new uint[(int)(size.x * size.y)];
	mazeCounter = 0;

	for (int i = 0; i < size.x * size.y; i++) {

	    prototype[i] = genEmpty;
	}

	// Place rooms
	for (int i = 0; i < 10000; i++) {

	    Room room = {
		Randomizer::random((int)size.x - 2, &seedLayout),
		Randomizer::random((int)size.y - 2, &seedLayout),
		// Randomizer::random(3, &seedLayout) + 1,
		// Randomizer::random(3, &seedLayout) + 1
		Randomizer::random(3, &seedLayout) + 1,
		Randomizer::random(3, &seedLayout) + 1
	    };


	    createRoom(prototype, size, room);
	}

	// Place random filled spots
	for (int i = 0; i < 200; i++) {

	    int x =Randomizer::random((int)size.x, &seedLayout) - 1;
	    int y = Randomizer::random((int)size.y, &seedLayout) - 1;

	    if (
		    (prototype[(int)(x + y * size.y)] & genRoom) == 0 &&
		    prototype[(int)(x + (y+1) * size.y)] != genFilled &&
		    prototype[(int)((x+1) + y * size.y)] != genFilled &&
		    prototype[(int)(x + (y-1) * size.y)] != genFilled &&
		    prototype[(int)((x-1) + y * size.y)] != genFilled
	       ) {

		// TODO: Add seperate filled space tile
		prototype[(int)(x + y * size.y)] = genFilled;
	    }

	}

	// Maze carver
	int cx = 0;
	int cy = 0;
	// while (prototype[(int)(cx + cy * size.x)] == genEmpty) {

	    cx =Randomizer::random((int)size.x, &seedLayout) - 1;
	    cy = Randomizer::random((int)size.y, &seedLayout) - 1;
	// }

	Cell startCell = {cx, cy, 0};
	carveMaze(prototype, size, startCell, 0);

	// Randomly connect maze parts
	for (int i = 0; i < 100; i++) {
	    
	    connectMaze(prototype, size);
	}

	// Remove dead ends
	for (int i = 0; i < 100000; i++) {

	    if (mazeCounter > 250) {

		sparseMaze(prototype, size);
	    }
	}

	findRooms(prototype, size);

	// Place exit
	// while(!placeExit(prototype, size));
	
	return prototype;

    }

    void createRoom(uint *prototype, vec2 size, Room room) {

	int requiredSpace = Randomizer::random(5, &seedLayout);

	for (int y = room.y - requiredSpace; y < room.y + room.height + requiredSpace + 1; y++) {

	    for (int x = room.x - requiredSpace; x < room.x + room.width + requiredSpace + 1; x++) {

		if (y < 0 || y > (int)size.y || x < 0 || x > (int)size.x || prototype[(int)(x + y * size.x)] != genEmpty) {

		    return;
		}
	    }
	}

	for (int y = room.y;  y < room.y + room.height; y++) {

	    for (int x = room.x; x < room.x + room.width; x++) {

		if (y == room.y && x == room.x) {

		    prototype[(int)(x + y * size.y)] = genRoom | genDoor;
		} else {

		    prototype[(int)(x + y * size.y)] = genRoom;
		}
	    }
	}
    }

    bool placeExit(uint *prototype, vec2 size) {

	int x = Randomizer::random((int)size.x, &seedLayout) - 1;
	int y =Randomizer::random((int)size.y, &seedLayout) - 1;

	if ((prototype[(int)(x + y * size.x)] == genRoom)) {

	    prototype[(int)(x + y * size.x)] = genRoom | genExit;

	    return true;
	}

	return false;
    }

    void carveMaze(uint *prototype, vec2 size, Cell cell, byte previousDirection) {

	std::vector<Cell> neighbourCells;
	uint directions = previousDirection;

	Cell north = {cell.x, cell.y+1, genDirNorth};
	neighbourCells.push_back(north);

	Cell east = {cell.x+1, cell.y, genDirEast};
	neighbourCells.push_back(east);

	Cell south = {cell.x, cell.y-1, genDirSouth};
	neighbourCells.push_back(south);

	Cell west = {cell.x-1, cell.y, genDirWest};
	neighbourCells.push_back(west);

	srand(Randomizer::random(&seedLayout));

	std::random_shuffle(neighbourCells.begin(), neighbourCells.end());

	prototype[(int)(cell.x + cell.y * size.y)] = genDirNone;

	for (Cell nextCell : neighbourCells) {

	    if (nextCell.y >= 0 && nextCell.y < (int)size.y && nextCell.x >= 0 && nextCell.x < (int)size.x) {

		byte oppositeDirection = 0;
		if (nextCell.direction < 4) {

		    oppositeDirection = nextCell.direction * 4;
		} else {

		    oppositeDirection = nextCell.direction / 4;
		}

		if (prototype[(int)(nextCell.x + nextCell.y * size.x)] == genEmpty) {

		    directions |= nextCell.direction;

		    mazeCounter++;

		    carveMaze(prototype, size, nextCell, oppositeDirection);
		}

		if ((prototype[(int)(nextCell.x + nextCell.y * size.x)] & genDoor) == genDoor) {

		    directions |= nextCell.direction;
		}
	    }
	}

	prototype[(int)(cell.x + cell.y * size.y)] = directions;
    }

    void connectMaze(uint *prototype, vec2 size) {

	int x = Randomizer::random((int)size.x, &seedLayout) - 1;
	int y = Randomizer::random((int)size.y, &seedLayout) - 1;

	int direction = Randomizer::random(4, &seedLayout);

	if ((prototype[(int)(x + y * size.x)] & genRoom) != genRoom && (prototype[(int)(x + y * size.x)] & genFilled) != genFilled) {

	    if (direction == 1 && (prototype[(int)(x + (y+1) * size.x)] & genRoom) != genRoom && (prototype[(int)(x + (y+1) * size.x)] & genFilled) != genFilled && (y+1) < (int)size.y) {
		prototype[(int)(x + y * size.x)] |= genDirNorth;
		prototype[(int)(x + (y+1) * size.x)] |= genDirSouth;
	    }

	    if (direction == 2 && (prototype[(int)((x+1) + y * size.x)] & genRoom) != genRoom && (prototype[(int)((x+1) + y * size.x)] & genFilled) != genFilled && (x+1) < (int)size.x) {
		prototype[(int)(x + y * size.x)] |= genDirEast;
		prototype[(int)((x+1) + y * size.x)] |= genDirWest;
	    }

	    if (direction == 3 && (prototype[(int)(x + (y-1) * size.x)] & genRoom) != genRoom && (prototype[(int)(x + (y-1) * size.x)] & genFilled) != genFilled && (y-1) >= 0) {
		prototype[(int)(x + y * size.x)] |= genDirSouth;
		prototype[(int)(x + (y-1) * size.x)] |= genDirNorth;
	    }

	    if (direction == 4 && (prototype[(int)((x-1) + y * size.x)] & genRoom) != genRoom && (prototype[(int)((x-1) + y * size.x)] & genFilled) != genFilled && (x-1) >= 0) {

		prototype[(int)(x + y * size.x)] |= genDirWest;
		prototype[(int)((x-1) + y * size.x)] |= genDirEast;
	    }
	}
    }

    void sparseMaze(uint *prototype, vec2 size) {

	int x = Randomizer::random((int)size.x, &seedLayout) - 1;
	int y = Randomizer::random((int)size.y, &seedLayout) - 1;

	if (prototype[(int)(x + y * size.x)] == genDirNorth) {

	    prototype[(int)(x + y * size.x)] = genEmpty;
	    prototype[(int)(x + (y+1) * size.x)] ^= genDirSouth;

	    mazeCounter--;
	}

	if (prototype[(int)(x + y * size.x)] == genDirEast) {

	    prototype[(int)(x + y * size.x)] = genEmpty;
	    prototype[(int)((x+1) + y * size.x)] ^= genDirWest;

	    mazeCounter--;
	}

	if (prototype[(int)(x + y * size.x)] == genDirSouth) {

	    prototype[(int)(x + y * size.x)] = genEmpty;
	    prototype[(int)(x + (y-1) * size.x)] ^= genDirNorth;

	    mazeCounter--;
	}

	if (prototype[(int)(x + y * size.x)] == genDirWest) {

	    prototype[(int)(x + y * size.x)] = genEmpty;
	    prototype[(int)((x-1) + y * size.x)] ^= genDirEast;

	    mazeCounter--;
	}
    }

    void findRooms(uint *prototype, vec2 size) {

	for (int y = 0; y < (int)size.y; y++) {

	    for (int x = 0; x < (int)size.x; x++) {

		if (
			((prototype[(int)(x + y * size.x)] & (genDirEast | genDirSouth)) == (genDirEast | genDirSouth) || (prototype[(int)(x + y * size.x)] & genRoom) == genRoom) &&
			((prototype[(int)(x + (y-1) * size.x)] & (genDirEast | genDirNorth)) == (genDirEast | genDirNorth) || (prototype[(int)(x + (y-1) * size.x)] & genRoom) == genRoom) &&
			((prototype[(int)((x+1) + y * size.x)] & (genDirWest | genDirSouth)) == (genDirWest | genDirSouth) || (prototype[(int)((x+1) + y * size.x)] & genRoom) == genRoom) &&
			((prototype[(int)((x+1) + (y-1) * size.x)] & (genDirWest | genDirNorth)) == (genDirWest | genDirNorth) || (prototype[(int)((x+1) + (y-1) * size.x)] & genRoom) == genRoom)
		   ) {

		    prototype[(int)(x + y * size.x)] = genRoom; 
		    prototype[(int)(x + (y-1) * size.x)] = genRoom;
		    prototype[(int)((x+1) + y * size.x)] = genRoom;
		    prototype[(int)((x+1) + (y-1) * size.x)] = genRoom;
		}
	    }

	}

    }

    uint getDirectionTile(uint direction) {

	switch (direction) {

	    case genEmpty:
		return 1;
		break;

	    case genFilled:
		// return 0;
		return 1;
		break;

	    case genRoom:
		return 2;
		break;

	    case genRoom | genDoor:
		return 12;
		break;

	    case genRoom | genExit:
		return 4;
		break;

	    case genDirNorth:
		return 14;
		break;

	    case genDirEast:
		return 15;
		break;

	    case genDirSouth:
		return 16;
		break;

	    case genDirWest:
		return 17;
		break;

	    case genDirNorth | genDirEast:
		return 18;
		break;

	    case genDirNorth | genDirSouth:
		return 19;
		break;

	    case genDirNorth | genDirWest:
		return 20;
		break;

	    case genDirEast | genDirSouth:
		return 21;
		break;

	    case genDirEast | genDirWest:
		return 22;
		break;

	    case genDirSouth | genDirWest:
		return 23;
		break;

	    case genDirNorth | genDirEast | genDirSouth:
		return 24;
		break;

	    case genDirNorth | genDirEast | genDirWest:
		return 25;
		break;

	    case genDirNorth | genDirSouth | genDirWest:
		return 26;
		break;

	    case genDirEast | genDirSouth | genDirWest:
		return 27;
		break;

	    case genDirNorth | genDirEast | genDirWest | genDirSouth:
		return 28;
		break;
	}

	return 0;
    }

};
