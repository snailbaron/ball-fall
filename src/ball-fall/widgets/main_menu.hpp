#pragma once

#include "../widget.hpp"
#include "panel.hpp"
#include "solid_background.hpp"

#include <vector>
#include <memory>

class MainMenu : public Widget {
public:
    MainMenu(SDL_Renderer* renderer);

    void processEvent(const SDL_Event& event) override;
    void render() const override;

private:
    enum class Screen {
        Main,
        Options,
    };

    SolidBackground _background;
    Panel _mainPanel;
    Panel _optionsPanel;
    Screen _screen = Screen::Main;
};