#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cuda_dll.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    const int arraySize = 5;
    int d[arraySize] = { 11, 22, 33, 44, 55 };
    int b[arraySize] = { 10, 20, 30, 40, 50 };
    int e[arraySize] = { 0 };
    int number = vectorAdd(e, d, b, arraySize);
    QMessageBox::about(this, "CUDA",
        QObject::tr("{1,2,3,4,5} + {10,20,30,40,50}= {%1,%2,%3,%4,%5}")
        .arg(e[0]).arg(e[1]).arg(e[2]).arg(e[3]).arg(e[4]));







    c=new QChart();             // 图表对象
    c->setTitle("光谱") ;
    c->legend()->setVisible(false);
    ui->chart_light->setChart(c);
    xAxis.setRange(293,845);
    yAxis.setRange(0, 100000);
    xAxis.setTitleText("Wavelength(nm)");
    xAxis.setTickCount(20);
    yAxis.setTickCount(20);
    yAxis.setTitleText("Intensity(a.u)");
    currpath=QDir::currentPath().toStdString();
    FileName=QString::fromStdString(currpath);
    ui->Exposure_Slider->setRange(0,150);
//    ui->Brightness_Slider->setSingleStep(attrProp.dbValStep);
    timerpre=new QTimer();
    connect(timerpre, &QTimer::timeout, this, QOverload<>::of(&MainWindow::pre));

//    bw_camera=new BWCamera();
//    connect(bw_camera, SIGNAL(return_bwimg(QImage)), this, SLOT(DisplayBW(QImage)));
//    bw_camera->start();

    ui->camera->setScaledContents(true);
    color_camera=new colorcamera();
    connect(color_camera, SIGNAL(return_colorimg(QImage)), this, SLOT(DisplayColor(QImage)));
    color_camera->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayBW(QImage temp)
{
    if(pre_state)
    {
        img=cv::Mat(temp.height(),temp.width(),CV_8UC1,(uchar*)temp.bits(),temp.bytesPerLine());
//        qDebug()<<img.rows;
    }
    ui->camera->setPixmap(QPixmap::fromImage(temp));
}

void MainWindow::DisplayColor(QImage temp)
{
    if(pre_state)
    {
        img=color_camera->temp_img;
        qDebug()<<img.channels();
    }
    ui->camera->setPixmap(QPixmap::fromImage(temp));
}

void MainWindow::on_path_clicked()
{
    FileName =QFileDialog::getExistingDirectory(this, "请选择模板保存路径...", "./");
    ui->path_text->setText(FileName);
}

void MainWindow::on_Start_measuring_triggered()
{
    if(!pre_state)
    {
//        qDebug()<<img.empty();
//        if(img.empty())
//        {
            fin.open(currpath+"/stdy20220701.txt");
            fin1.open(currpath+"/stdx20220701.txt");
            stdx=Mat::zeros(1,100,CV_32FC1);
            stdy=Mat::zeros(1,300,CV_32FC1);
            prob=Mat::zeros(1,300,CV_32FC1);
            for (int i=0; i < 300; ++i)
            {
                float a;
                fin >> a;
                stdy.at<float>(0,i) = a;//
            }
            for (int i=0; i < 100; ++i)
            {
                float a;
                fin1 >> a;
                stdx.at<float>(0,i) = a;//
            }
            try
            {
                net = readNetFromONNX(currpath+"/sequential_20220701.onnx");
                timerpre->start(300);
                pre_state=true;
            }
            catch (...)
            {
                QMessageBox::warning(NULL, "warning", "模型错误1");
                timerpre->stop();
                pre_state=false;
            }
//        }
    }
    else
    {
        timerpre->stop();
        pre_state=false;
    }
}

