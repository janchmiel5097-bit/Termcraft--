#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include "enemy.hpp"
#include "entity.hpp"
#include "../global.hpp"
#include "player.hpp"

struct ArcherEntity :EnemyEntity {

    struct ArrowAttackEntity :EnemyEntity {
        float speed;
        vec2 direction;

        ArrowAttackEntity(vec2 _dir, vec2 _pos, float _speed) : speed(_speed), direction(_dir.normalized()) {
            position = _pos;
            size = vec2(10,10);
            color = vec4(0.8f,0.1f,0.0f);
        }
        void update(float dt) override {
            // move
            position += direction * speed * dt;

            // mark out-of-bounds for deletion
            if (position.x < -size.x || position.x > WINDOW_WIDTH ||
                position.y < -size.y || position.y > WINDOW_HEIGHT) {
                toDelete = true;
            }

            // player collision
            PlayerEntity* PLAYER = nullptr;
            for (auto& e : ENTITIES) {
                PLAYER = dynamic_cast<PlayerEntity*>(e.get());
                if (PLAYER) break;
            }

            if (PLAYER) {
                bool playerOverlap =
                    position.x + size.x >= GLOBAL_PLAYER_POSITON.x &&
                    position.x <= GLOBAL_PLAYER_POSITON.x + GLOBAL_PLAYER_SIZE.x &&
                    position.y + size.y >= GLOBAL_PLAYER_POSITON.y &&
                    position.y <= GLOBAL_PLAYER_POSITON.y + GLOBAL_PLAYER_SIZE.y;

                if (playerOverlap) {
                    PLAYER->damage(1, position, 750.0f);
                    toDelete = true; // mark for deletion
                }
            }
        }
    };

    float speed = (std::rand() % 20)+15.0F;
    float arrow_speed = 600.0F;
    bool arrow_type = false;
    unsigned int arrowCooldown = (std::rand() % 30);

    explicit ArcherEntity(
        vec2 _size = vec2(30.0F, 30.0F),
        vec2 _pos = vec2((std::rand() % WINDOW_WIDTH), (std::rand() % WINDOW_HEIGHT)),
        vec4 _color = vec4(0.0, 0.2, 0.7)
    ) {
        size = _size;
        position = _pos;
        color = _color;
    }

    ~ArcherEntity() override = default;

    void update(float dt) override {

        vec2 dir = GLOBAL_PLAYER_POSITON - position;
        if (arrowCooldown == 0) {
            arrowCooldown = (std::rand() % 50)+40.0F;

            vec2 final_dir = dir;

            if (arrow_type) {
                float pred_time = GLOBAL_PLAYER_POSITON.length()/arrow_speed;
                vec2 pred_pos = GLOBAL_PLAYER_POSITON + GLOBAL_PLAYER_VELOCITY * pred_time;
                final_dir = (pred_pos - position);
            }

            arrow_type = !arrow_type;

            PENDING_ENTITIES.push_back(std::make_unique<ArrowAttackEntity>(final_dir, position, arrow_speed));
        }
        else {
            arrowCooldown--;
        }


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
};
