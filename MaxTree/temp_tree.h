#ifndef TEMP_TREE_H
#define TEMP_TREE_H

#include <QMainWindow>
#include<QTreeWidgetItem>
#include <QSqlError>
#include <QSqlQuery>
#include <QSql>
#include<global.h>
#include<QDebug>
namespace Ui {
class temp_tree;
}

class temp_tree : public QMainWindow
{
    Q_OBJECT

public:
    explicit temp_tree(QWidget *parent = nullptr);
    ~temp_tree();

private slots:
    void on_temptree_itemClicked(QTreeWidgetItem *item, int column);

    void on_enter_clicked();

    void on_close_clicked();

private:
    Ui::temp_tree *ui;
//    QSqlDatabase db;
    QString temp_str;
    int id=0;
    int parent_index=-1;
    QString temp_index;
    bool openDB();
    void addData(QString parent, QTreeWidget *item);
    void addData(QString parent, QTreeWidgetItem *item);
    void findparent(QTreeWidgetItem *temp);
};

#endif // TEMP_TREE_H
