#include "temp_tree.h"
#include "ui_temp_tree.h"
#include <qfileinfo.h>

temp_tree::temp_tree(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::temp_tree)
{
    ui->setupUi(this);
    openDB();
}

temp_tree::~temp_tree()
{
    delete ui;
}

void temp_tree::on_temptree_itemClicked(QTreeWidgetItem *item, int column)
{
    findparent(item);
    temp_str=item->text(0);
    temp_index=QString::number(parent_index+1);
    parent_index=-1;
}


void temp_tree::on_enter_clicked()
{
    QSqlQuery query;
    if(query.exec("select Name from ResourceDatas where Name='"+temp_name+"' and ParentFile='"+temp_str+"' and Path='"+temp_path+"' and Level='"+temp_index+"' "))
    {
        QString FileName;
       while(query.next())
       {
           FileName=query.value(0).toString();
           qDebug()<<FileName;
       }
       if(FileName.isNull())
       {
          query.prepare("insert into ResourceDatas values (?,?,?,?,?)");
          query.bindValue(0,id);
          query.bindValue(1,temp_name);
          query.bindValue(2,temp_path);
          query.bindValue(3,temp_str);
          query.bindValue(4,temp_index);
          if(!query.exec())
          {
              QSqlError lastError = query.lastError();
              qDebug()<<"插入错误";
          }
          id+=1;
       }
       this->close();
    }
}





void temp_tree::on_close_clicked()
{
    this->close();
}


void temp_tree::findparent(QTreeWidgetItem *temp)
{
    if(temp==NULL)
    {
        qDebug()<<parent_index;
    }
    else
    {
        parent_index +=1;
        QTreeWidgetItem *parent_temp=temp->parent();
        findparent(parent_temp);
    }
}

void temp_tree::addData(QString parent, QTreeWidget *item)
{
    QSqlQuery query;
    query.exec("select Name from ResourceDatas where Level='0' and ParentFile='"+parent+"' and Path='Null'");
    while(query.next())
    {
        QString FileName=query.value(0).toString();
        if(!FileName.isEmpty())
        {
            QTreeWidgetItem *temp= new QTreeWidgetItem(item,QStringList(QString(FileName)));
            addData(FileName,temp);
        }
    }
}


void temp_tree::addData(QString parent, QTreeWidgetItem *item)
{
    findparent(item);
    QSqlQuery query;
    query.exec("select Name from ResourceDatas where Level='"+QString::number(parent_index+1)+"' and ParentFile='"+parent+"' and Path='Null' ");
    while(query.next())
    {
        QString FileName=query.value(0).toString();
        if(!FileName.isEmpty())
        {
            QTreeWidgetItem *temp= new QTreeWidgetItem(item,QStringList(QString(FileName)));
            addData(FileName,temp);
        }
    }
    parent_index=-1;
}




bool temp_tree::openDB()
{
    QSqlQuery query;
    query.exec("SELECT id FROM ResourceDatas WHERE id = (SELECT MAX(id) FROM ResourceDatas) LIMIT 1");
    while(query.next())
    {
        id=query.value(0).toInt();
    }
    id+=1;
    ui->temptree->clear();
    ui->temptree->setHeaderHidden(true);
    addData("root",ui->temptree);
    return 1;
}
