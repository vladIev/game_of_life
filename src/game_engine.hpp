#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP
#include "game_settings.hpp"
#include "rules_engine.hpp"

namespace life {
class GameEngine {
    RulesEngine d_rulesEngine;
    GameSettings d_settings;

  public:
    GameEngine(GameSettings settings, RulesEngine&& engine);
    void start();
    void stop();
    FieldType getNextGeneration(FieldType field);
};
} // namespace life

#endif