#ifndef L_H
#define L_H

#include <QtOpenGL>
#include <box.h>

class L
{
    private:
    QGLShaderProgram *program;


    public:
    box b1;
    QMatrix4x4 rot;

    L(QGLShaderProgram* new_prog)
    {
        program=new_prog;
        b1.setshaderprog(program);

        b1.model=rot*b1.model;

        b1.face_color.append(QVector4D(1,0,0,0));
        b1.face_color.append(QVector4D(1,0.5,0,0));
        b1.face_color.append(QVector4D(1,0,0.5,0));
        b1.face_color.append(QVector4D(0.1,0.2,0.9,0));
        b1.face_color.append(QVector4D(0.112,1,0.545,0));
        b1.face_color.append(QVector4D(0.7,0,0.7,0));
    }

    void rotate_around_point(qreal x,qreal y,qreal z,qreal angle)
    {
        QMatrix4x4 rot_m;
        rot_m.translate(x,y,z);
        rot_m.rotate(angle,0,1,0);
        rot_m.translate(-x,-y,-z);
        b1.model=rot_m*b1.model;
    }

    void common_rotate(qreal x,qreal y,qreal z,qreal angle)
    {
        QMatrix4x4 r;
        r.rotate(angle, x, y, z );
        b1.model=r*b1.model;
    }

    void draw()
    {
        program->setUniformValue("box_numb",10);
        b1.draw();
    }

};

#endif // L_H
