#include "bwcamera.h"

BWCamera::BWCamera(QObject *parent)
: QThread{parent}
{

}

void BWCamera::run()
{
    int s=InitDevice("");
    qDebug()<< s;
    int devCnts = DeviceCount();
    if (devCnts<1)
    {
        qDebug()<< "w";
    }
     struct _DESCRIPTOR desc;
    for (int i=0; i<devCnts; ++i)
    {
        DeviceDescriptor(&desc, i);
    }
    char *name=desc.name;
    if (NO_FAIL ==ResumeDevice(name))
    {
        qDebug()<< "s";
        int hei;
        while(1)
        {
            if (NO_FAIL ==GetRawDataPtr(&imgdata,&hei, name))
            {
//                int Depth = *(unsigned char *)(imgdata+RAW_OFT_DEPTH);
                int width = *(unsigned short *)(imgdata+RAW_OFT_WIDTH);
                int height = *(unsigned short *)(imgdata+RAW_OFT_HEIGHT);
//                qDebug()<<Depth<<width<<height;
                QImage image = QImage(imgdata,width, height, QImage::Format_Grayscale16);
                emit return_bwimg(image);
            }
            else
            {
                qDebug()<<"err";
            }
        }
    }
}

