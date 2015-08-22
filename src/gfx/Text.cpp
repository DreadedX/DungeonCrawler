# include "Standard.h"

namespace Text {

    void init() {

	FT_Library ft;
	if(FT_Init_FreeType(&ft)) {

	    Log::print("Could not load FreeType library", ERROR);
	    Game::stop(ERROR_FT);
	}
    }

    void render() {
    }
}
