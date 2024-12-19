#pragma once
#include <Widgets.hpp>
#include <iostream>

class GnomeLabel :  public Label
{
public:
    void draw() const override
    {
        std::cout << "GnomeLabel\n";
    }
};

class GnomeSlider : public Slider
{
public:
    void draw() const override
    {
        std::cout << "GnomeSlider\n";
    }

    void onSlide() const override
    {
        std::cout << "I can slide on Gnome\n";
    }
};

class GnomeButton : public Button
{
public:
    void draw() const override
    {
        std::cout << "GnomeButton\n";
    }

    void onClick() const override
    {
        std::cout << "I can click on Gnome\n";
    }
};


