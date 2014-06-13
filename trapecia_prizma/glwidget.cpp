#include "glwidget.h"
//#include <QtGui>




GLWidget::GLWidget(QWidget *parent, QGLWidget *shareWidget)
    : QGLWidget(parent, shareWidget)
{
 /*   QGLFormat frmt; // создать формат по умолчанию
       frmt.setSampleBuffers(true); // задать простую буферизацию
       frmt.setSamples(4);
       setFormat(frmt); // установить формат в контекст*/
    QGLContext *con;
    QGLFormat fm;
    fm.setProfile(QGLFormat::CoreProfile);
    fm.setAlpha(true);
    fm.setDoubleBuffer(true);
    fm.setVersion(3,3);
    fm.setSampleBuffers(true);
    fm.setSamples(4);
    fm.setAccum(true);
    fm.setDepth(true);
    fm.setDirectRendering(true);
    con=new QGLContext(fm);
    con->setFormat(fm);
    con->create();
    con->makeCurrent();

    clearColor = Qt::black;
    program = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_screen()));
    timer->start(10);

    Vector3d t(0,0,15);

    cam.setPosition(&t);

    light_pos=QVector4D(0,5,0,0);
    b1 =new box();

    sph1=new sphere();
    sph1->make_sphere(0,0,0,0.1,20);

    prism_enable=true;
    L_enable=false;
    prism_angle=1;
    L_angle=1;

    light_move_x = 0;
    light_move_y = 0;
    light_move_z = 0;

}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(200, 200);
}


void GLWidget::setClearColor(const QColor &color)
{
    clearColor = color;
    updateGL();
}

void GLWidget::initializeGL()
{
    glFuncs=new QGLFunctions(QGLContext::currentContext());
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    glEnable(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    #define PROGRAM_VERTEX_ATTRIBUTE 0
    #define PROGRAM_TEXCOORD_ATTRIBUTE 1
    #define PROGRAM_NORMAL_ATTRIBUTE 2

    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);

    vshader->compileSourceFile(QLatin1String(":/vertex_shader.vert"));

    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);
//
    fshader->compileSourceFile(QLatin1String(":/fragment_shader.frag"));

    program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);
    program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    program->bindAttributeLocation("normal", PROGRAM_NORMAL_ATTRIBUTE);
    program->link();

    program->bind();
    program->setUniformValue("texture", 0);
    program->setUniformValue("texture2", 1);
    program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    program->enableAttributeArray(PROGRAM_NORMAL_ATTRIBUTE);

    program->setUniformValue("ambient", QVector4D(0.2,0.2,0.2,1));
    program->setUniformValue("material", QVector4D(1.0,1.0,1.0,1));
    program->setUniformValue("light_pos",light_pos);
    program->setUniformValue("light_intensity", QVector4D(1.0,1.0,1.0,1));
     //program->setUniformValue("without_texture",1);

    coordinate_axis.setshaderprog(program);
    b1->setshaderprog(program);
    b1->set_texures(textures);

    pr.setshaderprog(program);

    pr.model.translate(0.5,0.36625,0);

    word=new L(program);
    rotation_point p;
    //1
    p=rotation_point(1.0,0.36625,0,180);
    rotations.points.append(p);
    //2
    p=rotation_point(1.5,-0.5,0,240);
    rotations.points.append(p);
    //3
    p=rotation_point(0.5,-0.5,0,120);
    rotations.points.append(p);
    //4
    p=rotation_point(-0.5,-0.5,0,120);
    rotations.points.append(p);
    //5
    p=rotation_point(-1.5,-0.5,0,240);
    rotations.points.append(p);
    //6
    p=rotation_point(-1.0,0.36625,0,180);
    rotations.points.append(p);
    //7
    p=rotation_point(0.0,0.36625,0,120);
    rotations.points.append(p);

    curr_step=0;

    sph1->setshaderprog(program);
    first_step=true;
}

