#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    double move_sens;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    GLWidget* glw;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    QDoubleValidator* start_param_validator;
signals:
    void new_planet(double,double,double);
private slots:
    void set_move_sens(int new_move_sens);
    void on_L_but_clicked();
    void on_pr_but_clicked();
    void on_change_L_rot_clicked();
    void on_change_prism_rot_clicked();
    void on_pushButton_2_pressed();
    void on_pushButton_2_released();
    void on_pushButtonXmin_pressed();
    void on_pushButtonYpl_released();
    void on_pushButtonYmin_pressed();
    void on_pushButtonYmin_released();
    void on_pushButtonXmin_released();
    void on_pushButtonYpl_pressed();
    void on_pushButtonZpl_pressed();
    void on_pushButtonZpl_released();
    void on_pushButtonZmin_pressed();
    void on_pushButtonZmin_released();
};

#endif // MAINWINDOW_H
