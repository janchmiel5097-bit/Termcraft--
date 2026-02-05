#pragma once

// OLD

// #include <cmath>
// #include "entity.hpp"
// #include "../global.hpp"

// struct BouncerEntity : Entity {
//     float speed = 200.0f;
//     float direction = 127.0f; // initial angle in degrees

//     BouncerEntity(vec2 _pos, vec2 _size, float _dir) : direction(_dir) {
//         position = _pos;
//         size = _size;
//         color = vec4(0x1147a3ff);
//     }

//     virtual ~BouncerEntity() = default;

//     void update(float dt) override {
//         // direction -> radians
//         float rad = direction * (3.14159265f / 180.0f);

//         // some color magic
//         {
//             float targetR = std::fmod(color.r + (rad / 180.0f), 1.0f);
//             float targetG = std::fmod(color.g + (rad / 180.0f), 1.0f);
//             float targetB = std::fmod(color.b + (rad / 180.0f), 1.0f);

//             float lerpSpeed = 50.0f;
//             color.r = lerp(color.r, targetR, dt * lerpSpeed);
//             color.g = lerp(color.g, targetG, dt * lerpSpeed);
//             color.b = lerp(color.b, targetB, dt * lerpSpeed);
//         }

//         // move
//         position.x += std::cos(rad) * speed * dt;
//         position.y += std::sin(rad) * speed * dt;

//         // bounce horizontally
//         if (position.x <= 0.0f) {
//             position.x = 0.0f;
//             direction = 180.0f - direction; // reflect horizontally
//         }
//         else if (position.x + size.x >= WINDOW_WIDTH) {
//             position.x = WINDOW_WIDTH - size.x;
//             direction = 180.0f - direction;
//         }

//         // bounce vertically
//         if (position.y <= 0.0f) {
//             position.y = 0.0f;
//             direction = -direction; // reflect vertically
//         }
//         else if (position.y + size.y >= WINDOW_HEIGHT) {
//             position.y = WINDOW_HEIGHT - size.y;
//             direction = -direction;
//         }

//         // keep angle in [-180, 180] for sanity
//         if (direction > 180.0f) direction -= 360.0f;
//         if (direction < -180.0f) direction += 360.0f;
//     }
// };
