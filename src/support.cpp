#include "support.h"

bool check_collision(SDL_Rect a, SDL_Rect b)
{
    int a_x_left{a.x};
    int a_x_right{a.x + a.w};
    int a_y_top{a.y};
    int a_y_bottom{a.y + a.h};

    int b_x_left{b.x};
    int b_x_right{b.x + b.w};
    int b_y_top{b.y};
    int b_y_bottom{b.y + b.h};

    if(b_x_left > a_x_right)
    {
        return false;
    }

    if(b_x_right < a_x_left)
    {
        return false;
    }

    if(b_y_top > a_y_bottom)
    {
        return false;
    }

    if(b_y_bottom < a_y_top)
    {
        return false;
    }

    return true;
}