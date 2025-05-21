#include "Input.h"

void Input::Response(HWND hWnd) {
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    Mdx = pt.x - Mx;
    Mdy = pt.y - My;
    Mx = pt.x;
    My = pt.y;

    memcpy(OldKeys, Keys, 256);
    GetKeyboardState(Keys);
    for (INT i = 0; i < 256; i++)
    {
        Keys[i] >>= 7;
        KeysClick[i] = !OldKeys[i] && Keys[i];
    }

}