// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "pixels.hpp"

constexpr unsigned RGB_SIZE = 3;

Pixels::Pixels(unsigned width, unsigned height)
  : data_(width * height * RGB_SIZE, 0), width_(width), height_(height) {
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);

    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data_.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

auto Pixels::PutPixel(unsigned x, unsigned y, RGB color) -> void {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return;
    }

    y = height_ - y - 1;

    auto index = (y * width_ + x) * 3;
    data_[index] = color.r;
    data_[index + 1] = color.g;
    data_[index + 2] = color.b;

    dirty_ = true;
}

auto Pixels::Draw() -> void {
    if (!dirty_) return;

    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, data_.data());

    dirty_ = false;
}