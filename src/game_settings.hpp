#ifndef GAME_SETTINGS_HPP
#define GAME_SETTINGS_HPP

#include <cctype>
#include <utility>

namespace life {

class GameSettignsBuilder;
enum BordersType {
    LIMITED,
};
enum RulesType {
    BASIC,
};

class GameSettings {
  private:
    RulesType d_rules = RulesType::BASIC;
    BordersType d_bordersType = BordersType::LIMITED;
    size_t d_width = 80;
    size_t d_height = 24;

    GameSettings() = default;
    friend GameSettignsBuilder;

  public:
    GameSettings(GameSettings&&) = default;
    GameSettings& operator=(GameSettings&&) = default;
    GameSettings(const GameSettings&) = default;
    GameSettings& operator=(const GameSettings&) = default;

    [[nodiscard]] auto getRulesType() const -> RulesType { return d_rules; }

    [[nodiscard]] auto getBordersType() const -> BordersType
    {
        return d_bordersType;
    }

    [[nodiscard]] auto width() const -> size_t { return d_width; }
    [[nodiscard]] auto height() const -> size_t { return d_height; }
};

class GameSettignsBuilder {
  private:
    GameSettings d_settings;

  public:
    auto withRules(RulesType rules) && -> GameSettignsBuilder&&
    {
        d_settings.d_rules = rules;
        return static_cast<GameSettignsBuilder&&>(*this);
    }

    auto withBordersType(BordersType borders) && -> GameSettignsBuilder&&
    {
        d_settings.d_bordersType = borders;
        return static_cast<GameSettignsBuilder&&>(*this);
    }

    auto withWdith(size_t width) && -> GameSettignsBuilder&&
    {
        d_settings.d_width = width;
        return static_cast<GameSettignsBuilder&&>(*this);
    }

    auto withHeight(size_t height) && -> GameSettignsBuilder&&
    {
        d_settings.d_height = height;
        return static_cast<GameSettignsBuilder&&>(*this);
    }

    GameSettings&& build() && { return std::move(d_settings); }
};

} // namespace life

#endif