#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QMessageBox>
#include <QHeaderView>
#include <QSql>
#include<QSqlRecord>
#include <QSqlTableModel>
#include<QSqlRelationalTableModel>
#include <QStandardItemModel>
#include<QTreeWidgetItem>
#include<QInputDialog>
#include<QUuid>
#include<QListWidgetItem>
#include<QFileDialog>
#include<QFileSystemModel>
#include<temp_tree.h>
#include<global.h>
#include<QDesktopServices>
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

    void slotMenuPopup(const QPoint &pos);

    void addRootNode();

    void RefreshAllNode();

    void addCategory();

    void addTemplate();

    void deleteNode();

    void reNameNode();

    void deleteNode(QTreeWidgetItem *temp);

    void on_search_lineEdit_textChanged(const QString &arg1);

    void on_on_search_clicked();

    void on_on_export_clicked();

    void on_Img_List_itemSelectionChanged();

    void on_Tag_tree_itemClicked(QTreeWidgetItem *item, int column);

    void on_on_add_data_clicked();

    void on_File_tree_itemClicked(QTreeWidgetItem *item, int column);

    void on_File_tree_itemExpanded(QTreeWidgetItem *item);

    void imglist_slotMenuPopup(const QPoint &pos);
    void AddTag();

    void on_Img_List_itemPressed(QListWidgetItem *item);

    void on_on_delete_data_clicked();

    void on_open_dir_clicked();


    void on_pushButton_clicked();

    void on_comboBox_3_activated(int index);

    void on_verticalScrollBar_valueChanged(int value);


private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    void initTree();
    bool openDB();
    void addData(QString parent, QTreeWidgetItem *item);
    void addData(QString parent, QTreeWidget *item);
    void SetData(QTreeWidgetItem *rootItem,QString path);
    void findparent(QTreeWidgetItem *temp);
    bool DelDir(const QString &path);
    void wheelEvent(QWheelEvent *event);
    QTreeWidgetItem* curtagItem;  //当前被右击的item
    //空白地方点击
    QAction *addRootNodeAction;
    QAction *RefreshAllNodeAction;
    QTreeWidgetItem* curFileItem;
    //节点上点击
    QAction *addCategoryAction;
    QAction *addTemplateAction;
    QAction *deleteNodeAction;
    QAction *reNameNodeAction;
    bool listimg_display=true;
    int id;
    QString tagtree;
    QString Listimg_path;
    int parent_index=-1;
    QListWidgetItem* curlistItem;
    QAction *addtag;

    QVector<QString> m_VectorImageName;
    QVector<QString> m_VectorOfImageFullName;
    QVector<QString> m_VectorImageSuffix;
    QFileInfoList folder_list;
    int m_ImageSum;
    QString tempimg_path="E:/MaxtreeAssetsManager_TestFiles/MT_PM_Vol1/MT_PM_V1_01_01.jpg";
};
#endif // MAINWINDOW_H
