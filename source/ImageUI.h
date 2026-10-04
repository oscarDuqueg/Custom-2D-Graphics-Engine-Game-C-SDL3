#include "ImageObject.h"

class ImageUI : public ImageObject
{
private:
    float _screenWidth;
public:
    ImageUI(Vector2 position, Vector2 sourceOffset, Vector2 sourceSize)
        : ImageObject("resources/splashimage.png", sourceOffset, sourceSize) {

        _screenWidth = RM->WINDOW_WIDTH;

        _transform->position = position;
        _transform->size = Vector2(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT);
        _transform->scale = Vector2(1.f, 1.f);
    }


    void Update() override 
    {
        Object::Update();
    }
};