#ifndef PLAYER_H
#define PLAYER_H

#include "texture.h"
#include "renderable.h"

class Player : public IRenderable
{   
    public:
        // Maximum velocity of player
        static const int MAX_VELOCITY{5};
        Player();
        Player(Texture texture, int x, int y, int y_limit);

        void render(SDL_Renderer* renderer);
        void handle_events(SDL_Event& event);
        void move();
        void slow_move(int y_velocity);
        
        void set_score(int score);
        
        SDL_Rect get_box();
        int get_y_velocity();
        int get_score();
        

    private:
        Texture m_texture{};
        int m_x{0};
        int m_y{0};
        int m_score{0};

        SDL_Rect m_collision_box{};

        int m_y_limit{0};

        int m_velocity_y{0};
};

#endif