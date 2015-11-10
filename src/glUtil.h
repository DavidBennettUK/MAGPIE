#ifndef GLUTIL_H
#define GLUTIL_H

#include <QGLFunctions>
#include <cmath>

static const double PI = 3.14159265358979323846264338327950288419717;
static double PI_OVER_180 = PI / 180.0;

namespace glUtil
{
    inline void drawUnitSquare()
    {
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
    }

    inline void drawUnitCircle(int segments = 360)
    {
        for (int i = 0; i < segments; i++)
            glVertex2f(cos(i * PI_OVER_180), sin(i * PI_OVER_180));
    }

    inline void drawUnitTriangle()
    {
        glVertex2f(0.0f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
    }

    inline void drawLine(float x1, float y1, float x2, float y2, float thickness = 1.0f)
    {
        float px = -(y2 - y1); float py = x2 - x1;
        float length = sqrt(px * px + py * py);
        px /= length; py /= length;

        glVertex2f(x1 - px * thickness, y1 - py * thickness);
        glVertex2f(x1 + px * thickness, y1 + py * thickness);
        glVertex2f(x2 + px * thickness, y2 + py * thickness);
        glVertex2f(x2 - px * thickness, y2 - py * thickness);
    }
}

#endif // GLUTIL_H
