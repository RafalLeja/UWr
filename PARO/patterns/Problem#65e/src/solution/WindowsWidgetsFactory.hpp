#pragma once
#include <memory>
#include <WidgetsFactory.hpp>
#include <Windows.hpp>

class WindowsWidgetsFactory : public WidgetsFactory
{
   std::unique_ptr<Label> createLabel() const override { return std::unique_ptr<Label>(new WindowsLabel); }

   std::unique_ptr<Slider> createSlider() const override { return std::unique_ptr<Slider>(new WindowsSlider); }

   std::unique_ptr<Button> createButton() const override { return std::unique_ptr<Button>(new WindowsButton); }
};
