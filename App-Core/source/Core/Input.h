#pragma once
#include "Core/Base.h"
#include "Core/KeyCodes.h"

#include <glm/vec2.hpp>

namespace Core
{
    enum InputAxis
    {
        INPUT_AXIS_HORIZONTAL = 0,
        INPUT_AXIS_VERTICAL,
    };

    struct InputMouseState
    {
        glm::vec2 position;
        u32 buttonsHeld[MOUSE_BUTTON_COUNT];
        u32 buttonsClicked[MOUSE_BUTTON_COUNT];
    };

    struct InputKeyboardState
    {
        bool keysHeld[KEY_COUNT];
        bool keysPressed[KEY_COUNT];
    };

    struct InputState
    {
        InputMouseState mouse;
        InputKeyboardState keyboard;
    };

    bool IsMouseDown(MouseButton button);
    bool IsMouseClicked(MouseButton button);
    bool IsKeyDown(u32 scancode);
    bool IsKeyPressed(u32 scancode);
    float GetInputAxis(InputAxis axis);
    float GetInputAxisAlt(InputAxis axis);

    extern InputState Input;
}
