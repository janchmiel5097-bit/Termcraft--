#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "entity.hpp"
#include "../global.hpp"

struct PlayerEntity :Entity {
    const float FRICTION = 6.0f;
    float SPEED = 2000.0F;
    float DASH_BOOST = 75000.0F;
    vec2 velocity = vec2(0.0F, 0.0F);
    int damageCooldown = -1;
    int dashCooldown = -1;

    explicit PlayerEntity(
        vec2 _size = vec2(40.0F, 40.0F),
        vec2 _pos = vec2(480.0F, 380.0F),
        vec4 _color = vec4(0x09db02ff)
    ) {
        size = _size;
        position = _pos;
        color = _color;

        GLOBAL_PLAYER_SIZE = _size;
    }

    virtual ~PlayerEntity() = default;

    void update(float dt) override {
        // decrease damage cooldown
        if (damageCooldown > -1) damageCooldown--;

        // move player according to current velocity
        position += velocity * dt; // multiply by delta for frame independence

        // clamp inside window
        position.x = std::clamp(position.x, 0.0F, WINDOW_WIDTH - size.x);
        position.y = std::clamp(position.y, 0.0F, WINDOW_HEIGHT - size.y);

        // gradually reduce velocity
        velocity.x -= velocity.x * FRICTION * dt;
        velocity.y -= velocity.y * FRICTION * dt;

        // apply input on top of existing velocity
        if (Input.upPressed) {    velocity.y -= SPEED * dt; }
        if (Input.downPressed) {  velocity.y += SPEED * dt; }
        if (Input.leftPressed) {  velocity.x -= SPEED * dt; }
        if (Input.rightPressed) { velocity.x += SPEED * dt; }

        if (dashCooldown == -1) {
            if (Input.dashPressed) {
                if (Input.upPressed) {    velocity.y -= DASH_BOOST * dt; }
                if (Input.downPressed) {  velocity.y += DASH_BOOST * dt; }
                if (Input.leftPressed) {  velocity.x -= DASH_BOOST * dt; }
                if (Input.rightPressed) { velocity.x += DASH_BOOST * dt; }

                if (Input.upPressed || Input.downPressed || Input.leftPressed || Input.rightPressed) {
                    dashCooldown = 90; // 1.5seconds
                    damageCooldown = 30;
                }
            }
        } else dashCooldown--;

        // diagonal movement correction
        int activeInputs = 0;
        bool inputs[4] = { Input.upPressed, Input.downPressed, Input.leftPressed, Input.rightPressed };
        for (bool b : inputs) activeInputs += (b ? 1 : 0);
        if (activeInputs == 2) velocity *= 0.85F; // slower on diagonal

        // update global player position
        GLOBAL_PLAYER_POSITON = position;
        GLOBAL_PLAYER_VELOCITY = velocity;
    }


    void damage(int _amount, vec2 _damager_pos, float _knockback=1500.0F) {
        if (damageCooldown == -1) {
            GLOBAL_PLAYER_TOTAL_HEALTH -= _amount;
            damageCooldown = 50;

            std::cout << GLOBAL_PLAYER_TOTAL_HEALTH << std::endl;
            if (GLOBAL_PLAYER_TOTAL_HEALTH == 0) REQUEST_RESTART = true;

            {
                // knockback
                vec2 knockDir = position - _damager_pos;
                knockDir = knockDir.normalized();
                velocity += knockDir * _knockback;
            }
        }
    }
};
