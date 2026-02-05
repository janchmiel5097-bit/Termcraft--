#pragma once
#include "math.hpp"
#include "object/entity.hpp"
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

inline              bool    REQUEST_RESTART                     =       false;
inline  const       int     WINDOW_WIDTH                        =       1450;
inline  const       int     WINDOW_HEIGHT                       =       900;
inline  std::vector<std::unique_ptr<Entity>> ENTITIES                   {};
inline  std::vector<std::unique_ptr<Entity>> PENDING_ENTITIES   =       {};

inline  unsigned    int     GLOBAL_UPGRADE_PLAYER_MAX_HEALTH    =       10;

inline              vec2    GLOBAL_PLAYER_POSITON               =       vec2(0, 0);
inline              vec2    GLOBAL_PLAYER_VELOCITY              =       vec2(0, 0);
inline              vec2    GLOBAL_PLAYER_SIZE                  =       vec2(0, 0);
inline  unsigned    int     GLOBAL_PLAYER_TOTAL_HEALTH          =       GLOBAL_UPGRADE_PLAYER_MAX_HEALTH;

inline void restart(); // from main
