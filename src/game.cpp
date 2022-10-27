#include "game.h"

Game::Game(int height, int width)
{
    m_width = width;
    m_height = height;
}

bool Game::run()
{
    if(init())
    {
        while(!m_quit)
        {
            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                handle_events(event);
            }
            m_players["player"].move();
            m_players["npc"].slow_move(m_ball.get()->get_y_velocity());
            
            bool ball_outside = m_ball.get()->move(m_players);
            if(ball_outside)
            {
                update_score();
            }
            render();
        }
    }
    close();
    return false;
}

bool Game::init()
{
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize SDL. SDL error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize Window & Renderer
    m_window.reset(new Window(m_width, m_height, m_title));
    if(!(m_window.get()->init()))
    {
        printf("Failed to initialze Window.\n");
        return false;
    }

    // Initialize SDL Image
    int img_flags{ IMG_INIT_PNG };
    int innit{ IMG_Init(img_flags) };
    if( !(innit & img_flags) )
    {
        printf("Failed to initialize SDL Image. SDL Image Error: %s\n", IMG_GetError());
        return false;
    }

    // Initialize SDL Font
    if(TTF_Init() == -1)
    {
        printf("Failed to initialize SDL_ttf. SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    // TODO: Load media and intialize player, npc & ball in the same fcn?
    if(!load_media())
    {
        return false;
    }
    // TODO: keep initial positions stored in a variable
    m_players["player"] = Player(m_pad_texture, m_width-20,10, m_height);
    m_players["npc"] = Player(m_pad_texture, 10, m_height/2, m_height);
    m_ball.reset(new Ball(m_ball_texture, m_width/2, m_height/2, m_width, m_height));
    return true;
}

void Game::close()
{
    m_window.get()->free();
    m_pad_texture.free();
    m_ball_texture.free();
    m_font_texture.free();
    TTF_CloseFont(m_font);
    
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

void Game::handle_events(SDL_Event event)
{
    if(event.type == SDL_QUIT || (event.type == SDL_KEYUP and event.key.keysym.sym == SDLK_ESCAPE))
    {
        m_quit = true;
    }
    m_players["player"].handle_events(event);
}

bool Game::load_media()
{
    SDL_Renderer* renderer = m_window.get()->get_renderer();
    if(!m_pad_texture.load_texture_from_file(m_pad_path, renderer))
    {
        return false;
    }

    if(!m_ball_texture.load_texture_from_file(m_ball_path, renderer))
    {
        return false;
    }

    m_font = TTF_OpenFont(m_font_path.c_str(), 32);
    if(m_font == NULL)
    {
        printf("Failed to load font! SDL ttf error: %s\n", TTF_GetError());
        return false;
    }
    
    if(!m_font_texture.load_texture_from_font("Score: 0, 0", renderer, m_font))
    {
        false;
    }

    return true;
}

void Game::render()
{
    m_window.get()->render_clear();
    
    m_window.get()->render(m_players["player"]);
    m_window.get()->render(m_players["npc"]);
    m_ball.get()->render(m_window.get()->get_renderer());
    m_font_texture.render(m_width/2-m_font_texture.get_width()/2, 20, m_window.get()->get_renderer());

    m_window.get()->render_present();
}

void Game::update_score()
{
    int player_distance = std::abs(m_ball.get()->get_x()-m_players["player"].get_box().x);
    int npc_distance = std::abs(m_ball.get()->get_x()-m_players["npc"].get_box().x);

    if(player_distance < npc_distance)
    {
        m_players["npc"].set_score(m_players["npc"].get_score()+1);
    }
    else
    {
        m_players["player"].set_score(m_players["player"].get_score()+1);
    }
    std::string score = "Score: " + std::to_string(m_players["npc"].get_score()) + ", " + std::to_string(m_players["player"].get_score());
    m_font_texture.load_texture_from_font(score, m_window.get()->get_renderer(), m_font);

    m_ball.get()->reset_movement(m_width/2, m_height/2);
}