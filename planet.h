
#pragma once

#include "vector"
#include "math.h"
#include <QOpenGLTexture>
using namespace std;

struct point
{
    float x;
    float y;
    float z;


    point(float _x = 0, float _y = 0, float _z = 0)
        : x(_x), y(_y), z(_z)
    {
    }

    void normalize()
    {
        float len = sqrtf(x * x + y * y + z * z);

        x /= len;
        y /= len;
        z /= len;
    }
};


class planet
{
public :
    planet(point _pos, point _axes_rev, float _size, float _rev_speed, float _rota_speed, bool _sun, const char *texname);
    virtual ~planet();

    void update(float timepass);
    void draw();

    void add_secondary(planet* p);
private :

    vector<planet*> m_secondary;

    point m_pos;

    float m_size;

    bool m_sun;

    float m_rev_speed;

    float m_rota_speed;

    float m_revolution;

    float m_rotation;

    point m_axes;

    point m_axes_rev;

    float m_distance2sun;

    GLuint m_tex;

    QOpenGLTexture * m_texture;


};
