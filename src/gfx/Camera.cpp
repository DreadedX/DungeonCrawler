# include "Standard.h"

glm::vec4 positionLast = glm::vec4(0, 0, 0, 0);
glm::vec4 toMove       = glm::vec4(0, 0, 0, 0);

float tweenFloat = 0.1 * VT;
glm::mat4 tween       = glm::scale(IDENTITY, glm::vec3(tweenFloat, tweenFloat, 1));
PositionComponent *cPosition = nullptr;

void Camera::init() {

    // Get a pointer to the player
    cPosition = &Level::getPlayer()->getComponent<PositionComponent>();
#if not LEGACY
    positionLast = cPosition->position;
#else
    positionLast.x = cPosition->position.x - 16;
    positionLast.y = cPosition->position.y - 12;
#endif
    Render::move(positionLast);
}

void Camera::tick() {

    // Calculate the position delta
#if not LEGACY
    toMove += cPosition->position - positionLast;
#else
    toMove.x += (cPosition->position.x - 16) - positionLast.x;
    toMove.y += (cPosition->position.y - 12) - positionLast.y;
#endif

    // NOTE: This is only here for testing puposes
    if(Input::isPressed(Key::DEBUG_ZOOM_IN)) {

	toMove.z -= 1.0f * VT;
    }

    if(Input::isPressed(Key::DEBUG_ZOOM_OUT)) {

	toMove.z += 1.0f * VT;
    }

    // Tell the renderer to adjust the world matrix
    Render::move(toMove * tween);

    // Subtract the moved amount from the toMove amount
    toMove -= toMove * tween;

    // Update the last position to the players current position
#if not LEGACY
    positionLast = cPosition->position;
#else
    positionLast.x = cPosition->position.x - 16;
    positionLast.y = cPosition->position.y - 12;
#endif
}
