#ifndef BWCAMERA_H
#define BWCAMERA_H
#include<QThread>
#include<QImage>
#include<CamApi.h>
#include<CamShare.h>
#include<QDebug>
#include <QPixmap>


class BWCamera: public QThread
{
    Q_OBJECT
public:
    explicit BWCamera(QObject *parent = nullptr);

protected:
    void run();

private:
    uchar *imgdata;

signals:
    void return_bwimg(QImage);
public:
};

#endif // BWCAMERA_H




