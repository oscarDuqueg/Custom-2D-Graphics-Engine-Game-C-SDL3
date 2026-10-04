#include "GamePersistence.h"

int GamePersistence::lastScore = 0;
int GamePersistence::lastLife = 500;
bool GamePersistence::hasTwoCanon = false;
int GamePersistence::secondCannonFuel = 0;
bool GamePersistence::hasLaser = false;
int GamePersistence::laserFuel = 0;
bool GamePersistence::hasTurrets = false;
float GamePersistence::moveSpeed = 20000.f;
bool GamePersistence::comingFromLevel1 = false;

void GamePersistence::Reset() {
    lastScore = 0;
    lastLife = 500;
    hasTwoCanon = false;
    secondCannonFuel = 0;
    hasLaser = false;
    laserFuel = 0;
    hasTurrets = false;
    moveSpeed = 20000.f;
}

void GamePersistence::SaveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << lastScore << "\n"
            << lastLife << "\n"
            << hasTwoCanon << "\n"
            << secondCannonFuel << "\n"
            << hasLaser << "\n"
            << laserFuel << "\n"
            << hasTurrets << "\n"
            << moveSpeed;
        file.close();
    }
}

void GamePersistence::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> lastScore >> lastLife >> hasTwoCanon >> secondCannonFuel >> hasLaser >> laserFuel >> hasTurrets >> moveSpeed;
        file.close();
    }
}