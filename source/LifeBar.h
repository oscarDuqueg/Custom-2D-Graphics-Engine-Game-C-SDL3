#pragma once
#include "Object.h"
#include "RenderManager.h"
#include "Player.h"

class LifeBar : public Object
{
private:
    Player* _player;
    int _maxWidth;
    int _height;

public:
    LifeBar(Player* player)
        : _player(player)
    {
        _maxWidth = 200;
        _height = 16;

        _transform->position = { 485.f, 727.f };
    }

    void Render() override
    {
        if (!_player) return;

        float percent =
            (float)_player->GetLife() / (float)_player->GetMaxLife();

        if (percent < 0.f) percent = 0.f;

        SDL_Renderer* renderer = RM->GetRenderer();

        SDL_FRect bg{
            _transform->position.x,
            _transform->position.y,
            (float)_maxWidth,
            (float)_height
        };

        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
        SDL_RenderFillRect(renderer, &bg);

        SDL_FRect bar{
            bg.x + 2.f,
            bg.y + 2.f,
            (_maxWidth - 4) * percent,
            (float)_height - 4.f
        };

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &bar);
    }
};
