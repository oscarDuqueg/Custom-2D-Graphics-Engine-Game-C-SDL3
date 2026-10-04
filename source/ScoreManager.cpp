#include "ScoreManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

ScoreManager::ScoreManager() {
    LoadHighScores();
}

void ScoreManager::InitializeDefaultScores() {
    highScores[1000] = "DEV1";
    highScores[900] = "DEV2";
    highScores[800] = "DEV3";
    highScores[700] = "DEV4";
    highScores[600] = "DEV5";
    highScores[500] = "DEV6";
    highScores[400] = "DEV7";
    highScores[300] = "DEV8";
    highScores[200] = "DEV9";
    highScores[100] = "DEV10";
}

bool ScoreManager::IsHighScore(int score) const {
    if (highScores.empty()) return true;

    auto it = highScores.end();
    --it;

    return (score > it->first) || (highScores.size() < MAX_SCORES);
}

void ScoreManager::AddHighScore(int score, const std::string& name) {
    if (!IsHighScore(score)) return;

    highScores[score] = name;

    while (highScores.size() > MAX_SCORES) {
        auto it = highScores.end();
        --it;
        highScores.erase(it);
    }

    std::cout << "High score added: " << name << " - " << score << std::endl;

    SaveHighScores();
}

void ScoreManager::ClearHighScores() {
    highScores.clear();
    InitializeDefaultScores();
    SaveHighScores();
}

void ScoreManager::LoadHighScores() {
    highScores.clear();

    const std::string filename = "highscores.txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "No se encontró " << filename << "  usando puntajes por defecto\n";
        InitializeDefaultScores();
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int score;
        std::string name;

        if (iss >> score >> name) {
            if (score >= 0 && !name.empty()) {
                highScores[score] = name;
            }
        }
        // Si la línea está mal formada  simplemente se ignora
    }

    file.close();

    std::cout << "Cargados " << highScores.size() << " puntajes de " << filename << "\n";

    if (highScores.empty() || highScores.size() < MAX_SCORES) {
        std::cout << "Pocos puntajes  añadiendo valores por defecto\n";
        InitializeDefaultScores();
    }
}

void ScoreManager::SaveHighScores() const {
    const std::string filename = "highscores.txt";
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir " << filename << " para escritura\n";
        return;
    }

    for (const auto& p : highScores) {
        file << p.first << " " << p.second << "\n";
    }

    file.close();

    std::cout << "Guardados " << highScores.size() << " puntajes en " << filename << "\n";
}