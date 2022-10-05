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
            m_player.get()->move();
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
        printf("Failed to initialize SDL Image. SDL Image Error %s: \n", IMG_GetError());
        return false;
    }

    // TODO: Load media and intialize player, computer & ball in the same fcn?
    if(!load_media())
    {
        return false;
    }

    m_player.reset(new Player(m_pad, m_width-20,10, m_width, m_height));
    
    return true;
}

void Game::close()
{
    m_window.get()->free();
    m_pad.free();

    SDL_Quit();
    IMG_Quit();
}

void Game::handle_events(SDL_Event event)
{
    if(event.type == SDL_QUIT || (event.type == SDL_KEYUP and event.key.keysym.sym == SDLK_ESCAPE))
    {
        m_quit = true;
    }
    m_player.get()->handle_events(event);
}

bool Game::load_media()
{
    bool successfull{ m_pad.load_texture_from_file(m_pad_path, m_window.get()->get_renderer()) };
    return successfull;
}

void Game::render()
{
    m_window.get()->render_clear();
    m_player.get()->render(m_window.get()->get_renderer());
    m_window.get()->render_present();
}