#ifndef ROTATIONS_ARRAY_H
#define ROTATIONS_ARRAY_H
#include <QVector>

class rotation_point
{
public:
    qreal x,y,z,angle;
    rotation_point(qreal x_in,qreal y_in,qreal z_in,qreal angle_in)
    {
        x=x_in;
        y=y_in;
        z=z_in;
        angle=angle_in;
    }
    rotation_point()
    {

    }
};

class rotations_array
{
public:

    QVector<rotation_point> points;

};

#endif // ROTATIONS_ARRAY_H
