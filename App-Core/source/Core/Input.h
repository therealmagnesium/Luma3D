#pragma once
#include "Core/Base.h"
#include "Core/KeyCodes.h"

#include <glm/vec2.hpp>

namespace Core
{
    // [@brief] Determines what keys return -1 and 1.
    enum InputAxis
    {
        INPUT_AXIS_HORIZONTAL = 0,
        INPUT_AXIS_VERTICAL,
    };

    /* [@brief] Holds input information about the mouse.
     * [@field] position - The position of the cursor in mouse coordinates.
     * [@field] buttonsHeld - The mouse buttons that are being held down.
     * [@field] buttonsClicked - The mouse buttons that are clicked.
     * */
    struct InputMouseState
    {
        glm::vec2 position;
        bool buttonsHeld[MOUSE_BUTTON_COUNT];
        bool buttonsClicked[MOUSE_BUTTON_COUNT];
    };

    /* [@brief] Holds input information about the keyboard.
     * [@field] keysHeld - The mouse buttons that are being held down.
     * [@field] keysPressed - The mouse buttons that are clicked.
     * */
    struct InputKeyboardState
    {
        bool keysHeld[KEY_COUNT];
        bool keysPressed[KEY_COUNT];
    };

    /* [@brief] Holds all of the input information about the mouse and keyboard.
     * [@field] mouse - The input information about the mouse.
     * [@field] keyboard - The input information about the keyboard.
     * */
    struct InputState
    {
        InputMouseState mouse;
        InputKeyboardState keyboard;
    };

    /* [@brief] Returns true if the given mouse button is held down.
     * [@param] button - The mouse button to check if being held down.
     * */
    bool IsMouseDown(MouseButton button);

    /* [@brief] Returns true only on the initial click of the mouse button.
     * [@param] button - The mouse button to check if it was clicked.
     * */
    bool IsMouseClicked(MouseButton button);

    /* [@brief] Returns true if the given key is being held down.
     * [@param] scancode - The key to check if being held down.
     * */
    bool IsKeyDown(u32 scancode);

    /* [@brief] Returns true only on the initial press of the given key.
     * [@param] scancode - The key to check if it was pressed.
     * */
    bool IsKeyPressed(u32 scancode);

    /* [@brief] Returns a signed, normalized float representing the virtual input axis.
     * [@param] axis - The axis determines which keys need to be pressed to return a value.
     * */
    float GetInputAxis(InputAxis axis);

    /* [@brief] Same as GetInputAxis([InputAxis]), but with different key bindings.
     * [@param] axis - The axis determines which keys need to be pressed to return a value.
     * */
    float GetInputAxisAlt(InputAxis axis);

    extern InputState Input;
}
