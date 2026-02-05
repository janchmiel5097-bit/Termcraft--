#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "entity.hpp"
#include "../global.hpp"

struct PlayerEntity :Entity {
    float speed = 200.0F;
    vec2 velocity = vec2(0.0F, 0.0F);
    int damageCooldown = -1;

    explicit PlayerEntity(
        vec2 _size = vec2(40.0F, 40.0F),
        vec2 _pos = vec2(380.0F, 280.0F),
        vec4 _color = vec4(0x09db02ff)
    ) {
        size = _size;
        position = _pos;
        color = _color;

        GLOBAL_PLAYER_SIZE = _size;
    }

    virtual ~PlayerEntity() = default;

    void update(float dt) override {
        if (damageCooldown > -1) damageCooldown--;

        velocity = vec2(0.0f, 0.0f);

        if (Input.upPressed) {    velocity.y -= speed * dt; }
        if (Input.downPressed) {  velocity.y += speed * dt; }
        if (Input.leftPressed) {  velocity.x -= speed * dt; }
        if (Input.rightPressed) { velocity.x += speed * dt; }

        {
            // if going for example up&right apply *0.75 slowness to the player
            int v0=0;
            bool v1_a[4] = {Input.upPressed, Input.downPressed, Input.leftPressed, Input.rightPressed};
            for (bool b : v1_a) v0 += (b ? 1 : 0);
            if (v0 == 2) velocity *= 0.75;
        }

        position += velocity;
        position.x = std::clamp(position.x, 0.0F, WINDOW_WIDTH - size.x);
        position.y = std::clamp(position.y, 0.0F, WINDOW_HEIGHT - size.y);

        GLOBAL_PLAYER_POSITON = position;
    }

    void damage(int _amount) {
        if (damageCooldown == -1) {
            GLOBAL_PLAYER_TOTAL_HEALTH -= _amount;
            damageCooldown = 50;

            std::cout << GLOBAL_PLAYER_TOTAL_HEALTH << std::endl;
            if (GLOBAL_PLAYER_TOTAL_HEALTH == 0) exit(0);
        }
    }
};
