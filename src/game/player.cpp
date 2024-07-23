// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "player.hpp"

Player::Player(const Level& level) : level_(level) {
    x_ = (level_.Width() - Player::size_) >> 1;
    y_ = (level_.Height() - Player::size_) >> 1;   
}

auto Player::DrawMinimap(Pixels& pixels) const -> void {
    pixels.SetFill({.r = 255, .g = 0, .b = 0});
    pixels.NoStroke();
    pixels.Rect(x_, y_, Player::size_, Player::size_);
}