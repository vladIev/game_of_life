#ifndef RULES_ENGINE_HPP
#define RULES_ENGINE_HPP
#include "fields/field.hpp"

#include <filesystem>
#include <ranges>

namespace life {
class Field;
struct FieldFactory {
    Field build(size_t width, size_t height) { return Field(width, height); }
    Field build(const std::filesystem::path& path) { return Field(1, 1); }
    Field build(const Field& field)
    {
        return Field(field.width(), field.height());
    }
    Field build(size_t width, size_t height, const Field& in)
    {
        Field field(std::max(width, in.width()), std::max(height, in.height()));
        // embed(field, in);
        return field;
    }
};

class CellCalculator {
    const Field* d_field;

  public:
    CellCalculator(const Field* field);
    uint8_t operator()(size_t x, size_t y) const;
};

class BasicRulesEngine {
    FieldFactory d_factory;

  public:
    BasicRulesEngine() {}
    const FieldFactory& fieldsFactory() const { return d_factory; }
    Field getNextGeneration(const Field& field)
    {
        CellCalculator calculator(&field);
        Field newField = d_factory.build(field);
        for (size_t i = 0; i < field.height(); i++) {
            for (size_t j = 0; j < field.width(); j++) {
                newField.at(i, j) = calculator(i, j);
            }
        }

        return newField;
    }
};
} // namespace life
#endif
