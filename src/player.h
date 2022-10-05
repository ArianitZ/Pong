#ifndef PLAYER_H
#define PLAYER_H

#include "texture.h"
#include "renderable.h"

class Player : public IRenderable
{   
    public:
        // Maximum velocity of player
        static const int MAX_VELOCITY{5};

        Player(Texture texture, int x, int y, int x_limit, int y_limit);

        void render(SDL_Renderer* renderer);
        void handle_events(SDL_Event& event);
        void move();

    private:
        Texture m_texture{};
        int m_x{0};
        int m_y{0};

        int m_x_limit{0};
        int m_y_limit{0};
        
        int m_velocity_x{0};
        int m_velocity_y{0};
};

#endif