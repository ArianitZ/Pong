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
        // Returns true if ball goes outside game window.
        bool move(std::unordered_map<std::string, Player> players);
        void reset_movement(int x, int y);

        int get_x();
        int get_y();
        int get_y_velocity();

    private:
        Texture m_texture{};

        int m_x{0};
        int m_y{0};
        int m_x_limit{0};
        int m_y_limit{0};

        SDL_Rect m_collision_box{0,0,0,0};

        int m_velocity_x{0};
        int m_velocity_y{0};

        int compute_y_velocity_factor(SDL_Rect player_box);
};

#endif