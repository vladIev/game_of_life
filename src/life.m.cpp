// #include "game_engine.hpp"
#include "game_engine.hpp"
#include "game_settings.hpp"
#include "utils/args_parser.hpp"

#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <magic_enum/magic_enum.hpp>

#include <stdexcept>
#include <vector>

using namespace life;

constexpr auto getAppArgs() -> std::vector<utils::OptionInfo>
{
    return {
        {.name = "-h", .description = "Prints application description"},
        {.name = "-r",
         .description = "Settle rules set for the game. BASIC - basic rulse",
         .isMandatory = false,
         .hasArgValue = true},
        {.name = "-b",
         .description = "Settle rules for borders. LIMITED - hard borders, "
                        "cells that leaves filed are diying.",
         .isMandatory = false,
         .hasArgValue = true},
        {.name = "-f",
         .description = "Path to file with initial filed state",
         .isMandatory = false,
         .hasArgValue = true},
    };
}

GameSettings buildGameSettings(const utils::ArgsParser& clArgs)
{
    const auto getEnumFromArgs =
        [&clArgs](std::string_view argName,
                  auto defaultValue) -> decltype(defaultValue) {
        using EnumT = decltype(defaultValue);
        return clArgs.isSpecified(argName)
                   ? magic_enum::enum_cast<EnumT>(clArgs.getArgValue(argName))
                         .value_or(defaultValue)
                   : defaultValue;
    };

    return GameSettignsBuilder()
        .withBordersType(getEnumFromArgs("-b", BordersType::LIMITED))
        .withRules(getEnumFromArgs("-r", RulesType::BASIC))
        .build();
}

auto main(int argc, char** argv) -> int
{
    utils::ArgsParser clArgs(getAppArgs());
    try {
        clArgs.parse(argc, argv);
    }
    catch (std::invalid_argument& e) {
        spdlog::error("Failed to start application. Reason: {}", e.what());
        spdlog::info("Usage: life {}", clArgs.getHelp());
        return 1;
    }

    if (clArgs.isSpecified("-h")) {
        spdlog::info("Usage: life {}", clArgs.getHelp());
        return 0;
    }

    auto settings = buildGameSettings(clArgs);
    spdlog::info("Creating game with {} rules and {} borders",
                 magic_enum::enum_name(settings.getRulesType()),
                 magic_enum::enum_name(settings.getBordersType()));

    GameEngine engine(std::move(settings));
    const auto& fieldsFactory = engine.getFieldsFactory();
    const auto& fieldsTypes = fieldsFactory.getTemplateFieldsType();

    UI ui;
    const auto selectedType = ui.selectFildType(fieldsTypes);
    if (selectedType == FieldsTypes::Custom) {
        const auto path = ui.getPathToField();
        auto field = fieldsFactory.build(path);
        engine.start(std::move(field));
    }
    else {
        auto field = fieldsFactory.build(selectedType);
        engine.start(std::move(field));
    }

    ui.initCommandsHandler(...);
    while (!isStopped()) {
        auto field = engine.getNextGeneration();
        ui.draw(field);
    }

    engine.stop();
    ui.stop();
    return 0;
}