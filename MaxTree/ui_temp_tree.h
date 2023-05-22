/********************************************************************************
** Form generated from reading UI file 'temp_tree.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMP_TREE_H
#define UI_TEMP_TREE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_temp_tree
{
public:
    QWidget *centralwidget;
    QTreeWidget *temptree;
    QPushButton *enter;
    QPushButton *close;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *temp_tree)
    {
        if (temp_tree->objectName().isEmpty())
            temp_tree->setObjectName(QString::fromUtf8("temp_tree"));
        temp_tree->resize(800, 600);
        centralwidget = new QWidget(temp_tree);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        temptree = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        temptree->setHeaderItem(__qtreewidgetitem);
        temptree->setObjectName(QString::fromUtf8("temptree"));
        temptree->setGeometry(QRect(110, 30, 521, 421));
        enter = new QPushButton(centralwidget);
        enter->setObjectName(QString::fromUtf8("enter"));
        enter->setGeometry(QRect(140, 480, 75, 24));
        close = new QPushButton(centralwidget);
        close->setObjectName(QString::fromUtf8("close"));
        close->setGeometry(QRect(490, 480, 75, 24));
        temp_tree->setCentralWidget(centralwidget);
        menubar = new QMenuBar(temp_tree);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        temp_tree->setMenuBar(menubar);
        statusbar = new QStatusBar(temp_tree);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        temp_tree->setStatusBar(statusbar);

        retranslateUi(temp_tree);

        QMetaObject::connectSlotsByName(temp_tree);
    } // setupUi

    void retranslateUi(QMainWindow *temp_tree)
    {
        temp_tree->setWindowTitle(QCoreApplication::translate("temp_tree", "MainWindow", nullptr));
        enter->setText(QCoreApplication::translate("temp_tree", "\347\241\256\345\256\232", nullptr));
        close->setText(QCoreApplication::translate("temp_tree", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class temp_tree: public Ui_temp_tree {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMP_TREE_H
