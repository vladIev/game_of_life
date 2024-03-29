#ifndef ARGS_PARSER_HPP
#define ARGS_PARSER_HPP
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <fmt/format.h>

namespace utils {

struct OptionInfo {
    const std::string name;
    const std::string description;
    const bool isMandatory = false;
    const bool hasArgValue = false;
};

class ArgsParser {
    using ArgType = std::string;

    const std::vector<OptionInfo> d_options;
    std::unordered_map<std::string_view, std::optional<ArgType>> d_args;

    void validate() const;

  public:
    ArgsParser(std::vector<OptionInfo> options);
    ArgsParser(const ArgsParser&) = delete;
    ArgsParser(ArgsParser&&) = delete;

    void parse(int argc, const char* const* argv);

    bool isSpecified(std::string_view name) const;

    ArgType getArgValue(std::string_view name) const;

    std::string getHelp() const;
};

} // namespace utils
#endif