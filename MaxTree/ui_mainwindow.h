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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QSpacerItem *File_label;
    QPushButton *on_add_data;
    QPushButton *open_dir;
    QPushButton *on_delete_data;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labels_label;
    QSpacerItem *horizontalSpacer_3;
    QTreeWidget *Tag_tree;
    QTreeWidget *File_tree;
    QGroupBox *groupBox_2;
    QLineEdit *search_lineEdit;
    QPushButton *on_set;
    QPushButton *on_search;
    QPushButton *on_users;
    QLabel *logo_label;
    QComboBox *comboBox_3;
    QGroupBox *groupBox_3;
    QListWidget *Img_List;
    QScrollBar *verticalScrollBar;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *on_export;
    QLabel *label_3;
    QLabel *label_10;
    QLabel *label_7;
    QLabel *label_14;
    QLabel *label_15;
    QComboBox *comboBox_2;
    QLabel *label_13;
    QComboBox *comboBox;
    QLabel *label_16;
    QPushButton *pushButton;
    QWidget *widget;
    QWidget *tab_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdut;
    QMenu *menuWindow;
    QMenu *menuHlep;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1800, 910);
        MainWindow->setMinimumSize(QSize(1200, 400));
        MainWindow->setMaximumSize(QSize(1800, 910));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 100, 271, 771));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        File_label = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(File_label);

        on_add_data = new QPushButton(groupBox);
        on_add_data->setObjectName(QString::fromUtf8("on_add_data"));
        on_add_data->setMinimumSize(QSize(25, 0));
        on_add_data->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(on_add_data);

        open_dir = new QPushButton(groupBox);
        open_dir->setObjectName(QString::fromUtf8("open_dir"));
        open_dir->setMinimumSize(QSize(15, 0));

        horizontalLayout->addWidget(open_dir);

        on_delete_data = new QPushButton(groupBox);
        on_delete_data->setObjectName(QString::fromUtf8("on_delete_data"));

        horizontalLayout->addWidget(on_delete_data);


        gridLayout_5->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labels_label = new QLabel(groupBox);
        labels_label->setObjectName(QString::fromUtf8("labels_label"));

        horizontalLayout_2->addWidget(labels_label);

        horizontalSpacer_3 = new QSpacerItem(150, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        gridLayout_5->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        Tag_tree = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        Tag_tree->setHeaderItem(__qtreewidgetitem);
        Tag_tree->setObjectName(QString::fromUtf8("Tag_tree"));

        gridLayout_5->addWidget(Tag_tree, 3, 0, 1, 1);

        File_tree = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        File_tree->setHeaderItem(__qtreewidgetitem1);
        File_tree->setObjectName(QString::fromUtf8("File_tree"));

        gridLayout_5->addWidget(File_tree, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setEnabled(true);
        groupBox_2->setGeometry(QRect(0, 0, 1451, 101));
        search_lineEdit = new QLineEdit(groupBox_2);
        search_lineEdit->setObjectName(QString::fromUtf8("search_lineEdit"));
        search_lineEdit->setGeometry(QRect(290, 30, 771, 40));
        search_lineEdit->setMinimumSize(QSize(700, 40));
        on_set = new QPushButton(groupBox_2);
        on_set->setObjectName(QString::fromUtf8("on_set"));
        on_set->setEnabled(true);
        on_set->setGeometry(QRect(1160, 40, 75, 24));
        on_search = new QPushButton(groupBox_2);
        on_search->setObjectName(QString::fromUtf8("on_search"));
        on_search->setGeometry(QRect(1070, 30, 75, 40));
        on_search->setMaximumSize(QSize(80, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8("C:/Users/wuhao/Desktop/\345\260\217\345\233\276\346\240\207.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        on_search->setIcon(icon);
        on_search->setIconSize(QSize(32, 32));
        on_users = new QPushButton(groupBox_2);
        on_users->setObjectName(QString::fromUtf8("on_users"));
        on_users->setGeometry(QRect(1250, 40, 75, 24));
        logo_label = new QLabel(groupBox_2);
        logo_label->setObjectName(QString::fromUtf8("logo_label"));
        logo_label->setGeometry(QRect(70, 10, 200, 80));
        logo_label->setMinimumSize(QSize(200, 80));
        logo_label->setMaximumSize(QSize(200, 80));
        comboBox_3 = new QComboBox(groupBox_2);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(1350, 40, 59, 22));
        comboBox_3->setMinimumSize(QSize(40, 20));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(270, 100, 1181, 771));
        Img_List = new QListWidget(groupBox_3);
        Img_List->setObjectName(QString::fromUtf8("Img_List"));
        Img_List->setEnabled(true);
        Img_List->setGeometry(QRect(10, 10, 1151, 751));
        Img_List->setTextElideMode(Qt::ElideRight);
        Img_List->setSelectionRectVisible(false);
        verticalScrollBar = new QScrollBar(groupBox_3);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(1156, 10, 20, 751));
        verticalScrollBar->setOrientation(Qt::Vertical);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(1450, 0, 351, 861));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        on_export = new QPushButton(tab);
        on_export->setObjectName(QString::fromUtf8("on_export"));
        on_export->setGeometry(QRect(210, 490, 75, 24));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 70, 321, 251));
        label_3->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";\n"
