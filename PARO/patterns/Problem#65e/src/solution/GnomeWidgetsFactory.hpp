#pragma once
#include <memory>
#include <WidgetsFactory.hpp>
#include <Gnome.hpp>

class GnomeWidgetsFactory : public WidgetsFactory
{
   std::unique_ptr<Label> createLabel() const override { return std::unique_ptr<Label>(new GnomeLabel); }

   std::unique_ptr<Slider> createSlider() const override { return std::unique_ptr<Slider>(new GnomeSlider); }

   std::unique_ptr<Button> createButton() const override { return std::unique_ptr<Button>(new GnomeButton); }
};
