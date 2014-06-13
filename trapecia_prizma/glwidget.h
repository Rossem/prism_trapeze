
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>
#include <camera.h>
#include "box.h"
#include "prism.h"
#include <coord_axis.h>
#include <L.h>
#include <rotations_array.h>
#include<C:\Qt_projects\Eigen\Dense>
#include <sphere.h>
class QGLShaderProgram;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0, QGLWidget *shareWidget = 0);
    ~GLWidget();

    double aspect_ratio;
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void setClearColor(const QColor &color);
    Camera cam;

    QVector4D light_pos;

    void set_lp()
    {
        program->setUniformValue("light_pos",light_pos);
    }


    bool L_enable,prism_enable;
    double L_angle,prism_angle;
    bool first_step;

    float light_move_x;
    float light_move_y;
    float light_move_z;

signals:
    void clicked();
    void get_str(QString);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent * event);

private:
    QTimer *timer;
    QTime animation_timer;
    QMatrix4x4 v;
    QMatrix4x4 p;

    QGLFunctions *glFuncs;

    QColor clearColor;
    QPoint lastPos;
    GLuint textures[6];
    GLuint geom_texture;
    GLuint planet_texture[3];
    QGLShaderProgram *program;

    rotations_array rotations;
    qreal curr_rot;
    int curr_step;

    box* b1;
    box* b2;
    prism pr;
    L* word;

    sphere* sph1;
    //QVector<planet*> planets;

    coord_axis coordinate_axis;


private slots:
    void update_screen();
    void set_time_speed(int new_time_speed);
};

#endif
