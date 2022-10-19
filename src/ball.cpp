#include "ball.h"

Ball::Ball(Texture texture, int x, int y, int window_width, int window_height)
{
    m_texture = texture;
    m_x = x;
    m_y = y;

    m_x_limit = window_width;
    m_y_limit = window_height;

    m_collision_box = {x, y, texture.get_width(), texture.get_height()};
    m_velocity_x = INITIAL_VELOCITY;
}

void Ball::render(SDL_Renderer* renderer)
{
    m_texture.render(m_x, m_y, renderer);
}

void Ball::move(std::unordered_map<std::string, Player> players)
{
    m_x += m_velocity_x;
    m_y += m_velocity_y;

    // Check x limits
    if(m_x < 0 || m_x > m_x_limit)
    {
        reset_movement(m_x_limit/2, m_y_limit/2);
    }
    // Check y limits
    else if(m_y < 0 || m_y > m_y_limit)
    {
        m_velocity_y = -1*m_velocity_y;
        m_y += 2*m_velocity_y;
    }
    // Check collisions with players
    for(auto& kv : players){
        Player& player = kv.second;
        SDL_Rect box = player.get_box();
        int velocity = player.get_y_velocity();

        if(check_collision(m_collision_box, box))
        {
            m_velocity_x = m_velocity_x < 0 ? MAX_VELOCITY : -MAX_VELOCITY;
            m_velocity_y = -1*m_velocity_y + velocity;
            m_x += 2*m_velocity_x;
            m_y += 2*m_velocity_y;
        }
    }
    m_collision_box.x = m_x;
    m_collision_box.y = m_y;
}

void Ball::reset_movement(int x, int y)
{
    m_x = x;
    m_y = y;

    m_velocity_x = INITIAL_VELOCITY;
    m_velocity_y = 0;

    m_collision_box.x = x;
    m_collision_box.y = y;
}

int Ball::get_x()
{
    return m_x;
}

int Ball::get_y()
{
    return m_y;
}