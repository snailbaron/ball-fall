#pragma once

struct SDL_Renderer;

class Widget {
public:
    enum class VisualState {
        Normal,
        Focused,
        Pressed,
    };

    Widget(SDL_Renderer* renderer) : _renderer(renderer) {}
    virtual ~Widget() {}

    virtual void render() const = 0;
    virtual void update(double /*delta*/) {}

    virtual bool contains(int /*x*/, int /*y*/) { return false; }

    virtual void onVisualState(VisualState /*state*/) {}
    virtual void onActivate() {}

protected:
    SDL_Renderer* renderer() const { return _renderer; }

private:
    SDL_Renderer* _renderer;
};

