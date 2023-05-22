/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *Start_measuring;
    QAction *Save;
    QAction *c01;
    QAction *c02;
    QAction *c03;
    QAction *c04;
    QAction *c05;
    QWidget *centralwidget;
    QChartView *chart_light;
    QLabel *camera;
    QLineEdit *Exposure_lineEdit;
    QLabel *Exposure_label;
    QSlider *Exposure_Slider;
    QLineEdit *Brightness_lineEdit;
    QLabel *Brightness_label;
    QSlider *Brightness_Slider;
    QTextEdit *path_text;
    QPushButton *path;
    QLabel *Saturation_label;
    QSlider *White_balance_Slider;
    QLineEdit *Contrast_lineEdit;
    QLabel *White_balance_label;
    QLineEdit *Gain_lineEdit;
    QLabel *Gain_label;
    QLabel *Hue_label;
    QLineEdit *Saturation_lineEdit;
    QLabel *Contrast_label;
    QLineEdit *Hue_lineEdit;
    QSlider *Gain_Slider;
    QSlider *Saturation_Slider;
    QSlider *Contrast_Slider;
    QLineEdit *White_balance_lineEdit;
    QSlider *Hue_Slider;
    QMenuBar *menubar;
    QMenu *menu_xuanz;
    QMenu *menu_2;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1571, 708);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../APP/Set.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        Start_measuring = new QAction(MainWindow);
        Start_measuring->setObjectName(QString::fromUtf8("Start_measuring"));
        Save = new QAction(MainWindow);
        Save->setObjectName(QString::fromUtf8("Save"));
        c01 = new QAction(MainWindow);
        c01->setObjectName(QString::fromUtf8("c01"));
        c01->setVisible(false);
        c02 = new QAction(MainWindow);
        c02->setObjectName(QString::fromUtf8("c02"));
        c02->setVisible(false);
        c03 = new QAction(MainWindow);
        c03->setObjectName(QString::fromUtf8("c03"));
        c03->setVisible(false);
        c04 = new QAction(MainWindow);
        c04->setObjectName(QString::fromUtf8("c04"));
        c04->setVisible(false);
        c05 = new QAction(MainWindow);
        c05->setObjectName(QString::fromUtf8("c05"));
        c05->setVisible(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        chart_light = new QChartView(centralwidget);
        chart_light->setObjectName(QString::fromUtf8("chart_light"));
        chart_light->setGeometry(QRect(950, 10, 611, 601));
        camera = new QLabel(centralwidget);
        camera->setObjectName(QString::fromUtf8("camera"));
        camera->setGeometry(QRect(330, 10, 601, 601));
        Exposure_lineEdit = new QLineEdit(centralwidget);
        Exposure_lineEdit->setObjectName(QString::fromUtf8("Exposure_lineEdit"));
        Exposure_lineEdit->setGeometry(QRect(260, 44, 40, 21));
        Exposure_lineEdit->setMinimumSize(QSize(20, 0));
        Exposure_lineEdit->setMaximumSize(QSize(40, 16777215));
        Exposure_lineEdit->setAutoFillBackground(false);
        Exposure_lineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Exposure_label = new QLabel(centralwidget);
        Exposure_label->setObjectName(QString::fromUtf8("Exposure_label"));
        Exposure_label->setGeometry(QRect(40, 34, 24, 31));
        Exposure_Slider = new QSlider(centralwidget);
        Exposure_Slider->setObjectName(QString::fromUtf8("Exposure_Slider"));
        Exposure_Slider->setGeometry(QRect(80, 40, 161, 22));
        Exposure_Slider->setMaximumSize(QSize(300, 16777215));
        Exposure_Slider->setOrientation(Qt::Horizontal);
        Brightness_lineEdit = new QLineEdit(centralwidget);
        Brightness_lineEdit->setObjectName(QString::fromUtf8("Brightness_lineEdit"));
        Brightness_lineEdit->setGeometry(QRect(260, 110, 40, 21));
        Brightness_lineEdit->setMinimumSize(QSize(20, 0));
        Brightness_lineEdit->setMaximumSize(QSize(40, 16777215));
        Brightness_lineEdit->setAutoFillBackground(false);
        Brightness_lineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Brightness_label = new QLabel(centralwidget);
        Brightness_label->setObjectName(QString::fromUtf8("Brightness_label"));
        Brightness_label->setGeometry(QRect(41, 102, 24, 31));
        Brightness_Slider = new QSlider(centralwidget);
        Brightness_Slider->setObjectName(QString::fromUtf8("Brightness_Slider"));
        Brightness_Slider->setGeometry(QRect(81, 106, 161, 22));
        Brightness_Slider->setOrientation(Qt::Horizontal);
        path_text = new QTextEdit(centralwidget);
        path_text->setObjectName(QString::fromUtf8("path_text"));
        path_text->setGeometry(QRect(121, 167, 141, 31));
        path = new QPushButton(centralwidget);
        path->setObjectName(QString::fromUtf8("path"));
        path->setGeometry(QRect(40, 170, 61, 24));
        Saturation_label = new QLabel(centralwidget);
        Saturation_label->setObjectName(QString::fromUtf8("Saturation_label"));
        Saturation_label->setEnabled(false);
        Saturation_label->setGeometry(QRect(40, 250, 41, 21));
        White_balance_Slider = new QSlider(centralwidget);
        White_balance_Slider->setObjectName(QString::fromUtf8("White_balance_Slider"));
        White_balance_Slider->setEnabled(false);
        White_balance_Slider->setGeometry(QRect(90, 370, 151, 22));
        White_balance_Slider->setOrientation(Qt::Horizontal);
        Contrast_lineEdit = new QLineEdit(centralwidget);
        Contrast_lineEdit->setObjectName(QString::fromUtf8("Contrast_lineEdit"));
        Contrast_lineEdit->setEnabled(false);
        Contrast_lineEdit->setGeometry(QRect(260, 430, 41, 21));
        White_balance_label = new QLabel(centralwidget);
        White_balance_label->setObjectName(QString::fromUtf8("White_balance_label"));
        White_balance_label->setEnabled(false);
        White_balance_label->setGeometry(QRect(40, 370, 41, 21));
        Gain_lineEdit = new QLineEdit(centralwidget);
        Gain_lineEdit->setObjectName(QString::fromUtf8("Gain_lineEdit"));
        Gain_lineEdit->setEnabled(false);
        Gain_lineEdit->setGeometry(QRect(260, 490, 41, 21));
        Gain_label = new QLabel(centralwidget);
        Gain_label->setObjectName(QString::fromUtf8("Gain_label"));
        Gain_label->setEnabled(false);
        Gain_label->setGeometry(QRect(40, 490, 31, 21));
        Hue_label = new QLabel(centralwidget);
        Hue_label->setObjectName(QString::fromUtf8("Hue_label"));
        Hue_label->setEnabled(false);
        Hue_label->setGeometry(QRect(38, 310, 31, 21));
        Saturation_lineEdit = new QLineEdit(centralwidget);
        Saturation_lineEdit->setObjectName(QString::fromUtf8("Saturation_lineEdit"));
        Saturation_lineEdit->setEnabled(false);
        Saturation_lineEdit->setGeometry(QRect(260, 250, 41, 21));
        Contrast_label = new QLabel(centralwidget);
        Contrast_label->setObjectName(QString::fromUtf8("Contrast_label"));
        Contrast_label->setEnabled(false);
        Contrast_label->setGeometry(QRect(40, 430, 41, 21));
        Hue_lineEdit = new QLineEdit(centralwidget);
        Hue_lineEdit->setObjectName(QString::fromUtf8("Hue_lineEdit"));
        Hue_lineEdit->setEnabled(false);
        Hue_lineEdit->setGeometry(QRect(258, 310, 41, 21));
        Gain_Slider = new QSlider(centralwidget);
        Gain_Slider->setObjectName(QString::fromUtf8("Gain_Slider"));
        Gain_Slider->setEnabled(false);
        Gain_Slider->setGeometry(QRect(90, 490, 151, 22));
        Gain_Slider->setOrientation(Qt::Horizontal);
        Saturation_Slider = new QSlider(centralwidget);
        Saturation_Slider->setObjectName(QString::fromUtf8("Saturation_Slider"));
        Saturation_Slider->setEnabled(false);
        Saturation_Slider->setGeometry(QRect(90, 250, 151, 22));
        Saturation_Slider->setOrientation(Qt::Horizontal);
        Contrast_Slider = new QSlider(centralwidget);
        Contrast_Slider->setObjectName(QString::fromUtf8("Contrast_Slider"));
        Contrast_Slider->setEnabled(false);
        Contrast_Slider->setGeometry(QRect(90, 430, 151, 22));
        Contrast_Slider->setOrientation(Qt::Horizontal);
        White_balance_lineEdit = new QLineEdit(centralwidget);
        White_balance_lineEdit->setObjectName(QString::fromUtf8("White_balance_lineEdit"));
        White_balance_lineEdit->setEnabled(false);
        White_balance_lineEdit->setGeometry(QRect(260, 370, 41, 21));
        Hue_Slider = new QSlider(centralwidget);
        Hue_Slider->setObjectName(QString::fromUtf8("Hue_Slider"));
        Hue_Slider->setEnabled(false);
        Hue_Slider->setGeometry(QRect(90, 310, 151, 22));
        Hue_Slider->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1571, 22));
        menu_xuanz = new QMenu(menubar);
        menu_xuanz->setObjectName(QString::fromUtf8("menu_xuanz"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu_xuanz->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu_xuanz->addAction(c01);
        menu_xuanz->addAction(c02);
        menu_xuanz->addAction(c03);
        menu_xuanz->addAction(c04);
        menu_xuanz->addAction(c05);
        toolBar->addSeparator();
        toolBar->addSeparator();
        toolBar->addAction(Start_measuring);
        toolBar->addAction(Save);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Light", nullptr));
        Start_measuring->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\351\242\204\346\265\213", nullptr));
        Save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        c01->setText(QCoreApplication::translate("MainWindow", "01", nullptr));
        c02->setText(QCoreApplication::translate("MainWindow", "02", nullptr));
        c03->setText(QCoreApplication::translate("MainWindow", "03", nullptr));
        c04->setText(QCoreApplication::translate("MainWindow", "04", nullptr));
        c05->setText(QCoreApplication::translate("MainWindow", "05", nullptr));
        camera->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\347\252\227\345\217\243", nullptr));
        Exposure_label->setText(QCoreApplication::translate("MainWindow", "\346\233\235\345\205\211", nullptr));
        Brightness_label->setText(QCoreApplication::translate("MainWindow", "\344\272\256\345\272\246", nullptr));
        path_text->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">......</p></body></html>", nullptr));
        path->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        Saturation_label->setText(QCoreApplication::translate("MainWindow", "\351\245\261\345\222\214\345\272\246", nullptr));
        White_balance_label->setText(QCoreApplication::translate("MainWindow", "\347\231\275\345\271\263\350\241\241", nullptr));
        Gain_label->setText(QCoreApplication::translate("MainWindow", "\345\242\236\347\233\212", nullptr));
        Hue_label->setText(QCoreApplication::translate("MainWindow", "\350\211\262\350\260\203", nullptr));
        Contrast_label->setText(QCoreApplication::translate("MainWindow", "\345\257\271\346\257\224\345\272\246", nullptr));
        White_balance_lineEdit->setText(QString());
        menu_xuanz->setTitle(QCoreApplication::translate("MainWindow", "\347\233\270\346\234\272\351\200\211\346\213\251", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
