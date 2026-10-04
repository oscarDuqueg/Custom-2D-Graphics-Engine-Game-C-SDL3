#pragma once
#include "TextObject.h"
#include "Enemy.h"
#include <string>
#include <iomanip>
#include <sstream>


class Score : public TextObject
{
private:
    int loScore = 0;

public:
    Score()
        : TextObject("000000"), loScore(0)
    {
        GetTransform()->position = { 225.f, 800.f };
        GetTransform()->scale = { 2.f, 2.f };
    }

    void Add(int value)
    {
         loScore += value;

        std::ostringstream ss;
        ss << std::setw(6) << std::setfill('0') << loScore;

        SetText(ss.str());
    }

    int GetScore() { return loScore; }

    void SetScore(int value)
    {
        loScore = value;

        std::ostringstream ss;
        ss << std::setw(6) << std::setfill('0') << loScore;
        SetText(ss.str());
    }
};
