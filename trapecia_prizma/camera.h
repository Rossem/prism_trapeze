#ifndef CAMERA_H
#define CAMERA_H
#include<C:\Qt_projects\Eigen\Dense>
#include<QMatrix4x4>

using namespace Eigen;

class Camera
{

    enum CameraType { LANDOBJECT, AIRCRAFT };
public:
         Camera();
         Camera(CameraType cameraType);
        ~Camera();

        void strafe(double units); // left/right
        void fly(double units);    // up/down
        void walk(double units);   // forward/backward

        void pitch(double angle); // rotate on right vector
        void yaw(double angle);   // rotate on up vector
        void roll(double angle);  // rotate on look vector

        void getViewMatrix(QMatrix4x4 *V);
        void setCameraType(CameraType cameraType);
        void getPosition(Vector3d* pos);
        void setPosition(Vector3d* pos);

        void getRight(Vector3d* right);
        void getUp(Vector3d* up);
        void getLook(Vector3d* look);
    private:
        CameraType  _cameraType;
        Vector3d _right;
        Vector3d _up;
        Vector3d _look;
        Vector3d _pos;
};

#endif // CAMERA_H
