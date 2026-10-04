#pragma once
#include "ImageObject.h"
#include "TimeManager.h"

class Fondo : public ImageObject {
private:
    float _scrollSpeed;          
    float _screenWidth;          
    bool* _isScrolling;          
    Fondo* _nextFondo;

public:
    Fondo(Vector2 position, Vector2 sourceOffset, Vector2 sourceSize, bool* scrolling)
        : ImageObject("resources/loFondo.png", sourceOffset, sourceSize) {

        _scrollSpeed = 300.f; 
        _screenWidth = RM->WINDOW_WIDTH;
        _isScrolling = scrolling;
        _nextFondo = nullptr;
        
        _transform->position = position;
        _transform->size = Vector2(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT);
        _transform->scale = Vector2(1.f, 1.f); 
    }

    ~Fondo() {}

    void Update() override {
        if (*_isScrolling) {
            _transform->position.x -= _scrollSpeed * TIME.GetDeltaTime();
            
            if (_nextFondo && _transform->position.x + (_transform->size.x * 1.5f) <= 0.f) {
                _transform->position.x = _nextFondo->_transform->position.x + _nextFondo->_transform->size.x;
            }
        }

        Object::Update();
    }

    void SetNextFondo(Fondo* next) {
        _nextFondo = next;
    }
    void SetScrollSpeed(float speed) {
        _scrollSpeed = speed;
    }
};



