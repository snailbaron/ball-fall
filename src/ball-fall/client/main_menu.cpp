#include "main_menu.hpp"
#include "widgets/button.hpp"
#include "../events.hpp"

MainMenu::MainMenu()
{
    _mainPanel.position(100, 100);
    _mainPanel.size(800, 500);

    _optionsPanel.position(100, 100);
    _optionsPanel.size(800, 500);

    _mainPanel.make<Button>()
        .text("New Game")
        .action([] {
            evt::bus().makeSend<evt::NewGame>();
        });
    _mainPanel.make<Button>()
        .text("Options")
        .action([this] {
            _screen = Screen::Options;
        });
    _mainPanel.make<Button>()
        .text("Quit")
        .action([] {
            evt::bus().makeSend<evt::Quit>();
        });

    _optionsPanel.make<Button>()
        .text("Volume");
    _optionsPanel.make<Button>()
        .text("Fullscreen");
    _optionsPanel.make<Button>()
        .text("Back")
        .action([this] {
            _screen = Screen::Main;
        });
}

void MainMenu::processEvent(const SDL_Event& event)
{
    switch (_screen) {
        case Screen::Main:
            _mainPanel.processEvent(event);
            break;

        case Screen::Options:
            _optionsPanel.processEvent(event);
            break;
    }
}

void MainMenu::update(double delta)
{
    _background.update(delta);
    _mainPanel.update(delta);
    _optionsPanel.update(delta);
}

void MainMenu::render() const
{
    _background.render();

    switch (_screen) {
        case Screen::Main:
            _mainPanel.render();
            break;

        case Screen::Options:
            _optionsPanel.render();
            break;
    }
}