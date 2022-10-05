#include "player.h"

Player::Player(Texture texture, int x, int y, int x_limit, int y_limit)
{
    m_texture = texture;
    m_x = x;
    m_y = y;

    m_x_limit = x_limit;
    m_y_limit = y_limit;
}

void Player::render(SDL_Renderer* renderer)
{
    m_texture.render(m_x, m_y, renderer);
}

void Player::handle_events(SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_DOWN: m_velocity_y += MAX_VELOCITY; break;
            case SDLK_UP: m_velocity_y -= MAX_VELOCITY; break;
            default: break;
        }
    }
    else if(event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_DOWN: m_velocity_y -= MAX_VELOCITY; break;
            case SDLK_UP: m_velocity_y += MAX_VELOCITY; break;
            default: break;
        }
    }
}

void Player::move()
{
    if(m_velocity_y > 0)
    {
        if(m_y + m_velocity_y + m_texture.get_height() < m_y_limit)
        {
            m_y += m_velocity_y;
        }
        else
        {
            m_y = m_y_limit - m_texture.get_height();
        }
    }
    else if(m_velocity_y < 0)
    {
        if(m_y + m_velocity_y > 0)
        {
            m_y += m_velocity_y;
        }
        else
        {
            m_y = 0;
        }
    }
}