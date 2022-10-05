#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "texture.h"
#include "player.h"

class Game
{
    public:
        Game(int height, int width);
        bool run();

    private:
        int m_width{};
        int m_height{};

        const std::string m_title{"Pong"};
        bool m_quit{false};

        std::string m_pad_path{"../assets/pad.png"};
        Texture m_pad{};

        std::unique_ptr<Player> m_player{};
        std::unique_ptr<Window> m_window{};

        bool init();
        void close();
        void handle_events(SDL_Event event);
        bool load_media();
        void render();

};

#endif