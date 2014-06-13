#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glw=new GLWidget();
    ui->screens_layout->addWidget(glw);
    connect(glw,SIGNAL(get_str(QString)),this,SLOT(set_text(QString)));


    move_sens=3;
    start_param_validator=new QDoubleValidator();

    setWindowTitle("shadow.exe");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //set_text("press");
    switch (event->key()) {
    //cam walking
      case  Qt::Key_W:
        glw->cam.walk(0.2*move_sens);
          break;
      case  Qt::Key_S:
        glw->cam.walk(-0.2*move_sens);
          break;
      case Qt::Key_A:
        glw->cam.strafe(-0.2*move_sens);
          break;
      case  Qt::Key_D:
      glw->cam.strafe(0.2*move_sens);
          break;
      case Qt::Key_Z:
      glw->cam.fly(0.2*move_sens);
          break;
      case  Qt::Key_X:
      glw->cam.fly(-0.2*move_sens);
          break;
      //cam turning
    case Qt::Key_8:
      glw->cam.pitch(3.14/90);
        break;
    case  Qt::Key_5:
    glw->cam.pitch(-3.14/90);
        break;
    case Qt::Key_6:
    glw->cam.yaw(-3.14/90);
        break;
    case  Qt::Key_4:
    glw->cam.yaw(3.14/90);
        break;


    //light moving
    case  Qt::Key_I:
        glw->light_pos+=QVector4D(0,0,(float)-0.1,0);
    glw->set_lp();
        break;
    case Qt::Key_K:
        glw->light_pos+=QVector4D(0,0,(float)0.1,0);
    glw->set_lp();
        break;
    case  Qt::Key_J:
        glw->light_pos+=QVector4D(-0.1,0,0,0);
    glw->set_lp();
        break;
    case  Qt::Key_L:
        glw->light_pos+=QVector4D(0.1,0,0,0);
    glw->set_lp();;
        break;
   case  Qt::Key_N:
        glw->light_pos+=QVector4D(0,0.1,0,0);
    glw->set_lp();
        break;
   case  Qt::Key_M:
        glw->light_pos+=QVector4D(0,-0.1,0,0);
   glw->set_lp();;
        break;
    }

}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
   //set_text("release");
}




void MainWindow::set_move_sens(int new_move_sens)
{
    move_sens=new_move_sens;
}

void MainWindow::on_L_but_clicked()
{
    glw->L_enable=!glw->L_enable;
}

void MainWindow::on_pr_but_clicked()
{
    glw->prism_enable=!glw->prism_enable;
}

void MainWindow::on_change_L_rot_clicked()
{
    if(glw->L_angle==1)glw->L_angle=-1;
    else glw->L_angle=1;
}

void MainWindow::on_change_prism_rot_clicked()
{
    if(glw->prism_angle==1){glw->prism_angle=-1;/*glw->first_step=true;*/}
    else glw->prism_angle=1;

}

void MainWindow::on_pushButton_2_pressed()
{
    glw->light_move_x = 0.05;
}

void MainWindow::on_pushButton_2_released()
{
    glw->light_move_x = 0.0;
}

void MainWindow::on_pushButtonXmin_pressed()
{
    glw->light_move_x = -0.05;
}

void MainWindow::on_pushButtonXmin_released()
{
    glw->light_move_x = 0.0;
}

void MainWindow::on_pushButtonYpl_pressed()
{
    glw->light_move_y = 0.05;
}

void MainWindow::on_pushButtonYpl_released()
{
    glw->light_move_y = 0.0;
}

void MainWindow::on_pushButtonYmin_pressed()
{
    glw->light_move_y = -0.05;
}

void MainWindow::on_pushButtonYmin_released()
{
    glw->light_move_y = 0.0;
}

void MainWindow::on_pushButtonZpl_pressed()
{
    glw->light_move_z = 0.05;
}

void MainWindow::on_pushButtonZpl_released()
{
    glw->light_move_z = 0.0;
}

void MainWindow::on_pushButtonZmin_pressed()
{
    glw->light_move_z = -0.05;
}

void MainWindow::on_pushButtonZmin_released()
{
    glw->light_move_z = 0.0;
}