"font: 12pt \"Microsoft YaHei UI\";\n"
"text-decoration: underline;"));
        label_10 = new QLabel(tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 400, 291, 21));
        label_10->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 590, 61, 16));
        label_7->setStyleSheet(QString::fromUtf8("font: 12pt \"Microsoft YaHei UI\";\n"
"text-decoration: underline;"));
        label_14 = new QLabel(tab);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(30, 630, 71, 31));
        label_15 = new QLabel(tab);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(30, 680, 61, 21));
        label_15->setStyleSheet(QString::fromUtf8(""));
        comboBox_2 = new QComboBox(tab);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(110, 460, 59, 22));
        comboBox_2->setMinimumSize(QSize(40, 20));
        label_13 = new QLabel(tab);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 460, 71, 21));
        label_13->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));
        comboBox = new QComboBox(tab);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(110, 520, 59, 22));
        comboBox->setMinimumSize(QSize(40, 20));
        label_16 = new QLabel(tab);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(20, 520, 71, 21));
        label_16->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 430, 75, 24));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    /*1*/\n"
"	border:none;	/*\345\216\273\346\216\211\350\276\271\346\241\206*/\n"
"	border-radius:10px;\n"
"    /*1\357\274\214\346\267\273\345\212\240\345\233\276\347\211\207*/\n"
"  	background-image: url(:/images/quit.png);\n"
"	background-repeat:none;\n"
"	background-position:center;\n"
"    /*3\357\274\214\346\212\212\345\233\276\347\211\207\344\275\234\344\270\272\350\276\271\346\241\206\357\274\214\344\274\232\350\207\252\345\212\250\351\223\272\346\273\241\350\203\214\346\231\257*/\n"
"    border-image: url(:/images/quit.png);\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"	background-color:rgba(102,205,227,255);\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(48,188,218);\n"
"}"));
        tabWidget->addTab(tab, QString());
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        tabWidget->addTab(widget, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralwidget);
        groupBox_3->raise();
        groupBox_2->raise();
        groupBox->raise();
        tabWidget->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1800, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdut = new QMenu(menubar);
        menuEdut->setObjectName(QString::fromUtf8("menuEdut"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
        menuHlep = new QMenu(menubar);
        menuHlep->setObjectName(QString::fromUtf8("menuHlep"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdut->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHlep->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MaxTree", nullptr));
        groupBox->setTitle(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "FOLDERS", nullptr));
        on_add_data->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        open_dir->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        on_delete_data->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        labels_label->setText(QCoreApplication::translate("MainWindow", "TAGS", nullptr));
        groupBox_2->setTitle(QString());
        on_set->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        on_search->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        on_users->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267", nullptr));
        logo_label->setText(QCoreApplication::translate("MainWindow", "Logo_label", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "FBX", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "blend", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "JSON", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("MainWindow", "max", nullptr));

        groupBox_3->setTitle(QString());
        on_export->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272", nullptr));
        label_3->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "Format:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Others", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\347\244\276\344\272\244\344\277\241\346\201\257", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\345\256\230\347\275\221\351\223\276\346\216\245", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "FBX", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "blend", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "JSON", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "max", nullptr));

        label_13->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\240\274\345\274\217:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "blend", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "max", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "maya", nullptr));

        label_16->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\350\275\257\344\273\266:", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(widget), QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\350\256\276\347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\350\256\276\347\275\256", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdut->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuWindow->setTitle(QCoreApplication::translate("MainWindow", "Window", nullptr));
        menuHlep->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
