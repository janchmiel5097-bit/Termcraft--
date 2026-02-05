#pragma once
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include "entity.hpp"
#include "../global.hpp"
#include "player.hpp"

struct EnemyEntity :Entity {
    float speed = (std::rand() % 70)+15.0F;

    explicit EnemyEntity(
        vec2 _size = vec2(30.0F, 30.0F),
        vec2 _pos = vec2((std::rand() % WINDOW_WIDTH), (std::rand() % WINDOW_HEIGHT)),
        vec4 _color = vec4(0.8, 0.1, 0.0)
    ) {
        size = _size;
        position = _pos;
        color = _color;
    }

    virtual ~EnemyEntity() = default;

    void update(float dt) override {

        vec2 dir = GLOBAL_PLAYER_POSITON - position;

        if (dir.x != 0.0F || dir.y != 0.0F) {
            float length = std::sqrt((dir.x * dir.x) + (dir.y * dir.y));
            vec2 normalizedDir = dir / length;

            // move
            position += normalizedDir * speed * dt;

            // clamp within bounds
            position.x = std::clamp(position.x, 0.0F, WINDOW_WIDTH - size.x);
            position.y = std::clamp(position.y, 0.0F, WINDOW_HEIGHT - size.y);
        }

        {
            bool playerOverlap = position.x + size.x >= GLOBAL_PLAYER_POSITON.x &&
                       position.x <= GLOBAL_PLAYER_POSITON.x + GLOBAL_PLAYER_SIZE.x &&
                       position.y + size.y >= GLOBAL_PLAYER_POSITON.y &&
                       position.y <= GLOBAL_PLAYER_POSITON.y + GLOBAL_PLAYER_SIZE.y;
            if (playerOverlap && !ENTITIES.empty()) {
                auto* PLAYER = dynamic_cast<PlayerEntity*>(ENTITIES[0].get());
                PLAYER->damage(1, position);
            }
        }

    }

    void render() override {
        glColor4f(color.r, color.g, color.b, color.a);

        const int segments = 40;                // more = smoother
        const float radius = size.x * 0.5F;     // use half width as radius

        const float cx = position.x + radius;   // circle center x
        const float cy = position.y + radius;   // circle center y

        glBegin(GL_TRIANGLE_FAN);
            // center of the circle
            glVertex2f(cx, cy);

            // circle edge
            for (int i = 0; i <= segments; i++) {
                float angle = 2.0F * M_PI * i / segments;
                float x = cx + (radius * std::cos(angle));
                float y = cy + (radius * std::sin(angle));
                glVertex2f(x, y);
            }
        glEnd();
    }
};
