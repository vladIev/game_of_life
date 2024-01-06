#ifndef UI_HPP
#define UI_HPP
#include <unordered_map>

template <typename DrawerType>
class UI {
  public:
    using KeyCode = int;
    using HotkeyHandler = std::function<int()>;
    using HotkeysMap = std::unordered_map<KeyCode, HotkeyHandler>;

    auto selectFieldType(auto avaliableType);
    void initHotkeys(HotkeysMap hotkeysHandlers);
    void draw(const FiledType& field);
};

#endif