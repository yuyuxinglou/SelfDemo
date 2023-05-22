#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
#include <QMainWindow>
#include<QFileDialog>
#include "bwcamera.h"
#include "colorcamera.h"
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
using namespace cv::dnn;
using namespace cv;
using namespace cv::ml;
using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void DisplayBW(QImage);

    void DisplayColor(QImage);

    void on_path_clicked();


    void on_Brightness_Slider_valueChanged(int value);

    void on_Save_triggered();

    void on_Start_measuring_triggered();

    void on_Exposure_Slider_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    void GetResolutionRange();
    int GetCurrentResolution();
    void SetCurrentResolution(int nIdxRes);
    void GetExposureTimeRange();
    double GetCurrentExposureTime();
    void SetCurrentExposureTime(double dbVal);
    void SaveImage(QString);
    void SaveSpectrum(QString);
    QString FileName=".";
    int saveimgcout=0;

    BWCamera* bw_camera;

    colorcamera* color_camera;


    QTimer *timerpre;
    bool pre_state=false;
    Mat pre_data;
    Mat img;
    QValueAxis xAxis;
    QValueAxis yAxis;
    Mat stdx;
    Mat stdy;
    Mat prob;
    String currpath;
    Net net;
    ifstream fin;
    ifstream fin1;
    QChart *c;
    void pre();

};
#endif // MAINWINDOW_H
