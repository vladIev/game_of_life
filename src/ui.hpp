#ifndef UI_HPP
#define UI_HPP

#include "fields/field.hpp"

#include <atomic>
#include <cstdio>
#include <functional>
#include <iostream>
#include <span>
#include <thread>
#include <unordered_map>
#include <utility>

namespace life {
template <typename RenderType>
class UI {
    using KeyCode = int;
    using HotkeyHandler = std::function<void()>;
    using HotkeysMap = std::unordered_map<KeyCode, HotkeyHandler>;

  private:
    RenderType d_render;
    std::thread d_hotkeysThread;
    HotkeysMap d_hotkeys;
    std::atomic_bool d_stopped = false;

  public:
    ~UI();
    void initHotkeys(HotkeysMap&& hotkeysHandlers);
    void draw(const Field& field);
    template <typename T>
    T select(std::string_view inrto, std::span<const std::string> options);
};

template <typename T>
UI<T>::~UI()
{
    d_stopped = true;
    d_hotkeysThread.join();
}

template <typename T>
void UI<T>::initHotkeys(HotkeysMap&& hotkeysHandlers)
{
    constexpr int ESC_KEY = 27;
    d_hotkeys = std::forward<HotkeysMap>(hotkeysHandlers);
    d_hotkeysThread = std::thread([this]() {
        while (!d_stopped) {
            int key = std::getchar();
            if (!d_hotkeys.contains(key)) {
                continue;
            }
            d_hotkeys[key]();
        }
    });
}

template <typename T>
void UI<T>::draw(const Field& field)
{
    d_render.draw(field);
}

template <typename Render>
template <typename T>
T UI<Render>::select(std::string_view intro,
                     std::span<const std::string> options)
{
    d_render.printOptions(intro, options);
    int choice = -1;
    while (true) {
        std::cin >> choice;
        if (choice >= 0 && choice < options.size()) {
            break;
        }
    }
    return T(choice);
}
} // namespace life

#endif