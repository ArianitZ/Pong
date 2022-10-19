#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include <unordered_map>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "texture.h"
#include "player.h"
#include "ball.h"

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
        std::string m_ball_path{"../assets/ball.png"};
        Texture m_pad_texture{};
        Texture m_ball_texture{};

        std::unordered_map<std::string, Player> m_players{};
        std::unique_ptr<Ball> m_ball{};
        std::unique_ptr<Window> m_window{};

        bool init();
        void close();
        void handle_events(SDL_Event event);
        bool load_media();
        void render();

};

#endif