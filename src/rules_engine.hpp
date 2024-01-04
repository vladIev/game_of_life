#ifndef RULES_ENGINE_HPP
#define RULES_ENGINE_HPP
#include <ranges>

namespace life {
class FieldType;

template <typename RulesImpl>
class RulesEngine {
  public:
    static std::ranges::view auto getFiledsTemplates();
    static auto buildFiledTemplate() -> FieldType&&;

    FieldType getNextGeneration(const FieldType& initialFiled);
};
} // namespace life
#endif