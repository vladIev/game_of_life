#ifndef RULES_ENGINE_HPP
#define RULES_ENGINE_HPP
#include <filesystem>
#include <ranges>

namespace life {
class FieldType;
struct FieldFactory {
    FieldType build(size_t width, size_t height) {}
    FieldType build(const std::filesystem::path& path);
    FieldType build(const FieldType& field);
};

class CellCalculator {
    const FieldType* d_field;

  public:
    CellCalculator(const FieldType* field);
    uint8_t operator()(size_t x, size_t y) const;
};

class BasicRulesEngine {
    FieldFactory d_factory;

  public:
    BasicRulesEngine();
    const FieldFactory& fieldsFactory();
    FieldType getNextGeneration(const FieldType& field)
    {
        CellCalculator calculator(&field);
        FieldType newField = d_factory.build(field);
        for (size_t i = 1; i < field.height(); i++) {
            for (size_t j 0; j < field.width(); j++) {
                newField.at(i, j) = calculator(i, j);
            }
        }

        return newField;
    }
};
} // namespace life
#endif
