#pragma once
#include <memory>
#include <Widgets.hpp>

class WidgetsFactory
{
public:
    virtual ~WidgetsFactory() = default;

    virtual std::unique_ptr<Label> createLabel() const = 0;
    virtual std::unique_ptr<Slider> createSlider() const = 0;
    virtual std::unique_ptr<Button> createButton() const = 0;
};

