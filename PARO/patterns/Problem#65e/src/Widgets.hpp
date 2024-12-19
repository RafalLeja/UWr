#pragma once

class Widget
{
public:
    virtual ~Widget() = default;

    virtual void draw() const = 0;
};

class Label : public Widget
{
public:
    virtual ~Label() = default;

    virtual void draw() const = 0;
};

class Slider : public Widget
{
public:
    virtual ~Slider() = default;

    virtual void draw() const = 0;
    virtual void onSlide() const = 0;
};

class Button : public Widget
{
public:
    virtual ~Button() = default;

    virtual void draw() const = 0;
    virtual void onClick() const = 0;
};

