// #include "game_engine.hpp"
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
         .description = "Settle rules set for the game. BASIC - basic rulse"},
        {.name = "-b",
         .description = "Settle rules for borders. LIMITED - hard borders, "
                        "cells that leaves filed are diying."},
        {.name = "-f", .description = "Path to file with initial filed state"},
    };
}

GameSettings buildGameSettings(const utils::ArgsParser& clArgs)
{
    BordersType borders = BordersType::LIMITED;
    if (clArgs.isSpecified("-b")) {
        borders = magic_enum::enum_cast<BordersType>(clArgs.getArgValue("-b"))
                      .value();
    }

    RulesType rules = RulesType::BASIC;
    if (clArgs.isSpecified("-r")) {
        rules =
            magic_enum::enum_cast<RulesType>(clArgs.getArgValue("-r")).value();
    }

    return GameSettignsBuilder()
        .withBordersType(borders)
        .withRules(rules)
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

    const auto settings = buildGameSettings(clArgs);
    spdlog::info("Creating game with {} rules and {} borders",
                 magic_enum::enum_name(settings.getRulesType()),
                 magic_enum::enum_name(settings.getBordersType()));

    return 0;
}