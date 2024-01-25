#ifndef UI_HPP
#define UI_HPP

#include <atomic>
#include <cstdio>
#include <thread>
#include <unordered_map>

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
    void draw(const FiledType& field);
    template <typename T>
    T select(std::string_view inrto, std::span<const std::string> options);
};

template <typename T>
UI<T>::~UI()
{
    d_stopped = true;
    d_hotkeyThread.join();
}

template <typename T>
void UI<T>::initHotkeys(HotkeysMap&& hotkeysHandlers)
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

template <typename T>
void UI<T>::draw(const FiledType& field)
{
    d_render.draw(field);
}

template <typename Render>
template <typename T>
T UI<Render>::select(std::string_view inrto,
                     std::span<const std::string> options)
{
    d_render.printOptions(intro, options);
    int choice = -1;
    while (1) {
        std::cin >> choice;
        if (choice >= 0 && choice < options.size()) {
            break;
        }
    }
    return T(choice);
}
} // namespace life

#endif