#pragma once
#include <functional>
#include "ImageObject.h"
#include "InputManager.h"

class Button : public ImageObject
{
public:
    typedef std::function<void()> OnClick;

     Button(OnClick onClick, const Vector2& position, const std::string& texturePath)
        : ImageObject(texturePath, Vector2(0.f, 0.f), Vector2(306.f, 562.f))
    {
        _onClick = onClick;

        _transform->position = position;
        _transform->scale = Vector2(2.5f, 1.5f);

        _physics->AddCollider(new AABB(_transform->position, _transform->size));
    }

    virtual void Update() override
    {
        if (!_isHovered && _physics->CheckOverlappingPoint({ (float)IM->GetMouseX(), (float)IM->GetMouseY() }))
            OnHoverEnter();
        else if (_isHovered && !_physics->CheckOverlappingPoint({ (float)IM->GetMouseX(), (float)IM->GetMouseY() }))
            OnHoverExit();
        else if (_isHovered && IM->GetLeftClick())
            OnClicked();

        Object::Update();
    }

    virtual void Render() override
    {
        Object::Render();
    }

private:
    bool _isHovered = false;
    OnClick _onClick;

    void OnHoverEnter()
    {
        _transform->scale = Vector2(2.7f, 1.7f);
        _isHovered = true;
    }
    void OnHoverExit()
    {
        _transform->scale = Vector2(2.5f, 1.5f);
        _isHovered = false;
    }
    void OnClicked()
    {
        _onClick();
        if (_onClick) {
            _onClick();
        }
    }
};
