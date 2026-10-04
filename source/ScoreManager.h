#pragma once

#include <map>
#include <string>
#include <algorithm>

#define SC ScoreManager::GetInstance()

class ScoreManager {
public:
    static ScoreManager* GetInstance() {
        static ScoreManager instance;
        return &instance;
    }

    void AddHighScore(int score, const std::string& name);
    bool IsHighScore(int score) const;
    const std::map<int, std::string, std::greater<int>>& GetHighScores() const { return highScores; }
    void ClearHighScores();

private:
    ScoreManager();
    ScoreManager(ScoreManager&) = delete;
    ScoreManager& operator=(const ScoreManager&) = delete;
    ~ScoreManager() {}

    std::map<int, std::string, std::greater<int>> highScores;
    const size_t MAX_SCORES = 10;

    void InitializeDefaultScores();

    // Persistencia simple txt
    void LoadHighScores();
    void SaveHighScores() const;
};