# include "Standard.h"

namespace Camera {

    Player *player = nullptr;

    vec4 positionLast = vec4(0, 0, 0, 0);
    vec4 toMove       = vec4(0, 0, 0, 0);

    float tweenFloat = 0.1 * VT;
    mat4 tween       = scale(IDENTITY, vec3(tweenFloat, tweenFloat, 1));

    void init() {

	// Get a pointer to the player
	player = Level::getPlayer();
	positionLast = player->position;
	Render::move(positionLast);
    }

    void tick() {

	// Calculate the position delta
	toMove += player->position - positionLast;

	// NOTO: This is only here for testing puposes
	// Zoom in when Q is pressed
	if(Input::isPressed(GLFW_KEY_Q)) {

	    toMove.z -= 1.0f * VT;
	}

	// Zoom out when E is pressed
	if(Input::isPressed(GLFW_KEY_E)) {

	    toMove.z += 1.0f * VT;
	}

	// Tell the renderer to adjust the world matrix
	Render::move(toMove * tween);

	// Subtract the moved amount from the toMove amount
	toMove -= toMove * tween;

	// Update the last position to the players current position
	positionLast = player->position;
    }
}
