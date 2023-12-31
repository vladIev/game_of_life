#include "args_parser.hpp"

#include <ranges>
#include <set>
#include <stdexcept>
#include <string_view>

namespace utils {

void ArgsParser::validate() const
{
    std::set<std::string_view> usedKeys;
    for (const auto& option : d_options) {
        const bool isInArgs = isSpecified(option.name);
        if (isInArgs) {
            usedKeys.emplace(option.name);
        }
        else if (option.isMandatory) {
            throw std::invalid_argument(
                fmt::format("Option {} haven't specified", option.name));
        }
    }

    if (usedKeys.size() < d_args.size()) {
        for (const auto& [key, _] : d_args) {
            if (!usedKeys.contains(key)) {
                throw std::invalid_argument(
                    fmt::format("Unknown argument {}", key));
            }
        }
    }
}

ArgsParser::ArgsParser(std::vector<OptionInfo> options)
    : d_options(std::move(options))
{
}

void ArgsParser::parse(int argc, const char* const* argv)
{
    std::string_view last;
    for (const auto i : std::views::iota(1, argc)) {
        const auto arg = std::string_view(argv[i]);
        if (arg.starts_with("-")) {
            d_args.try_emplace(arg, std::nullopt);
            last = arg;
        }
        else {
            if (last.empty()) {
                throw std::invalid_argument(
                    fmt::format("Unexpected argument value {}", arg));
            }
            d_args[last] = arg;
            last = "";
        }
    }

    validate();
}

bool ArgsParser::isSpecified(std::string_view name) const
{
    return d_args.contains(name);
}

ArgsParser::ArgType ArgsParser::getArgValue(std::string_view name) const
{
    const auto argIt = d_args.find(name);
    if (argIt == d_args.cend()) {
        throw std::invalid_argument(
            fmt::format("Argument {} haven't been specified", name));
    }

    if (!argIt->second) {
        throw std::invalid_argument(
            fmt::format("Argument {} doesn't have assosiated value", name));
    }

    return argIt->second.value();
}

std::string ArgsParser::getHelp() const
{
    constexpr std::string_view argumentFormat = "\t{}{}  {}\n";
    size_t longestArgName = 0;
    for (const auto& option : d_options) {
        longestArgName = std::max(option.name.size(), longestArgName);
    }

    std::string result;
    for (const auto& option : d_options) {
        const size_t fillerLength = option.name.size() - longestArgName;
        std::string filler(fillerLength, ' ');
        result += fmt::format(
            argumentFormat, option.name, filler, option.description);
    }
    return result;
}
} // namespace utils