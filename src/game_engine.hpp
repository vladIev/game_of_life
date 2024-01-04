#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP
#include "game_settings.hpp"

namespace life {
template <typename RulesEngine>
class GameEngine {
    using FieldType = typename RulesEngine::FieldType;
    RulesEngine d_rulesEngine;
    GameSettings d_settings;

  public:
    GameEngine(GameSettings settings);
    void start();
    void stop();
    FieldType getNextState();
};
} // namespace life

#endif