#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

namespace life {
template <typename RulesEngine>
class GameEngine {
    using FieldType = typename RulesEngine::FieldType;
    RulesEngine d_rulesEngine;

  public:
    GameEngine(FieldType initialState);
    void start();
    void stop();
    FieldType getNextState();
};
} // namespace life

#endif