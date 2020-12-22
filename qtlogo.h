#ifndef QTLOGO_H
#define QTLOGO_H

#include <QGLWidget>
#include "glwidget.h"
#include "window.h"

// The geometry is divided into a list of parts which may be rendered in different ways. 
// The data in the Geometry class is stored in QVector<QVector3D> members which are convenient for use with OpenGL 
// because they expose raw contiguous floating point values via the constData() method.
// Methods are included for adding new vertex data, either with smooth normals, or facetted normals; 
// and for enabling the geometry ready for rendering.
struct Geometry
{
	QVector<GLushort> faces;
	QVector<QVector3D> vertices;
	QVector<QVector3D> normals;
	void appendSmooth(const QVector3D &a, const QVector3D &n, int from);
	void appendFaceted(const QVector3D &a, const QVector3D &n);
	void finalize();
	void loadArrays() const;
};

// The model-view matrix is saved and then restored so that any transformation does not affect other parts of the scene.
class Patch
{
public:
	enum Smoothing { Faceted, Smooth };
	Patch(Geometry *);
	void setSmoothing(Smoothing s) { sm = s; }
	void translate(const QVector3D &t);
	void rotate(qreal deg, QVector3D axis);
	void draw() const;
	void addTri(const QVector3D &a, const QVector3D &b, const QVector3D &c, const QVector3D &n);
	void addQuad(const QVector3D &a, const QVector3D &b,  const QVector3D &c, const QVector3D &d);

	GLushort start;
	GLushort count;
	GLushort initv;

	GLfloat faceColor[4];
	QMatrix4x4 *mat;
	Smoothing sm;
	Geometry *geom;
};

// This class encapsulates the OpenGL geometry data which will be rendered in the basic 3D scene.
class QtLogo : public QObject
{
public:
	QtLogo(QObject *parent, int d = 64, qreal s = 1.0);
	~QtLogo();
	void setColor(QColor c);
	void draw() const;
private:
	void buildGeometry(int d, qreal s);

	QList<Patch *> parts;
	Geometry *geom;
};
#endif
