// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <vector>

#include <glad/glad.h>

struct RGB {
    unsigned r {0};
    unsigned g {0};
    unsigned b {0};
};

class Pixels {
public:
    Pixels(unsigned width, unsigned height);

    ~Pixels();

    auto PutPixel(unsigned x, unsigned y, RGB color) -> void;

    auto Line(unsigned x1, unsigned y1, unsigned x2, unsigned y2, RGB color) -> void;

    auto Clear() -> void;

    auto Bind() -> void;

private:
    bool dirty_ {false};

    unsigned texture_ {0};
    unsigned width_ {0};
    unsigned height_ {0};

    std::vector<unsigned char> data_;
};