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

    auto PutPixel(unsigned x, unsigned y, RGB color) -> void;

    auto Draw() -> void;

private:
    bool dirty_ {false};

    unsigned texture_ {0};
    unsigned width_ {0};
    unsigned height_ {0};

    std::vector<unsigned char> data_;
};