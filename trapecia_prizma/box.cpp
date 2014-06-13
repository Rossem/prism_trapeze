#include "box.h"

box::box()
{
    static const float coords[6][4][3] = {
        { { +3, -1, -1 }, { -3, -1, -1 }, { -2, +0.73205, -1 }, { +2, +0.73205, -1 } },
        { { +2, +0.73205, -1 }, { -2, +0.73205, -1 }, { -2, +0.73205, +1 }, { +2, +0.73205, +1 } },
        { { +3, -1, +1 }, { +3, -1, -1 }, { +2, +0.73205, -1 }, { +2, +0.73205, +1 } },
        { { -3, -1, -1 }, { -3, -1, +1 }, { -2, +0.73205, +1 }, { -2, +0.73205, -1 } },
        { { +3, -1, +1 }, { -3, -1, +1 }, { -3, -1, -1 }, { +3, -1, -1 } },
        { { -3, -1, +1 }, { +3, -1, +1 }, { +2, +0.73205, +1 }, { -2, +0.73205, +1 } }
    };

   /*for (int j=0; j < 6; ++j) {
        textures[j] = gl->bindTexture
         (QPixmap(QString(":/images/side%1.png").arg(j + 1)), GL_TEXTURE_2D);
    }*/

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            texCoords.append
                (QVector2D(j == 0 || j == 3, j == 0 || j == 1));
            vertices.append
                (QVector3D(coords[i][j][0]*0.5,coords[i][j][1]*0.5,
                           coords[i][j][2]*0.5));
        }


        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 4; ++j) {
                if(i==0) normals.append(QVector4D(0,0,-1,0.0));
                if(i==1) normals.append(QVector4D(0,1,0,0.0));
                if(i==2) normals.append(QVector4D(+0.8660250378,0.5,0,0));
                if(i==3) normals.append(QVector4D(-0.8660250378,0.5,0,0));
                if(i==4) normals.append(QVector4D(0,-1,0,0.0));
                if(i==5) normals.append(QVector4D(0,0,1,0.0));
            }
        }

    }
}

void box::setshaderprog(QGLShaderProgram* new_prog)
{
    program=new_prog;
}
void box::set_texures(GLuint *new_textures)
{
    textures=new_textures;
}

void box::set_gl_func(QGLFunctions* in_glfunc)
{
    glfunc=in_glfunc;
}

void box::draw()
{

program->setUniformValue("model_matrix", model);

program->setAttributeArray
    (0, vertices.constData());
program->setAttributeArray
    (1, texCoords.constData());
program->setAttributeArray
    (2, normals.constData());

program->setUniformValue("without_texture",1);
 program->setUniformValue("material",QVector4D(1.0,1.0,1.0,1));

for (int i = 0; i < 6; ++i)
{
    //glBindTexture(GL_TEXTURE_2D, textures[i]);
    program->setUniformValue("material",face_color[i]);
    glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
}

}
