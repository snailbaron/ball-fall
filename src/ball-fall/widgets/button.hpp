#pragma once

#include "../widget.hpp"
#include "../color.hpp"
#include "../resources.hpp"
#include "../vector.hpp"

#include <SDL2/SDL.h>

#include <string>
#include <map>

class Button : public Widget {
public:
    using Widget::Widget;

    Button& position(int x, int y);
    Button& size(int width, int height);
    Button& text(std::string text);
    Button& action(std::function<void()> action);

    void render() const override;
    void update(double delta) override;

    bool contains(int x, int y) override;

    void onVisualState(VisualState state) override;
    void onActivate() override;
private:
    void recalculateTexture();

    static constexpr auto BorderSize = 5;
    static constexpr auto BorderColor = Color(100, 90, 250);
    static constexpr auto Font = res::FontId::Mecha;
    static const std::map<VisualState, Color> BgColorMap;

    Vector<int> _position;
    Vector<int> _size;
    std::string _text;
    std::function<void()> _action = []{};

    SDL_Texture* _texture = nullptr;
    Vector<int> _textureSize;
    Color _bgColor = BgColorMap.at(VisualState::Normal);
};