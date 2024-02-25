#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP
#include "fields/field.hpp"
#include "game_settings.hpp"
#include "rules_engine.hpp"

#include <memory>

namespace {
} // namespace

namespace life {
class GameEngine {
    std::unique_ptr<BasicRulesEngine> d_rulesEngine;
    GameSettings d_settings;
    Field d_lastField;

  public:
    GameEngine(GameSettings settings) : d_settings(settings), d_lastField(0, 0)
    {
    }

    void start(Field&& inititalField)
    {
        d_lastField = std::forward<Field>(inititalField);
    }

    void stop() {}
    const Field& getNextGeneration()
    {
        d_lastField = d_rulesEngine->getNextGeneration(d_lastField);
        return d_lastField;
    }
};
} // namespace life

#endif