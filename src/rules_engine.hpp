#ifndef RULES_ENGINE_HPP
#define RULES_ENGINE_HPP
#include "fields/field.hpp"
#include "game_settings.hpp"

#include <magic_enum/magic_enum.hpp>

#include <filesystem>
#include <ranges>

namespace life {
class Field;
class FieldFactory {
  private:
    static void randomize(Field* field);

  public:
    enum class Tempalte { RANDOM };
    [[nodiscard]] static std::vector<std::string> getTemplates()
    {
        constexpr auto names = magic_enum::enum_names<Tempalte>();
        return {names.begin(), names.end()};
    }

    [[nodiscard]] static Field build(size_t width, size_t height)
    {
        return {width, height};
    }

    [[nodiscard]] static Field build(const std::filesystem::path& path)
    {
        return {1, 1};
    }

    [[nodiscard]] static Field build(const Field& field)
    {
        return {field.width(), field.height()};
    }

    [[nodiscard]] static Field
    build(size_t width, size_t height, const Field& in)
    {
        Field field(std::max(width, in.width()), std::max(height, in.height()));
        // embed(field, in);
        return field;
    }

    [[nodiscard]] static Field build(Tempalte type, size_t width, size_t height)
    {
        switch (type) {
        case Tempalte::RANDOM: {
            auto field = build(width, height);
            randomize(&field);
            return field;
        }
        default:
            throw(std::runtime_error("Unknown template"));
        }
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
    [[nodiscard]] const FieldFactory& fieldsFactory() const
    {
        return d_factory;
    }

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
