#ifndef PRISM_H
#define PRISM_H

#include <QtOpenGL>

class prism
{
public:

    QGLFunctions* glfunc;
    QMatrix4x4 model;
    QMatrix4x4 add_rot;
    GLuint *textures;
    QVector<QVector3D> vertices;
    QVector<QVector4D> normals;
    QVector<QVector2D> texCoords;
    QGLShaderProgram *program;
    QVector<QVector4D> face_color;
    prism ()
    {
        qreal x=sqrt(1-0.25);
        //треуголная грань 1
        vertices.append(QVector3D(-0.5,0.0,0.5));
        vertices.append(QVector3D(0.5,0.0,0.5));
        vertices.append(QVector3D(0.0,x,0.5));
        for(int i=0;i<3;i++ ) normals.append(QVector3D(0,0,1));
        for(int i=0;i<3;i++ ) texCoords.append(QVector2D(0,0));

        //треуголная грань 2
        vertices.append(QVector3D(0.5,0.0,-0.5));
        vertices.append(QVector3D(-0.5,0.0,-0.5));
        vertices.append(QVector3D(0.0,x,-0.5));
        for(int i=0;i<3;i++ ) normals.append(QVector3D(0,0,-1));
        for(int i=0;i<3;i++ ) texCoords.append(QVector2D(0,0));

        //прямоуголная грань 1
        vertices.append(QVector3D(-0.5,0.0,0.5));
        vertices.append(QVector3D(-0.5,0.0,-0.5));
        vertices.append(QVector3D(0.5,0.0,-0.5));
        vertices.append(QVector3D(0.5,0.0,0.5));
        for(int i=0;i<4;i++ ) normals.append(QVector3D(0,-1,0));
        for(int i=0;i<4;i++ ) texCoords.append(QVector2D(0,0));
        //прямоуголная грань 2

        vertices.append(QVector3D(-0.5,0.0,0.5));
        vertices.append(QVector3D(0.0,x,0.5));
        vertices.append(QVector3D(0.0,x,-0.5));
        vertices.append(QVector3D(-0.5,0.0,-0.5));


        for(int i=0;i<4;i++ ) normals.append(QVector3D(-0.8660250378,0.5,0));
        for(int i=0;i<4;i++ ) texCoords.append(QVector2D(0,0));

        //прямоуголная грань 3
        vertices.append(QVector3D(0.0,x,0.5));
        vertices.append(QVector3D(0.5,0.0,0.5));
        vertices.append(QVector3D(0.5,0.0,-0.5));
        vertices.append(QVector3D(0.0,x,-0.5));

        for(int i=0;i<4;i++ ) normals.append(QVector3D(0.8660250378,0.5,0));
        for(int i=0;i<4;i++ ) texCoords.append(QVector2D(0,0));

        face_color.append(QVector4D(0,0,1,1));
        face_color.append(QVector4D(1,1,1,1));
        face_color.append(QVector4D(1,0,1,1));
        face_color.append(QVector4D(0.6,0.6,1,1));
        face_color.append(QVector4D(0.34,1,0,1));
    }


    void setshaderprog(QGLShaderProgram* new_prog)
    {
     program=new_prog;
    }

    void set_texures(GLuint* new_textures)
    {
        textures=new_textures;
    }

    void set_gl_func(QGLFunctions* in_glfunc)
    {
        glfunc=in_glfunc;
    }


    void rotate_around_point(qreal x,qreal y,qreal z,qreal angle)
    {
        QMatrix4x4 rot_m;
        rot_m.translate(x,y,z);
        rot_m.rotate(angle,0,0,1);
        rot_m.translate(-x,-y,-z);
        model=rot_m*model;
    }

    void rotate_around_point_add(qreal x,qreal y,qreal z,qreal angle)
    {
        add_rot.translate(x,y,z);
        add_rot.rotate(angle,0,1,0);
        add_rot.translate(-x,-y,-z);
    }

    void common_rotate(qreal x,qreal y,qreal z,qreal angle)
    {
        QMatrix4x4 r;
        r.rotate(angle, x, y, z );
        model=r*model;
    }

    void draw()
    {
        program->setUniformValue("model_matrix", add_rot*model);

        program->setAttributeArray
            (0, vertices.constData());
        program->setAttributeArray
            (1, texCoords.constData());
        program->setAttributeArray
            (2, normals.constData());

        program->setUniformValue("without_texture",1);
        program->setUniformValue("material",QVector4D(0.0,0.0,1.0,1));

        glDrawArrays(GL_TRIANGLES, 0, 3);
        program->setUniformValue("material",face_color[3]);
        glDrawArrays(GL_TRIANGLES, 3, 3);
        program->setUniformValue("material",face_color[4]);
        for(int i=0;i<3;i++)
        {
            program->setUniformValue("material",face_color[i]);
            glDrawArrays(GL_QUADS, 6+i*4, 4);
        }
    }
};

#endif // PRISM_H
