#pragma once
#include <Widgets.hpp>
#include <iostream>

class WindowsLabel : public Label
{
public:
    void draw() const override
    {
        std::cout << "WindowsLabel\n";
    }
};

class WindowsSlider : public Slider
{
public:
    void draw() const override
    {
        std::cout << "WindowsSlider\n";
    }

    void onSlide() const override
    {
        std::cout << "I can slide on Windows\n";
    }
};

class WindowsButton : public Button
{
public:
    void draw() const override
    {
        std::cout << "WindowsDivider\n";
    }

    void onClick() const override
    {
        std::cout << "I can click on Windows\n";
    }

};
