# include "Standard.h"

int Randomizer::random(long *seed) {

    *seed = (*seed * 32719 + 3) % 32749;

    return *seed + 1;
}

int Randomizer::random(int max, long *seed) {

    return ((random(seed)-1) % max) + 1;
}
