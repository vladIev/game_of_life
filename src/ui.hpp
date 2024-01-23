#ifndef UI_HPP
#define UI_HPP
#include <unordered_map>

template <typename DrawerType>
class UI {
  public:
    using KeyCode = int;
    using HotkeyHandler = std::function<void()>;
    using HotkeysMap = std::unordered_map<KeyCode, HotkeyHandler>;

    void initHotkeys(HotkeysMap hotkeysHandlers);
    void draw(const FiledType& field);
    template <typename T>
    T select(std::span<const std::string> options);
};

#endif