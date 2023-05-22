#include "colorcamera.h"
#include "ExplosureFusion.h"
colorcamera::colorcamera(QObject *parent)
    : QThread{parent}
{

}

void colorcamera::run()
{
    CExplosureFusion cExplosureFusion=CExplosureFusion();


    TUCAM_INIT itApi; // 初始化 SDK 环境参数
    itApi.pstrConfigPath = NULL;
    itApi.uiCamCount = 0;
    if (TUCAMRET_SUCCESS != TUCAM_Api_Init(&itApi))
    {
        qDebug()<<"ere";
    }
    if (0 == itApi.uiCamCount)
    {
        qDebug()<<"ere";
    }
    opCam.hIdxTUCam = 0;
    opCam.uiIdxOpen = 0;
    if (TUCAMRET_SUCCESS != TUCAM_Dev_Open(&opCam))
    {
        qDebug()<<"ere";
    }
    m_frame.pBuffer = NULL;
    m_frame.ucFormatGet = TUFRM_FMT_RGB888;
    m_frame.uiRsdSize = 1;
    if(TUCAMRET_SUCCESS != TUCAM_Buf_Alloc(opCam.hIdxTUCam,&m_frame))
    {
        qDebug()<<"读取数据失败";
    }
    if(TUCAMRET_SUCCESS != TUCAM_Cap_Start(opCam.hIdxTUCam, TUCCM_SEQUENCE))
    {
        TUCAM_Buf_Release(opCam.hIdxTUCam);
    }

    if(TUCAMRET_SUCCESS!= TUCAM_Capa_SetValue(opCam.hIdxTUCam,TUIDC_ATEXPOSURE,0))
    {
        qDebug()<<"关闭自动曝光失败";
    }
    while(1)
    {
        if(TUCAMRET_SUCCESS==TUCAM_Buf_WaitForFrame(opCam.hIdxTUCam,&m_frame))
        {
//            unsigned char *PA=(unsigned char*)(&m_frame.pBuffer+m_frame.usHeader);
//            qDebug()<<m_frame.usOffset<<m_frame.uiHstSize;
//            m_frame.pBuffer;
//            qDebug()<<"dadsa"<<m_frame.uiImgSize<<m_frame.usHeight<<m_frame.ucChannels<<m_frame.uiImgSize/m_frame.usHeight/3;
//            qDebug()<<m_frame.uiImgSize;
            QImage image = QImage((const unsigned char*)(&m_frame.pBuffer[0]+1024),5472,3648,QImage::Format_RGB888);
            temp_img=cv::Mat(5472,3648,CV_8UC3,(void*)(&m_frame.pBuffer[0]+1024));
            cExplosureFusion.setInputImages(temp_img);

            emit return_colorimg(image.rgbSwapped());
        }
    }
    TUCAM_Dev_Close(opCam.hIdxTUCam); // 关闭相机
    TUCAM_Api_Uninit(); // 反初始化 SDK API 环境

}







