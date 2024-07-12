// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <vector>

#include <glad/glad.h>

struct RGB {
    unsigned char r {0};
    unsigned char g {0};
    unsigned char b {0};
};

class Pixels {
public:
    Pixels(unsigned width, unsigned height);

    ~Pixels();

    auto SetStroke(RGB color) -> void;

    auto SetFill(RGB color) -> void;

    auto NoStroke() { no_stroke_ = true; }

    auto NoFill() { no_fill_ = true; }

    auto Line(unsigned x1, unsigned y1, unsigned x2, unsigned y2) -> void;

    auto Rect(unsigned x, unsigned y, unsigned width, unsigned height) -> void;

    auto Clear() -> void;

    auto Bind() -> void;

private:
    bool dirty_ {false};
    bool no_stroke_ {false};
    bool no_fill_ {false};

    unsigned texture_ {0};
    unsigned width_ {0};
    unsigned height_ {0};

    RGB stroke_color_ {255, 255, 255};
    RGB fill_color_ {255, 255, 255};

    std::vector<unsigned char> data_;

    auto PutPixel(unsigned x, unsigned y, RGB color) -> void;
};