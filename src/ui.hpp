#ifndef UI_HPP
#define UI_HPP

#include <atomic>
#include <cstdio>
#include <thread>
#include <unordered_map>

namespace life {
template <typename DrawerType>
class UI {
    using KeyCode = int;
    using HotkeyHandler = std::function<void()>;
    using HotkeysMap = std::unordered_map<KeyCode, HotkeyHandler>;

  private:
    DrawerType d_drawer;
    std::thread d_hotkeysThread;
    HotkeysMap d_hotkeys;
    std::atomic_bool d_stopped = false;

  public:
    ~UI();
    void initHotkeys(HotkeysMap&& hotkeysHandlers);
    void draw(const FiledType& field);
    template <typename T>
    T select(std::span<const std::string> options);
};

template <typename DrawerType>
UI::~UI()
{
    d_stopped = true;
    d_hotkeyThread.join();
}

template <typename DrawerType>
void UI::initHotkeys(HotkeysMap&& hotkeysHandlers)
{
    constexpr int ESC_KEY = 27;
    d_hotkeys = std::forward(hotkeysHandlers);
    d_hotkeysThread = std::thread([this]() {
        while (int key = std::getchar(); key != ESC_KEY && !d_stopped) {
            if (!d_hotkeys.contains(key)) {
                continue;
            }
            d_hotkeys[key]();
        }
    });
}
} // namespace life

#endif