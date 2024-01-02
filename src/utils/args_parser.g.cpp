#include "args_parser.hpp"
#include "fmt/core.h"

#include <gtest/gtest.h>
#include <stdexcept>

using namespace utils;
using namespace std::string_literals;

void checkFlag(const ArgsParser& parser, const OptionInfo& option)
{
    EXPECT_TRUE(parser.isSpecified(option.name));
}

void checkArgvalue(const ArgsParser& parser,
                   const OptionInfo& option,
                   std::string_view expectedValue)
{
    EXPECT_TRUE(parser.isSpecified(option.name));
    EXPECT_EQ(parser.getArgValue(option.name), expectedValue);
}

TEST(args_parser, parse_without_options)
{
    const std::vector<char*> argv = {
        (char*)"program_name",
    };

    ArgsParser parser({});

    EXPECT_NO_THROW({ parser.parse(argv.size(), argv.data()); });
}

TEST(args_parser, parse_flag)
{
    const std::vector<OptionInfo> options{
        {.name = "-h",
         .description = "Prints application description",
         .isMandatory = false},
    };
    const std::vector<char*> argv = {
        (char*)"program_name",
        (char*)"-h",
    };

    ArgsParser parser(options);

    EXPECT_NO_THROW({ parser.parse(argv.size(), argv.data()); });

    checkFlag(parser, options[0]);
}

TEST(args_parser, parse_argvalue)
{
    const std::vector<OptionInfo> options{
        {.name = "-t",
         .description = "Specifies some test value",
         .isMandatory = false,
         .hasArgValue = true},
    };
    const std::vector<char*> argv = {
        (char*)"program_name",
        (char*)"-t",
        (char*)"value",
    };

    ArgsParser parser(options);

    EXPECT_NO_THROW({ parser.parse(argv.size(), argv.data()); });

    checkArgvalue(parser, options[0], "value");
}

TEST(args_parser, parse_argvalue_and_flag)
{
    const std::vector<OptionInfo> options{
        {.name = "-h",
         .description = "Prints application description",
         .isMandatory = false},
        {.name = "-t",
         .description = "Specifies some test value",
         .isMandatory = false,
         .hasArgValue = true},
    };

    const std::vector<char*> argv = {
        (char*)"program_name",
        (char*)"-h",
        (char*)"-t",
        (char*)"value",
    };

    ArgsParser parser(options);

    EXPECT_NO_THROW({ parser.parse(argv.size(), argv.data()); });

    checkFlag(parser, options[0]);

    checkArgvalue(parser, options[1], "value");
}

TEST(args_parser, throw_if_mandatory_skipped)
{
    const std::vector<OptionInfo> options{
        {.name = "-h",
         .description = "Prints application description",
         .isMandatory = true},
    };

    const std::vector<char*> argv = {
        (char*)"program_name",
    };

    ArgsParser parser(options);

    try {
        parser.parse(argv.size(), argv.data());
        FAIL() << "Expected std::invalid_argument";
    }
    catch (const std::invalid_argument& e) {
        EXPECT_EQ("Option -h haven't specified"s, e.what());
    }
    catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(args_parser, throw_if_unknown_option)
{
    const std::vector<char*> argv = {
        (char*)"program_name",
        (char*)"-h",
    };

    ArgsParser parser({});

    try {
        parser.parse(argv.size(), argv.data());
        FAIL() << "Expected std::invalid_argument";
    }
    catch (const std::invalid_argument& e) {
        EXPECT_EQ("Unknown argument -h"s, e.what());
    }
    catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(args_parser, get_help)
{
    const std::vector<OptionInfo> options{
        {.name = "-h",
         .description = "Prints application description",
         .isMandatory = false},
        {.name = "-t",
         .description = "Specifies some test value",
         .isMandatory = false,
         .hasArgValue = true},
    };

    const std::string expected =
        "\n\t[-h]    Prints application description"
        "\n\t[-t <value>]    Specifies some test value";

    const std::vector<char*> argv = {
        (char*)"program_name",
        (char*)"-h",
        (char*)"-t",
        (char*)"value",
    };

    ArgsParser parser(options);

    EXPECT_NO_THROW({ parser.parse(argv.size(), argv.data()); });

    EXPECT_EQ(expected, parser.getHelp());
}