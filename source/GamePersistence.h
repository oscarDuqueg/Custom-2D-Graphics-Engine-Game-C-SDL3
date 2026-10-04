#pragma once
#include <fstream>
#include <string>
#include <iostream>

class GamePersistence {
public:
    static int lastScore;
    static int lastLife;
    static bool hasTwoCanon;
    static int secondCannonFuel;
    static bool hasLaser;
    static int laserFuel;
    static bool hasTurrets;
    static float moveSpeed;
    static bool comingFromLevel1;
    static void Reset();
    static void SaveToFile(const std::string& filename);
    static void LoadFromFile(const std::string& filename);
};