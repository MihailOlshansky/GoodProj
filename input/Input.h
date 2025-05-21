#pragma once
#include "Dev.h"

class Input {
public:
    BYTE
        Keys[256],           /* Current key states */
        OldKeys[256],        /* Previous frame key states */
        KeysClick[256];      /* Click key flags */
    INT
        Mx, My,              /* Mouse cursor position */
        Mz,                  /* Mouse wheel state*/
        Mdx, Mdy, Mdz;       /* Delta values of mouse axes */

    Input() = default;

    void Response(HWND hWnd);

    void UpdateWheel(int newZ)
    {
        Mdz = newZ - Mz;
        Mz = newZ;
    }

    ~Input() = default;
};

