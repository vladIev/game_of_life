#ifndef GAME_SETTINGS_HPP
#define GAME_SETTINGS_HPP
#include <utility>

namespace life {
class GameSettignsBuilder;
class GameSettings {
  public:
    enum class RulesType {
        e_BASIC,
    };

    enum class BordersType { e_LIMITED };

  private:
    RulesType d_rules = RulesType::e_BASIC;
    BordersType d_bordersType = BordersType::e_LIMITED;

    friend GameSettignsBuilder;

  public:
    GameSettings() = delete;
    GameSettings(GameSettings&&) = default;
    GameSettings& operator=(GameSettings&&) = default;

    GameSettings(const GameSettings&) = delete;
    GameSettings& operator=(const GameSettings&) = delete;

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
    auto withRules(GameSettings::RulesType rules) && -> GameSettignsBuilder&&
    {
        d_settings.d_rules = rules;
        return static_cast<GameSettignsBuilder&&>(*this);
    }

    auto withBordersType(
        GameSettings::BordersType borders) && -> GameSettignsBuilder&&
    {
        d_settings.d_bordersType = borders;
        return static_cast<GameSettignsBuilder&&>(*this);
    }

    GameSettings&& build() && { return std::move(d_settings); }
};

} // namespace life

#endif