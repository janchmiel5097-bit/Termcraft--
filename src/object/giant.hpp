#pragma once
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "enemy.hpp"
#include "../global.hpp"
#include "entity.hpp"
#include "player.hpp"

struct GiantEntity : EnemyEntity {

    struct ShriekAttackEnemy :EnemyEntity {
        unsigned int liveFrames = 20; // disappear after X frames

        explicit ShriekAttackEnemy(vec2 _pos, vec2 _size) {
            position = _pos;
            size = _size;
            color = vec4(0.8f, 0.1f, 0.0f);
        }

        void update(float /*dt*/) override {
            if (liveFrames == 0) toDelete = true;
            else liveFrames--;

            // collision with player
            for (auto& e : ENTITIES) {
                if (auto* PLAYER = dynamic_cast<PlayerEntity*>(e.get())) {
                    bool overlap =
                        position.x + size.x >= GLOBAL_PLAYER_POSITON.x &&
                        position.x <= GLOBAL_PLAYER_POSITON.x + GLOBAL_PLAYER_SIZE.x &&
                        position.y + size.y >= GLOBAL_PLAYER_POSITON.y &&
                        position.y <= GLOBAL_PLAYER_POSITON.y + GLOBAL_PLAYER_SIZE.y;
                    if (overlap) {
                        PLAYER->damage(1, position, 250.0F);
                    }
                }
            }
        }
    };

    vec4 def_color;
    float speed = (std::rand() % 70) + 70.0F;
    unsigned int attackCooldown = (std::rand() % 60) + 100;
    unsigned int loadingCooldown = (std::rand() % 120) + 240;

    explicit GiantEntity(
        vec2 _size = vec2(60.0F, 60.0F),
        vec2 _pos = vec2((std::rand() % WINDOW_WIDTH), (std::rand() % WINDOW_HEIGHT)),
        vec4 _color = vec4(0.3, 0.5, 0.3)
    ) : def_color(_color) {
        size = _size;
        position = _pos;
        color = _color;
    }

    void update(float dt) override {
        vec2 dir = GLOBAL_PLAYER_POSITON - position;

        if (loadingCooldown == 0) {
            color.r = std::fmod((color.r + 0.005F), 1.0F);
            color.g = std::fmod((color.g + 0.005F), 1.0F);
            color.g = std::fmod((color.g + 0.005F), 1.0F);

            // attack cooldown
            if (attackCooldown == 0) {
                attackCooldown = (std::rand() % 60) + 100; // frames until next attack
                loadingCooldown = (std::rand() % 120) + 240;
                color = def_color;

                vec2 shriekPos = position;
                vec2 shriekSize = vec2(40.0f, 40.0f);

                vec2 normalizedDir = (((GLOBAL_PLAYER_POSITON + GLOBAL_PLAYER_VELOCITY * GLOBAL_PLAYER_POSITON.length()/999999999.0F) - position)).normalized();

                // spawn balls along the line from Giant to player
                const float step = 5.0F; // distance between shrieks
                float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);

                for (float d = 0.0F; d < distance; d += step) {
                    PENDING_ENTITIES.push_back(
                        std::make_unique<ShriekAttackEnemy>(shriekPos + normalizedDir * d, shriekSize)
                    );
                    shriekSize = vec2( std::max(shriekSize.x - 0.25F, 10.0F), std::max(shriekSize.y - 0.25F, 10.0F) );
                }

            } else {
                attackCooldown--;
            }
        }
        else {
            // move toward player
            if (dir.x != 0.0F || dir.y != 0.0F) {
                vec2 normalizedDir = dir.normalized();
                position += normalizedDir * speed * dt;

                position.x = std::clamp(position.x, 0.0F, WINDOW_WIDTH - size.x);
                position.y = std::clamp(position.y, 0.0F, WINDOW_HEIGHT - size.y);
            }

            loadingCooldown--;
        }

        // collide with player directly
        for (auto& e : ENTITIES) {
            if (auto* PLAYER = dynamic_cast<PlayerEntity*>(e.get())) {
                bool overlap =
                    position.x + size.x >= GLOBAL_PLAYER_POSITON.x &&
                    position.x <= GLOBAL_PLAYER_POSITON.x + GLOBAL_PLAYER_SIZE.x &&
                    position.y + size.y >= GLOBAL_PLAYER_POSITON.y &&
                    position.y <= GLOBAL_PLAYER_POSITON.y + GLOBAL_PLAYER_SIZE.y;
                if (overlap) PLAYER->damage(1, position);
            }
        }
    }
};
