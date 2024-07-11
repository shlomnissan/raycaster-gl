// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <vector>

#include <glad/glad.h>

class Pixels {
public:
    Pixels(unsigned width, unsigned height);

    auto Use() const -> void;

private:
    unsigned texture_ {0};
    unsigned width_ {0};
    unsigned height_ {0};

    std::vector<unsigned char> data_;
};