void MainWindow::pre()
{
    int i;
    Mat x;
    Mat x_crop;
    try
    {
//        Mat x=cv::imread("E:\\20220708\\tu\\gray11.bmp");
        cv::cvtColor(img, x,cv::COLOR_BGR2GRAY);
        Point center=Point(x.cols/2,x.rows/2);
        Mat rot_mat(2,3,CV_32FC1);
        rot_mat=cv::getRotationMatrix2D(center,0.9,1);
        warpAffine(x, x_crop, rot_mat, x_crop.size());
//        x_crop=x_crop(Rect(1400,1120,900,900));
        x_crop=x_crop(Rect(1,1,900,900));
    }
    catch (...)
    {
        QMessageBox::warning(NULL, "warning", "相机不对");
        pre_state=false;
    }
    try
    {
        Mat inputdata(1,100,CV_32FC1);
        Mat inputdata1(1,100,CV_32FC1);
        i=0;
        for(int m=0;m<10;++m)
        {
            for(int n=0;n<10;++n)
            {
                Scalar mean;  //均值
                Scalar stddev;  //标准差
                x=x_crop(Rect(45+m*86.5,45+n*86.5,25,25));
                cv::meanStdDev(x, mean, stddev );
                inputdata.at<float>(0,i)=mean.val[0];
                ++i;
            }
        }
        divide(inputdata,stdx,inputdata1,1,5);
        net.setInput(inputdata1);
        prob = net.forward();
        pre_data=prob.mul(stdy);
    }
    catch (...)
    {
        QMessageBox::warning(NULL, "warning", "参数错误");
        pre_state=false;
    }
    try
    {
        c->removeAllSeries();
        QLineSeries *MyLineSeries=new QLineSeries();
        QVector<QPointF> MyPointf;
    //    QLineSeries *MyLineSeries=new QLineSeries();
        i=0;
        for(float x=293;x<845;x+=1.84f)
        {
             MyPointf<<QPointF(x,pre_data.at<float>(0,i));
    //        pre_data2.at<float>(0,i)=pre_data.at<float>(0,i);
            ++i;
        }
        MyLineSeries->replace(MyPointf);
        c->addSeries(MyLineSeries);
        c->setAxisX(&xAxis,MyLineSeries);
        c->setAxisY(&yAxis,MyLineSeries);
    }
    catch (...)
    {
        QMessageBox::warning(NULL, "warning", "表个错误");
        pre_state=false;
    }
}

void MainWindow::GetResolutionRange()
{
    TUCAM_CAPA_ATTR attrCapa;
    TUCAM_VALUE_TEXT valText;
    char szRes[64] = {0};
    valText.nTextSize = 64;
    valText.pText = &szRes[0];
    attrCapa.idCapa = TUIDC_RESOLUTION;
    if (TUCAMRET_SUCCESS == TUCAM_Capa_GetAttr(color_camera->opCam.hIdxTUCam, &attrCapa))
    {
        // 获取分辨率个数
        int nCnt = attrCapa.nValMax - attrCapa.nValMin + 1;
        valText.nID = TUIDC_RESOLUTION;
        for (int i=0; i<nCnt; ++i)
        {
            valText.dbValue = i;
            TUCAM_Capa_GetValueText(color_camera->opCam.hIdxTUCam, &valText);
//            szRes=valText.pText;
            // 将分辨率文本添加到下拉菜单
        }
    }
 }



int MainWindow::GetCurrentResolution()
{
    int nVal = 0;
    if (TUCAMRET_SUCCESS == TUCAM_Capa_GetValue(color_camera->opCam.hIdxTUCam,TUIDC_RESOLUTION,&nVal))
    {
        // nVal 返回当前分辨率索引
        return nVal;
    }
    else
    {
        return 0;
    }
}

// 设置当前分辨率
void MainWindow::SetCurrentResolution(int nIdxRes)
{
    TUCAM_Capa_SetValue(color_camera->opCam.hIdxTUCam, TUIDC_RESOLUTION, nIdxRes);
}


