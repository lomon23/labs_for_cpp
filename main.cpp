#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

int main() {
    using namespace ftxui;
    auto doc = vbox({
        text("Money Lab") | bold | color(Color::Green) | center,
        separator(),
        text("Arch Linux + FTXUI завелося успішно!") | center,
    }) | border;
    
    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
    Render(screen, doc);
    screen.Print();
    return 0;
}