void GLWidget::paintGL()
{
    glClearColor(0.5f,0.7f,0.5f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cam.getViewMatrix(&v);
    v=v.transposed();
    program->setUniformValue("view_matrix", v);

    QMatrix4x4 pr_matr=pr.add_rot*pr.model;

    program->setUniformValue("model_prism",pr_matr);
    program->setUniformValue("model_L_b1", word->b1.model);

    program->setUniformValue("shadowed", true);
    word->draw();

    program->setUniformValue("box_numb",0);
    program->setUniformValue("shadowed", true);
    pr.draw();
    //pr.rotate_around_point(0.5,0,0,-1);
    if (prism_enable)
    {
        if(prism_angle>0)
        {
            if (!first_step)
            {
                pr.rotate_around_point
                        (rotations.points[curr_step].x,rotations.points[curr_step].y,rotations.points[curr_step].z,-1.0);
                curr_rot--;
                if(curr_rot==0) first_step=true;
                if (!first_step) goto end;
                else
                {
                    if(curr_step==(rotations.points.size()-1)) curr_step=0;
                    else curr_step++;
                    curr_rot=0;
                }
            }
            pr.rotate_around_point
                 (rotations.points[curr_step].x,rotations.points[curr_step].y,rotations.points[curr_step].z,-1.0);
            curr_rot++;
            if(curr_rot==(rotations.points[curr_step].angle))
            {
              curr_step++;
              curr_rot=0;
              if(curr_step==(rotations.points.size()))
             {
              //curr_rot=0;
              curr_step=0;
              }
        }
        }
        else
        {

            if (first_step)
            {
                pr.rotate_around_point
                        (rotations.points[curr_step].x,rotations.points[curr_step].y,rotations.points[curr_step].z,1.0);
                curr_rot--;
                if(curr_rot==0) first_step=false;
                if (first_step) goto end;
                else
                {
                    if(curr_step==0) curr_step=rotations.points.size()-1;
                    else curr_step--;
                    curr_rot=0;
                }
            }

            pr.rotate_around_point
                    (rotations.points[curr_step].x,rotations.points[curr_step].y,rotations.points[curr_step].z,1.0);
            curr_rot++;
            if(curr_rot==(rotations.points[curr_step].angle))
            {

                curr_rot=0;
                if(curr_step==0)
                {
                //curr_rot=0;
                curr_step=rotations.points.size()-1;
                }
                else curr_step--;

            }
            end:;
        }
    }

    if(L_enable)
    {
        pr.rotate_around_point_add(0.0,1.5,0,L_angle);
        word->rotate_around_point(0.0,1.5,0,L_angle);
    }

    //light move
    QVector4D light_move( light_move_x, light_move_y, light_move_z, 1);
    light_pos += light_move;

    set_lp();

    QMatrix4x4 light_matr;
    light_matr.translate(light_pos.x(),light_pos.y(),light_pos.z());
    sph1->model=light_matr;
    sph1->draw();
    //оси рисуются первыми или последними так как чистят z-буффер
    coordinate_axis.draw(&cam,aspect_ratio);
}


void GLWidget::set_time_speed(int new_time_speed)  //SLOT
{

}

void GLWidget::resizeGL(int width, int height)
{
    aspect_ratio=width;
    aspect_ratio/=height;
    glViewport(0 ,0, width, height);
    QMatrix4x4 new_perspective;
    p=new_perspective;
    p.perspective(60,aspect_ratio,1,10000);
    program->setUniformValue("proj_matrix", p);
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        cam.pitch(dy/360.0f);
        cam.yaw(dx/360.0f);
    }
    if (event->buttons() & Qt::RightButton) {
        cam.fly(dy/60.0f);
        cam.strafe(-dx/60.0f);
    }
    lastPos = event->pos();
    //get_mpos(lastPos.);

}

void GLWidget::mouseReleaseEvent(QMouseEvent * /* event */)
{
    emit clicked();
}

void GLWidget::wheelEvent(QWheelEvent * event)
{
    cam.walk(event->delta()/400.0f);
}

void GLWidget::update_screen()   //SLOT
{
    updateGL();
}

