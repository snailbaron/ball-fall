#pragma once

#include "game_state.hpp"
#include "widgets/panel.hpp"
#include "widgets/solid_background.hpp"

#include <vector>
#include <memory>

class MainMenu : public GameState {
public:
    MainMenu();

    void processEvent(const SDL_Event& event) override;
    void update(double delta) override;
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