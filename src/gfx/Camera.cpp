# include "Standard.h"

namespace Camera {

    Entity *player;
    vec4 positionLast;
    vec4 toMove = vec4(0, 0, 0, 0);

    float tweenFloat = 0.1 * VT;
    mat4 tween = scale(IDENTITY, vec3(tweenFloat, tweenFloat, 1));

    void init() {
	player = Level::getPlayer();

	positionLast = player->position;
    }

    void tick() {
	toMove += player->position - positionLast;
	
	if(Input::isPressed(GLFW_KEY_Q)) {
	    toMove.z -= 1.0f * VT;
	}
	if(Input::isPressed(GLFW_KEY_E)) {
	    toMove.z += 1.0f * VT;
	}

	Render::move(toMove * tween);

	toMove -= toMove * tween;

	positionLast = player->position;
    }

    void render() {

    }
}