void MainWindow::GetExposureTimeRange()
{
    TUCAM_PROP_ATTR attrProp;
    attrProp.nIdxChn = 0; // 当前通道
    attrProp.idProp = TUIDP_EXPOSURETM;

    if (TUCAMRET_SUCCESS == TUCAM_Prop_GetAttr(color_camera->opCam.hIdxTUCam, &attrProp))
    {
        // 曝光时间范围
//        attrProp.dbValMin; // 最小曝光时间
//        attrProp.dbValMax; // 最大曝光时间
//        attrProp.dbValDft; // 默认曝光时间
//        attrProp.dbValStep; // 曝光时间步长
//        ui->Brightness_Slider->setValue(attrProp.dbValDft);
        ui->Brightness_Slider->setRange(attrProp.dbValMin,attrProp.dbValMax);
        ui->Brightness_Slider->setSingleStep(attrProp.dbValStep);
//        ui->Brightness_lineEdit->setText(QString::number(ui->Brightness_Slider->value()));
    }
}


// 获取当前曝光时间
double MainWindow::GetCurrentExposureTime()
{
    double dbVal = 1.0f;
    if (TUCAMRET_SUCCESS == TUCAM_Prop_GetValue(color_camera->opCam.hIdxTUCam,  TUIDP_EXPOSURETM,  &dbVal))
    {
        return dbVal;
        // dbVal 返回当前曝光时间，单位 ms
    }
    else
    {
        return 0;
    }
}
// 设置当前曝光时间
void MainWindow::SetCurrentExposureTime(double dbVal)
{

//    TUCAM_Prop_SetValue(color_camera->opCam.hIdxTUCam, TUIDP_EXPOSURETM, dbVal);
    if(TUCAMRET_SUCCESS ==TUCAM_Prop_SetValue(color_camera->opCam.hIdxTUCam, TUIDP_EXPOSURETM, dbVal))
    {
//        qDebug()<<"success";
    }
}

void MainWindow::SaveImage(QString temp)
{
    if(TUCAMRET_SUCCESS==TUCAM_Buf_WaitForFrame(color_camera->opCam.hIdxTUCam, &color_camera->m_frame))
    {
//        qDebug()<<"success";
        TUCAM_FILE_SAVE fileSave;
        fileSave.nSaveFmt = TUFMT_TIF; // 保存 Tiff 格式
        fileSave.pFrame = &color_camera->m_frame; // 需要保存的帧指针

        std::string str = temp.toStdString();
        const char* ch = str.c_str();
        fileSave.pstrSavePath=(char*)ch; // 路径包含文件名（不包含扩展名）
        if (TUCAMRET_SUCCESS == TUCAM_File_SaveImage(color_camera->opCam.hIdxTUCam, fileSave))
        {
            // 保存图像文件成功
//            qDebug()<<"success";
        }
    }
}

void MainWindow::SaveSpectrum(QString temp)
{
    if(!pre_state)
    {
        cout<<"打开预测"<<endl;
    }
    else
    {
        fstream PLeft48(temp.toStdString()+".txt", ios::out);
        float x=293;
        if (!PLeft48.fail())
        {
            for (int j = 0; j < 300; ++j)
            {
                PLeft48 << x <<"\t"<<pre_data.at<float>(0, j) << "\n";
                x+=1.84f;
            }
            PLeft48 << std::endl;
        }
        else
        {
            cout << "can not open" << endl;
        }
        PLeft48.close();
        cout << "finish" << endl;
    }
}

void MainWindow::on_Brightness_Slider_valueChanged(int value)
{
//    GetExposureTimeRange();
    SetCurrentExposureTime(value);
    ui->Brightness_lineEdit->setText(QString::number(value));
}


void MainWindow::on_Save_triggered()
{
    QString temp_path=FileName+"/"+QString::number(saveimgcout);
    SaveImage(temp_path);
    SaveSpectrum(temp_path);
    saveimgcout+=1;
}


void MainWindow::on_Exposure_Slider_valueChanged(int value)
{
    SetCurrentExposureTime(value);
    ui->Exposure_lineEdit->setText(QString::number(value));
}

