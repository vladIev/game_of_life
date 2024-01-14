#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP
#include "fields/field.hpp"
#include "game_settings.hpp"
#include "rules_engine.hpp"

#include <memory>

namespace life {
class GameEngine {
    std::unique_ptr<RulesEngine> d_rulesEngine;
    GameSettings d_settings;

  public:
    GameEngine(GameSettings settings);
    void start();
    void stop();
    Field getNextGeneration(Field field);
};
} // namespace life

#endif