// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "player.hpp"

Player::Player(const Level& level) : level_(level) {
    x_ = static_cast<float>(level_.Width()) / 2;
    y_ = static_cast<float>(level_.Height()) / 2;   
}

auto Player::DrawMinimap(Pixels& pixels) const -> void {
    // TODO: impl.
}