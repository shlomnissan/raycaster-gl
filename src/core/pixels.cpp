// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "pixels.hpp"

#include <algorithm>
#include <cmath>

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
}

auto Pixels::PutPixel(unsigned x, unsigned y, RGB color) -> void {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return;
    }

    y = height_ - y - 1; // flip the y coordinate

    auto index = (y * width_ + x) * 3;
    data_[index] = color.r;
    data_[index + 1] = color.g;
    data_[index + 2] = color.b;

    dirty_ = true;
}

auto Pixels::Line(unsigned x1, unsigned y1, unsigned x2, unsigned y2, RGB color) -> void {
    auto delta_x = static_cast<int>(x2 - x1);
    auto delta_y = static_cast<int>(y2 - y1);
    auto sign_x = delta_x < 0 ? -1 : 1;
    auto sign_y = delta_y < 0 ? -1 : 1;
    auto steep = std::abs(delta_y) >= std::abs(delta_x);
    auto slope = steep ?
        static_cast<float>(delta_x) / static_cast<float>(delta_y) :
        static_cast<float>(delta_y) / static_cast<float>(delta_x);

    if (steep) {
        for (auto i = 0; i < delta_y; ++i) {
            auto px = slope * i + x1;
            auto py = i + y1;
            PutPixel(px, py, color);
        }
    } else {
        for (auto i = 0; i < delta_x; ++i) {
            auto px = i + x1;
            auto py = slope * i + y1;
            PutPixel(px, py, color);
        }
    }
}

auto Pixels::Clear() -> void {
    std::fill(begin(data_), end(data_), 0);
}

auto Pixels::Bind() -> void {
    if (!dirty_) return;
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, data_.data());
    dirty_ = false;
}

Pixels::~Pixels() {
    if (texture_ != 0) {
        glDeleteTextures(1, &texture_);
    }
}