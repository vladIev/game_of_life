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

    GameSettings&& build() && { return std::move(d_settings); }
};

} // namespace life

#endif