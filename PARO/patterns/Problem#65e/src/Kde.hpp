#pragma once
#include <Widgets.hpp>
#include <iostream>

class KdeLabel : public Label
{
public:
    void draw() const override
    {
        std::cout << "KdeLabel\n";
    }
};

class KdeSlider : public Slider
{
public:
    void draw() const override
    {
        std::cout << "KdeSlider\n";
    }

    void onSlide() const override
    {
        std::cout << "I can slide on Kde\n";
    }
};

class KdeButton : public Button
{
public:
    void draw() const override
    {
        std::cout << "KdeDivider\n";
    }

    void onClick() const override
    {
        std::cout << "I can click on Kde\n";
    }
};
