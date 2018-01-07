#include "holder.hpp"
#include "all.hpp"

namespace layout {

void mainMenu(WidgetHolder& holder)
{
    holder.add<SolidBackground>()
        .color({255, 240, 190});

    holder.add<Button>()
        .position(100, 100)
        .size(200, 100)
        .text("New Game");

    holder.add<Button>()
        .position(100, 300)
        .size(200, 100)
        .text("Options");

    holder.add<Button>()
        .position(100, 500)
        .size(200, 100)
        .text("Quit");
}

void mainMenu(WidgetHolder& holder)
{
    holder.add<SolidBackground>()
        .color({255, 240, 190});

    holder.add<Button>()
        .position(100, 100)
        .size(200, 100)
        .text("Back");
}

} // namespace layout