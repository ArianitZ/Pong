#include "player.h"

// TODO: Only needed for intializing map. Change this?
Player::Player()
{
    m_texture = Texture();
    m_x = 0;
    m_y = 0;
    m_score = 0;
}

Player::Player(Texture texture, int x, int y, int y_limit)
{
    m_texture = texture;
    m_x = x;
    m_y = y;
    m_score = 0;

    m_collision_box = {x, y, texture.get_width(), texture.get_height()};
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
        if(m_y + m_velocity_y + m_collision_box.h < m_y_limit)
        {
            m_y += m_velocity_y;
        }
        else
        {
            m_y = m_y_limit - m_collision_box.h;
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

    m_collision_box.y = m_y;
}

void Player::slow_move(int y_velocity)
{
    // Function meant for NPC. Slows down reaction of NPC by lowering the velocity of it.
    m_velocity_y = y_velocity < 0 ? y_velocity + 1 : y_velocity - 1;
    move();
}

void Player::set_score(int score)
{
    m_score = score;
}

SDL_Rect Player::get_box()
{
    return m_collision_box;
}

int Player::get_y_velocity()
{
    return m_velocity_y;
}

int Player::get_score()
{
    return m_score;
}