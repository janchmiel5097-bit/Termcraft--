#pragma once
#include "math.hpp"
#include "object/entity.hpp"
#include <memory>
#include <vector>

inline  const       int     WINDOW_WIDTH                        =       1000;
inline  const       int     WINDOW_HEIGHT                       =       800;
inline  std::vector<std::unique_ptr<Entity>> ENTITIES                   {};

inline  unsigned    int     GLOBAL_UPGRADE_PLAYER_MAX_HEALTH    =       10;

inline              vec2    GLOBAL_PLAYER_POSITON               =       vec2(0, 0);
inline              vec2    GLOBAL_PLAYER_SIZE                  =       vec2(0, 0);
inline  unsigned    int     GLOBAL_PLAYER_TOTAL_HEALTH          =       GLOBAL_UPGRADE_PLAYER_MAX_HEALTH;
