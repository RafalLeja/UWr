#pragma once
#include <WidgetsFactory.hpp>
#include <Kde.hpp>

class KdeWidgetsFactory : public WidgetsFactory
{
public:
    std::unique_ptr<Label> createLabel() const override { return std::unique_ptr<Label>(new KdeLabel); }

    std::unique_ptr<Slider> createSlider() const override { return std::unique_ptr<Slider>(new KdeSlider); }

    std::unique_ptr<Button> createButton() const override { return std::unique_ptr<Button>(new KdeButton); }
};
