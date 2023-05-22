#ifndef COLORCAMERA_H
#define COLORCAMERA_H
#include<QThread>
#include<QDebug>
#include<TUCamApi.h>
#include<TUDefine.h>
#include<QImage>
#include<opencv2/opencv.hpp>
class colorcamera : public QThread
{

    Q_OBJECT
public:
    explicit colorcamera(QObject *parent = nullptr);

protected:
    void run();

private:

signals:
    void return_colorimg(QImage);

public:
    TUCAM_OPEN opCam;
    TUCAM_FRAME m_frame;
    cv::Mat temp_img;
};

#endif // COLORCAMERA_H
