#ifndef BALL_H
#define BALL_H
#include <unordered_map>
#include "texture.h"
#include "renderable.h"
#include "player.h"
#include "support.h"

class Ball : IRenderable
{
    public:
        static const int INITIAL_VELOCITY{2};
        static const int MAX_VELOCITY{4};

        Ball(Texture texture, int x, int y, int window_width, int window_height);

        void render(SDL_Renderer* renderer);
        void move(std::unordered_map<std::string, Player> players);

        int get_x();
        int get_y();

    private:
        Texture m_texture{};
        // TODO: Use movement struct for position and velocity?
        int m_x{0};
        int m_y{0};

        int m_x_limit{0};
        int m_y_limit{0};

        SDL_Rect m_collision_box{0,0,0,0};

        int m_velocity_x{0};
        int m_velocity_y{0};

        void reset_movement(int x, int y);
};

#endif