#include "window.h"

Window::Window(int width, int height, std::string title)
{
    m_width = width;
    m_height = height;
    m_title = title;
}

bool Window::init()
{
    // free existing window & renderer
    free();
    
    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, 0);
    if(!m_window)
    {
        printf("Window could not be created, SDL Error: %s\n", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!m_renderer)
    {
        printf("Renderer could not be created, SDL Error: %s\n", SDL_GetError());
        free();
        return false;
    }

    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    return true;
}

void Window::render_present()
{
    if(m_renderer != NULL)
    {
        SDL_RenderPresent(m_renderer);
    }
    else
    {
        printf("Renderer has not been initialized, cannot render present!\n");
    }
}

void Window::render_clear()
{
    if(m_renderer != NULL)
    {
        SDL_RenderClear(m_renderer);
    }
    else
    {
        printf("Renderer has not been initialized, cannot render clear!\n");
    }
}

void Window::render(IRenderable &rendering_object)
{
    if(m_renderer != NULL)
    {
        rendering_object.render(m_renderer);
    }
    else
    {
        printf("Renderer has not been initialized, cannot render!\n");
    }
}

void Window::free()
{
    if(m_window != NULL)
    {
        SDL_DestroyWindow(m_window);
        m_window = NULL;
    }

    if(m_renderer != NULL)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = NULL;
    }
}

SDL_Renderer* Window::get_renderer()
{
    return m_renderer;
}