#include "planet.h"
#include <string.h>
#include <stdio.h>
#include "math.h"
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QDebug>
#pragma warning(disable : 4996)


planet::planet(point _pos, point _axes_rev, float _size, float _rev_speed, float _rota_speed, bool _sun, const char* texname)
    : m_pos(_pos), m_axes_rev(_axes_rev), m_size(_size), m_sun(_sun), m_tex(0),
      m_rev_speed(_rev_speed), m_rota_speed(_rota_speed),
     m_revolution(0),m_rotation(0), m_distance2sun(_pos.x),
      m_axes((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX)
{
    m_axes.normalize();

    if (! texname )
        return;

    QImage srcportraitImage;
    srcportraitImage.load( texname );

    m_texture =
            new QOpenGLTexture( srcportraitImage.mirrored(), QOpenGLTexture::MipMapGeneration::DontGenerateMipMaps );
    m_texture->setWrapMode( QOpenGLTexture::Repeat);
    m_texture->setMinificationFilter( QOpenGLTexture::Linear );
    m_texture->setMagnificationFilter( QOpenGLTexture::Linear );
    m_texture->create();


    m_tex = m_texture->textureId();

    qDebug()<<"m_tex"<<m_tex;

    m_texture->bind(0);


}

planet::~planet()
{
    for (size_t i = 0; i < m_secondary.size(); ++i)
        delete[] m_secondary[i];
}

void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)
{
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat)iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat)iSlices;
    GLfloat ds = 1.0f / (GLfloat)iSlices;
    GLfloat dt = 1.0f / (GLfloat)iStacks;
    GLfloat t = 1.0f;
    GLfloat s = 0.0f;
    GLint i, j;

    for (i = 0; i < iStacks; i++)
    {
        GLfloat rho = (GLfloat)i * drho;
        GLfloat srho = (GLfloat)(sin(rho));
        GLfloat crho = (GLfloat)(cos(rho));
        GLfloat srhodrho = (GLfloat)(sin(rho + drho));
        GLfloat crhodrho = (GLfloat)(cos(rho + drho));


        glBegin(GL_TRIANGLE_STRIP);
        s = 0.0f;
        for (j = 0; j <= iSlices; j++)
        {
            GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
            GLfloat stheta = (GLfloat)(-sin(theta));
            GLfloat ctheta = (GLfloat)(cos(theta));

            GLfloat x = stheta * srho;
            GLfloat y = ctheta * srho;
            GLfloat z = crho;

            glTexCoord2f(s, t);
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);

            x = stheta * srhodrho;
            y = ctheta * srhodrho;
            z = crhodrho;
            glTexCoord2f(s, t - dt);
            s += ds;
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
        }
        glEnd();

        t -= dt;
    }
}

void draw_circle()
{
    static GLuint uList = 0;

    if (uList == 0)
    {

        uList = glGenLists(1);
        glNewList(uList, GL_COMPILE);
        glBegin(GL_LINE_STRIP);
        glColor3f(0.5, 0.5, 0.5);
        for (int x = 0; x <= 36; ++x)
        {
            float ay = 3.141592654f * x * 10 / 180.f;
            point v;
            v.x = sinf(ay);
            v.y = 0;
            v.z = cosf(ay);

            glVertex3f(v.x, v.y, v.z);
        }
        glEnd();
        glEndList();
    }

    glCallList(uList);
}

void planet::update(float timepass)
{
   m_revolution += timepass * m_rev_speed;
   m_rotation += timepass * m_rota_speed;

    for (size_t i = 0; i < m_secondary.size(); ++i)
        m_secondary[i]->update(timepass);
}

void planet::draw()
{
    if (m_sun)
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        for (size_t i = 0; i < m_secondary.size(); ++i)
        {
            glPushMatrix();
            glScalef(m_secondary[i]->m_distance2sun, m_secondary[i]->m_distance2sun, m_secondary[i]->m_distance2sun);
            draw_circle();
            glPopMatrix();
        }

        glEnable(GL_TEXTURE_2D);

    }
    else
        glDisable(GL_LIGHTING);

    glPushMatrix();
    glRotatef(m_revolution, m_axes_rev.x, m_axes_rev.y, m_axes_rev.z);
    glTranslatef(m_pos.x, m_pos.y, m_pos.z);
    glPushMatrix();
    glRotatef(m_rotation, m_axes.x, m_axes.y, m_axes.z);
    glScalef(m_size, m_size, m_size);
    glBindTexture(GL_TEXTURE_2D, m_tex);
    gltDrawSphere(1.0,60,60);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    for (size_t i = 0; i < m_secondary.size(); ++i)
        m_secondary[i]->draw();

    glPopMatrix();

    glDisable(GL_LIGHTING);

}

void planet::add_secondary(planet* p)
{
    m_secondary.push_back(p);
}
