#pragma once
#include "../math.hpp"
#include "../input.hpp"
#include <GL/gl.h>

struct Entity {
    vec2 position;
    vec2 size;
    vec4 color;
    bool toDelete = false;

    virtual void update(float /*dt*/) {}

    virtual void render() {
        // color
        glColor4f(color.r, color.g, color.b, color.a);

        // rectangle
        glBegin(GL_QUADS);
            glVertex2f(position.x, position.y);
            glVertex2f(position.x + size.x, position.y);
            glVertex2f(position.x + size.x, position.y + size.y);
            glVertex2f(position.x, position.y + size.y);
        glEnd();
    }
};
