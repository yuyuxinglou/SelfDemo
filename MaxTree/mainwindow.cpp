#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QPainter>
#pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->tabWidget->setVisible(false);
//    ui->comboBox_3->setEditable(true);
    try
    {
        ui->logo_label->setOpenExternalLinks(true);
        ui->logo_label->setText(tr("<a href = 'www.baidu.com'><img src=C:/Users/wuhao/Desktop/小图标.jpg></a>"));
        ui->label_3->setScaledContents(true);
        ui->Tag_tree->setContextMenuPolicy(Qt::CustomContextMenu);
        ui->Img_List->setContextMenuPolicy(Qt::CustomContextMenu);
        ui->File_tree->setColumnCount(2);
        ui->File_tree->hideColumn(1);
        ui->File_tree->setHeaderHidden(true);
        ui->pushButton->setVisible(false);
        addRootNodeAction =new QAction(tr("添加根目录"),this);

        RefreshAllNodeAction =new QAction(tr("刷新"),this);

        addCategoryAction =new QAction(tr("添加目录"),this);

        addTemplateAction =new QAction(tr("添加资源文件"),this);

        deleteNodeAction =new QAction(tr("删除"),this);

        reNameNodeAction =new QAction(tr("重命名"),this);

        addtag=new QAction(tr("添加标签"),this);

        setFixedSize(1800,910);

        connect(ui->Tag_tree,&QTreeWidget::customContextMenuRequested,
                    this,&MainWindow::slotMenuPopup);

        connect(addRootNodeAction,SIGNAL(triggered()),this,SLOT(addRootNode()));

        connect(RefreshAllNodeAction,SIGNAL(triggered()),this,SLOT(RefreshAllNode()));

        connect(addCategoryAction,SIGNAL(triggered()),this,SLOT(addCategory()));

        connect(addTemplateAction,SIGNAL(triggered()),this,SLOT(addTemplate()));

        connect(deleteNodeAction,SIGNAL(triggered()),this,SLOT(deleteNode()));

        connect(reNameNodeAction,SIGNAL(triggered()),this,SLOT(reNameNode()));


        connect(ui->Img_List,&QListWidget::customContextMenuRequested,
                    this,&MainWindow::imglist_slotMenuPopup);

        connect(addtag,SIGNAL(triggered()),this,SLOT(AddTag()));

        ui->Img_List->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        connect(ui->verticalScrollBar, SIGNAL(sliderReleased()), this, SLOT(showImageList()));






        openDB();

        initTree();
    }
     catch (...)
    {
        QMessageBox::warning(NULL, "warning", "初始化失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


//寻找父类方便定位
void MainWindow::findparent(QTreeWidgetItem *temp)
{
    try
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
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "寻找父类失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

//中间图像显示的右键菜单
void MainWindow::imglist_slotMenuPopup(const QPoint &pos)
{
    try
    {
        curlistItem=ui->Img_List->itemAt(pos);
        temp_name=curlistItem->text();
        temp_path=Listimg_path;
        if(curlistItem != NULL)
        {
            QMenu *popMenu =new QMenu(ui->Img_List);
            popMenu->addAction(addtag);
            popMenu->exec(QCursor::pos());
        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "右键菜单失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}


//添加标签到数据集
void MainWindow::AddTag()
{
    try
    {
        temp_tree* temp=new temp_tree();
        temp->show();
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "数据添加弹窗出错！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}























//标签的右键菜单
void MainWindow::slotMenuPopup(const QPoint &pos)
{
    try
    {
        curtagItem=ui->Tag_tree->itemAt(pos);

        if(curtagItem == NULL)
        {
            QMenu *popMenu =new QMenu(ui->Tag_tree);
            popMenu->addAction(addRootNodeAction);
            popMenu->addAction(RefreshAllNodeAction);
            popMenu->exec(QCursor::pos());
        }
        else{
            tagtree = curtagItem->text(0);
            QMenu *popMenu =new QMenu(ui->Tag_tree);
            popMenu->addAction(addCategoryAction);
            popMenu->addAction(addTemplateAction);
            popMenu->addAction(deleteNodeAction);
            popMenu->addAction(reNameNodeAction);
            popMenu->exec(QCursor::pos());
        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "标签右键失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}


//重命名菜单
void MainWindow::reNameNode()
{
    try
    {
        QSqlQuery query;
        QString var = curtagItem->text(0);
        QInputDialog dia(this);
        dia.setWindowTitle("Input Dialog");
        dia.setLabelText("Please input text:");
        dia.setInputMode(QInputDialog::TextInput);//可选参数：DoubleInput  TextInput

        if(dia.exec() == QInputDialog::Accepted)
        {
           curtagItem->setText(0,dia.textValue());
           findparent(curtagItem);
           //更新数据库
           if(!query.exec("update ResourceDatas set Name = '"+curtagItem->text(0)+"' where Name = '"+var+"' and Path='Null' and Level='"+QString::number(parent_index)+"' "))
           {
               QSqlError lastError = query.lastError();
               qDebug() << lastError.driverText() << QString(QObject::tr("表更新失败"));
           }
        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "重命名失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

//删除功能菜单
void MainWindow::deleteNode()
{
    try
    {
        QSqlQuery query;
        int childcout=curtagItem->childCount();
        while (childcout!=0)
        {
            QTreeWidgetItem * childitem=curtagItem->child(childcout-1);
            deleteNode(childitem);
            childcout=curtagItem->childCount();
        }
        QTreeWidgetItem* parent = curtagItem->parent();
        if(parent == NULL )
        {
            //得到索引
            int index = 0;
            int count = ui->Tag_tree->topLevelItemCount();
            for(int i = 0;i<count;i++)
            {
                //QTreeWidget
                //ui->treeWidget->TopLevelItem()
                QTreeWidgetItem* temp = ui->Tag_tree->topLevelItem(i);
                if(curtagItem->text(0) == temp->text(0))
                {
                    index = i;
                }
            }
            ui->Tag_tree->takeTopLevelItem(index);
            if(!query.exec("delete from ResourceDatas where Name = '"+curtagItem->text(0)+"' "))
            {
                QSqlError lastError = query.lastError();
                qDebug() << lastError.driverText() << QString(QObject::tr("param表插入失败"));
            }
        }
        else
        {
            parent->removeChild(curtagItem);
            if(!query.exec("delete from ResourceDatas where Name = '"+curtagItem->text(0)+"' "))
            {
                QSqlError lastError = query.lastError();
                qDebug() << lastError.driverText() << QString(QObject::tr("param表删除失败"));
            }
            if(!query.exec("delete from ResourceDatas where ParentFile = '"+curtagItem->text(0)+"' "))
            {
                QSqlError lastError = query.lastError();
                qDebug() << lastError.driverText() << QString(QObject::tr("param表删除失败"));
            }
        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "删除数据失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

//删除递归
void MainWindow::deleteNode(QTreeWidgetItem *temp)
{
    try
    {
        QSqlQuery query;
        int childcout=temp->childCount();
        if(childcout!=0)
        {
            QTreeWidgetItem * childitem=temp->child(childcout-1);
            deleteNode(childitem);
        }
        QTreeWidgetItem* parent = temp->parent();
        if(parent == NULL )
        {
            //得到索引
            int index = 0;
            int count = ui->Tag_tree->topLevelItemCount();
            for(int i = 0;i<count;i++)
            {
                //QTreeWidget
                //ui->treeWidget->TopLevelItem()
                QTreeWidgetItem* detemp = ui->Tag_tree->topLevelItem(i);
                if(temp->text(0) == detemp->text(0))
                {
                    index = i;
                }
            }
            ui->Tag_tree->takeTopLevelItem(index);
        }
        else
        {
            parent->removeChild(temp);
            if(!query.exec("delete from ResourceDatas where Name = '"+temp->text(0)+"' "))
            {
                QSqlError lastError = query.lastError();
                qDebug() << lastError.driverText() << QString(QObject::tr("param表删除失败"));
            }
            if(!query.exec("delete from ResourceDatas where ParentFile = '"+temp->text(0)+"' "))
            {
                QSqlError lastError = query.lastError();
                qDebug() << lastError.driverText() << QString(QObject::tr("param表删除失败"));
            }
        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "删除递归失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }


}

//添加资源文件
void MainWindow::addTemplate()
{
    try
    {
        QSqlQuery query;
        QFileDialog* f=new QFileDialog(this);
        f->setWindowTitle("选择要添加的文件");
        f->setViewMode(QFileDialog::Detail);
        QString filePath;
        if(f->exec() == QDialog::Accepted)
        {
           filePath=f->selectedFiles()[0];
           QFileInfo fileInfo(filePath);
           findparent(curtagItem);
           if(query.exec("select Name from ResourceDatas where Name='"+fileInfo.completeBaseName()+"' and ParentFile='"+curtagItem->text(0)+"' and Path='"+fileInfo.path()+"' and Level='"+QString::number(parent_index+1)+"' "))
           {
               QString FileName=query.value(0).toString();
               if(FileName.isEmpty())
               {
                  query.prepare("insert into ResourceDatas values (?,?,?,?,?)");
                  query.bindValue(0,id);
                  query.bindValue(1,fileInfo.completeBaseName());
                  query.bindValue(2,fileInfo.path());
                  query.bindValue(3,curtagItem->text(0));
                  query.bindValue(4,parent_index+1);
                  if(!query.exec())
                  {
                      QSqlError lastError = query.lastError();
                      qDebug() << lastError.driverText() << QString(QObject::tr("param表插入失败"));
                  }
                  id+=1;
               }
           }
           parent_index=-1;
        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "收藏失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}
//添加目录文件
void MainWindow::addCategory()
{
    try
    {
        QSqlQuery query;
        QInputDialog dia(this);
        dia.setWindowTitle("Input Dialog");
        dia.setLabelText("Please input text:");
        dia.setInputMode(QInputDialog::TextInput);//可选参数：DoubleInput  TextInput
        if(dia.exec() == QInputDialog::Accepted)
        {
            findparent(curtagItem);
            if(query.exec("select Name from ResourceDatas where Name='"+dia.textValue()+"' and ParentFile='root' and Path='Null' and Level='"+QString::number(parent_index+1)+"' " ))
            {
                QString FileName=query.value(0).toString();
                if(FileName.isEmpty())
                {
                    QTreeWidgetItem *temp=new QTreeWidgetItem(curtagItem);
                    temp->setText(0,dia.textValue());
                    QVariant var;
                    QString str = QUuid::createUuid().toString();
                    var.setValue(str);
                    temp->setData(0,Qt::UserRole,var);
                    query.prepare("insert into ResourceDatas values (?,?,?,?,?)");
                    query.bindValue(0,id);
                    query.bindValue(1,dia.textValue());
                    query.bindValue(2,"Null");
                    query.bindValue(3,curtagItem->text(0));
                    query.bindValue(4,parent_index+1);
                    if(!query.exec())
                    {
                        QSqlError lastError = query.lastError();
                        qDebug() << lastError.driverText() << QString(QObject::tr("param表插入失败"));
                    }
                    id+=1;
                }
                else
                {
                   qDebug()<<"err";
                }
            }
            parent_index=-1;
        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "新建目录失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}
//刷新
void MainWindow::RefreshAllNode()
{
    try
    {
        initTree();
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "刷新文件树失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

//添加根节点
void MainWindow::addRootNode()
{
    try
    {
        QSqlQuery query;
        QTreeWidgetItem *temp=new QTreeWidgetItem(ui->Tag_tree);
        QInputDialog dia(this);
        dia.setWindowTitle("Input Dialog");
        dia.setLabelText("Please input text:");
        dia.setInputMode(QInputDialog::TextInput);
        if(dia.exec() == QInputDialog::Accepted)
        {
           if(dia.textValue().isEmpty())
           {
               qDebug()<<"this empty";
           }
           else
           {
               if(query.exec("select Name from ResourceDatas where Name='"+dia.textValue()+"' and ParentFile='root' and Path='Null' and Level='0' " ))
               {
                   QString FileName=query.value(0).toString();
                   if(FileName.isEmpty())
                   {
                       temp->setText(0,dia.textValue());
                       QVariant var;
                       QString str = QUuid::createUuid().toString();
                       var.setValue(str);
                       temp->setData(0,Qt::UserRole,var);
                       query.prepare("insert into ResourceDatas values (?,?,?,?,?)");
                       query.bindValue(0,id);
                       query.bindValue(1,dia.textValue());
                       query.bindValue(2,"Null");
                       query.bindValue(3,"root");
                       query.bindValue(4,0);
                       if(!query.exec())
                       {
                           QSqlError lastError = query.lastError();
                           qDebug() << lastError.driverText() << QString(QObject::tr("param表插入失败"));
                       }
                       id+=1;
                   }
                   else
                   {
                      qDebug()<<"err";
                   }
               }
           }
        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "添加根节点失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}



//初始化
void MainWindow::initTree()
{
    try
    {
        ui->Tag_tree->clear();
        ui->Tag_tree->setHeaderHidden(true);
        addData("root",ui->Tag_tree);
        ui->Img_List->setViewMode(QListWidget::IconMode);
        ui->Img_List->setIconSize(QSize(200,200));
        ui->Img_List->setSpacing(10);
        ui->Img_List->setResizeMode(QListView::Adjust);
        ui->Img_List->setMovement(QListView::Static);
        ui->Img_List->setViewMode(QListView::IconMode);
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "标签树数据库初始化失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

//添加标签数据
void MainWindow::addData(QString parent, QTreeWidget *item)
{
    try
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
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "初始化添加数据失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

//递归添加
void MainWindow::addData(QString parent, QTreeWidgetItem *item)
{
    try
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
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "初始化添加递归数据失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}



//打开数据库
bool MainWindow::openDB()
{
    try
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("MyDataBase.db");
        if (!db.open())
        {
            qDebug()<< db.lastError();
            return 0;
        }
        else{
            QSqlQuery query;
            query.exec("SELECT * FROM File_path ");
            while(query.next())
            {
                QFileInfo info(query.value(0).toString());
                QTreeWidgetItem *rootItem=new QTreeWidgetItem(QStringList()<<info.baseName()<<info.absoluteFilePath());
                ui->File_tree->addTopLevelItem(rootItem);
                SetData(rootItem, info.absoluteFilePath()+"/");
            }
            query.exec("SELECT id FROM ResourceDatas WHERE id = (SELECT MAX(id) FROM ResourceDatas) LIMIT 1");
            while(query.next())
            {
                id=query.value(0).toInt();
            }
            id+=1;
            ui->Img_List->setViewMode(QListWidget::IconMode);
            ui->Img_List->setIconSize(QSize(200,200));
            ui->Img_List->setSpacing(10);
            ui->Img_List->setResizeMode(QListView::Adjust);
            ui->Img_List->setMovement(QListView::Static);
            ui->Tag_tree->clear();
            ui->Tag_tree->setHeaderHidden(true);
            addData("root",ui->Tag_tree);
            return 1;
        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "数据库打开失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return 0;
    }
}



//搜索栏的变化
void MainWindow::on_search_lineEdit_textChanged(const QString &arg1)
{
    try
    {
        //    QSqlQuery query;
        //    query.exec("SELECT DISTINCT Name,Path from ResourceDatas WHERE Name LIKE '"+arg1+"%' and Path!='Null' ");
        //    ui->Img_List->clear();
        //    while(query.next())
        //    {
        //        QString Name = query.value(0).toString();
        //        QString path=query.value(1).toString()+"/"+Name+".jpg";
        //        QListWidgetItem *imageItem = new QListWidgetItem;
        //        imageItem->setIcon(QIcon(path));
        //        imageItem->setText(Name);
        //        imageItem->setSizeHint(QSize(215, 200));
        //        ui->Img_List->addItem(imageItem);
        //    }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "搜索失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

//搜索按钮点击
void MainWindow::on_on_search_clicked()
{
    try
    {
//        QSqlQuery query;
//        query.exec("SELECT DISTINCT Name,Path from ResourceDatas WHERE Name LIKE '"+ui->search_lineEdit->text()+"%'");
//        ui->Img_List->clear();
//        while(query.next())
//        {
//            QString Name = query.value(0).toString();
//            QString path=query.value(1).toString()+"/"+Name+".jpg";
//            QListWidgetItem *imageItem = new QListWidgetItem;
//            imageItem->setIcon(QIcon(path));
//            imageItem->setText(Name);
//            imageItem->setSizeHint(QSize(215, 200));
//            ui->Img_List->addItem(imageItem);
//        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "搜索按钮失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

//导出按键点击
void MainWindow::on_on_export_clicked()
{
    try
    {
        if(ui->comboBox->currentIndex()==0)
        {
            tcpSocket=new QTcpSocket();
            tcpSocket->abort();
            tcpSocket->connectToHost("127.0.0.1",25630);
            connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMesg()));
        }
        else if(ui->comboBox->currentIndex()==1)
        {
            tcpSocket=new QTcpSocket();
            tcpSocket->abort();
            tcpSocket->connectToHost("127.0.0.1",25631);
            connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMesg()));
        }
        QString temp_path=Listimg_path+"/"+curlistItem->text()+"."+ui->comboBox_2->currentText();
        QFileInfo fileInfo(temp_path);
        if(fileInfo.isFile())
        {
            tcpSocket->write(temp_path.toStdString().c_str(),strlen(temp_path.toStdString().c_str()));
        }
        else
        {
            QMessageBox::warning(NULL, "warning", "文件不存在！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }

    //        tcpSocket->write("s");
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "导出失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}










//中间显示点击状态移除
void MainWindow::on_Img_List_itemSelectionChanged()
{
    try
    {
        //    ui->groupBox_3->setGeometry(270,100,1531,771);
        //    ui->Img_List->setGeometry(10,10,1511,751);
        //    ui->tabWidget->setVisible(false);
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "界面变化失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

//标签树点击
void MainWindow::on_Tag_tree_itemClicked(QTreeWidgetItem *item, int column)
{
    try
    {
        ui->search_lineEdit->clear();
        ui->Img_List->clear();
        QSqlQuery query;
        tagtree=item->text(0);
        findparent(item);
        query.exec("select Name,Path from ResourceDatas where Level='"+QString::number(parent_index+1)+"' and ParentFile='"+item->text(0)+"' and Path!='Null' ");
        while(query.next())
        {
            QString Name = query.value(0).toString();
            QString path = query.value(1).toString()+"/"+Name+".jpg";
            qDebug()<<path;
            QListWidgetItem *imageItem = new QListWidgetItem;
            QPixmap pixmap(path);
            QLabel *item_img = new QLabel();
            item_img->setScaledContents(true);
            item_img->setPixmap(pixmap);
            ui->Img_List->setItemWidget(imageItem,item_img);
            imageItem->setText(Name);
            imageItem->setSizeHint(QSize(215, 200));
            ui->Img_List->addItem(imageItem);
        }
        listimg_display=false;
        parent_index=-1;
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "标签树点击失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

//添加按钮,添加路径文件到树
void MainWindow::on_on_add_data_clicked()
{
    try
    {
        QFileDialog *fileDialog = new QFileDialog(this);
        fileDialog->setFileMode(QFileDialog::Directory);
        if (fileDialog->exec() == QDialog::Accepted)
        {
            QFileInfo info(fileDialog->selectedFiles()[0]);
            QSqlQuery query;
            query.prepare("insert into File_path values (?)");
            query.bindValue(0,info.absoluteFilePath());
            if(!query.exec())
            {
                QSqlError lastError = query.lastError();
                qDebug() << lastError.driverText() << QString(QObject::tr("param表插入失败"));
            }
            else
            {
                QTreeWidgetItem *rootItem=new QTreeWidgetItem(QStringList()<<info.baseName()<<info.absoluteFilePath());
                ui->File_tree->addTopLevelItem(rootItem);
                SetData(rootItem, info.absoluteFilePath()+"/");
            }
        }
        else
        {
            qDebug()<<"err";
        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "添加新路径失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}



//文件树来进行生成数据
void MainWindow::SetData(QTreeWidgetItem *rootItem,QString path)
{
    try
    {
        QDir dir(path);
        dir.setSorting(QDir::Name);
        QFileInfoList folder_list = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
        for (int i = 0; i!=folder_list.size(); ++i)   //这个用来寻找文件夹
        {
            QString namePath = folder_list.at(i).absoluteFilePath();
            QFileInfo folderInfo = folder_list.at(i);
            QTreeWidgetItem *childRoot = new QTreeWidgetItem(QStringList()<<QString(folderInfo.fileName())<<namePath);
    //        childRoot->setIcon(0,QIcon(":/Image/folder.png"));
            rootItem->addChild(childRoot);
        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "目录加载失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}




//文件树点击
void MainWindow::on_File_tree_itemClicked(QTreeWidgetItem *item, int column)
{
    try
    {
        curFileItem=item;
        ui->Img_List->clear();
        Listimg_path=item->text(1);
        ui->search_lineEdit->setText(Listimg_path);
        QDir dir(item->text(1));
        dir.setSorting(QDir::Name);
        dir.setNameFilters(QStringList()<<"*.jpg"<<"*.FBX"<<"*.blend"<<"*.bmp");
        folder_list = dir.entryInfoList();
        if(folder_list.size()!=0)
        {
            ui->Img_List->clear();
            ui->verticalScrollBar->setValue(0);
            ui->verticalScrollBar->setRange(0, folder_list.size()/12);
            ui->verticalScrollBar->setPageStep(10);
            ui->verticalScrollBar->setSingleStep(2);
            m_ImageSum = folder_list.size();
            qDebug()<< m_ImageSum;
            if(m_ImageSum<12)
            {
                for(int i = 0; i < m_ImageSum; ++i)
                {
                    QListWidgetItem *item = new QListWidgetItem(folder_list[i].baseName(), ui->Img_List);
                    item->setTextAlignment(Qt::AlignBottom|Qt::AlignHCenter);
                    QWidget *widget = new QWidget;
                    widget->setFixedSize(250,234);
                    QVBoxLayout *widgetLayout = new QVBoxLayout;
                    QLabel *suffixLabel = new QLabel(folder_list[i].completeSuffix());
                    QLabel *imageLabel = new QLabel;
                    imageLabel->setFixedSize(QSize(250,224));
                    widget->setLayout(widgetLayout);
                    widgetLayout->setMargin(0);
                    widgetLayout->setSpacing(0);
                    widgetLayout->addWidget(suffixLabel);
                    widgetLayout->addWidget(imageLabel);
                    QPixmap pixmap(folder_list[i].absoluteFilePath());
                    if(pixmap.isNull())
                    {
                        pixmap.load(tempimg_path);
                    }
                    pixmap=pixmap.scaled(224,224,Qt::KeepAspectRatio);
                    imageLabel->setPixmap(pixmap);
                    imageLabel->setAlignment(Qt::AlignCenter);
                    suffixLabel->setAlignment(Qt::AlignRight);
                    item->setSizeHint(QSize(250,250));
                    ui->Img_List->setItemWidget(item,widget);
                    ui->Img_List->addItem(item);
                }
            }
            else
            {
                for(int i = 0; i < 12; ++i)
                {
                    QListWidgetItem *item = new QListWidgetItem(folder_list[i].baseName(), ui->Img_List);
                    item->setTextAlignment(Qt::AlignBottom|Qt::AlignHCenter);
                    QWidget *widget = new QWidget;
                    widget->setFixedSize(250,234);
                    QVBoxLayout *widgetLayout = new QVBoxLayout;
                    QLabel *suffixLabel = new QLabel(folder_list[i].completeSuffix());
                    QLabel *imageLabel = new QLabel;
                    imageLabel->setFixedSize(QSize(250,224));
                    widget->setLayout(widgetLayout);
                    widgetLayout->setMargin(0);
                    widgetLayout->setSpacing(0);
                    widgetLayout->addWidget(suffixLabel);
                    widgetLayout->addWidget(imageLabel);
                    QPixmap pixmap(folder_list[i].absoluteFilePath());
                    if(pixmap.isNull())
                    {
                        pixmap.load(tempimg_path);
                    }
                    pixmap=pixmap.scaled(224,224,Qt::KeepAspectRatio);
                    imageLabel->setPixmap(pixmap);
                    imageLabel->setAlignment(Qt::AlignCenter);
                    suffixLabel->setAlignment(Qt::AlignRight);
                    item->setSizeHint(QSize(250,250));
                    ui->Img_List->setItemWidget(item,widget);
                    ui->Img_List->addItem(item);
                }
            }

        }
        listimg_display=true;
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "文件树点击失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}


//滚轮重构
void MainWindow::wheelEvent(QWheelEvent *event)
{
    try
    {
        int numDegrees = event->angleDelta().y() / 8; //获取滚轮的垂直方向的值
        int numSteps = - numDegrees / 15; //这里取负号，目的是为了实现鼠标往下滚动时是数值增大，往上滚动时是数值减小
        if(event->orientation() == Qt::Vertical)
        {
            int index = ui->verticalScrollBar->value() + numSteps;
            ui->verticalScrollBar->setValue(index);
        }
        event->accept(); //表示此处已经处理了鼠标的滚动事件，不需要传给父部件处理
    }
    catch (...)
    {
        QMessageBox::warning(NULL, "warning", "滚轮重构失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}





//文件树展开
void MainWindow::on_File_tree_itemExpanded(QTreeWidgetItem *item)
{
    try
    {
        QDir dir(item->text(1));
        dir.setSorting(QDir::Name);
        QFileInfoList folder_list = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
        for (int i = 0; i!=folder_list.size(); ++i)   //这个用来寻找文件夹
        {
            QString namePath = folder_list.at(i).absoluteFilePath();
            QDir dir(namePath);
            dir.setSorting(QDir::Name);
            QFileInfoList folder_list = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
            if(folder_list.size()!=item->child(i)->childCount())
            {
                for (int j = 0; j != folder_list.size(); ++j)
                {
                    QString namePath = folder_list.at(j).absoluteFilePath();
                    QFileInfo folderInfo = folder_list.at(j);
                    QTreeWidgetItem *childRoot1 = new QTreeWidgetItem(QStringList()<<QString(folderInfo.fileName())<<namePath);
            //        childRoot->setIcon(0,QIcon(":/Image/folder.png"));
                    item->child(i)->addChild(childRoot1);
                }
            }
        }
    }
    catch (...)
    {
        QMessageBox::warning(NULL, "warning", "文件树展开失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}




//中间图像显示按下(无论左右)
void MainWindow::on_Img_List_itemPressed(QListWidgetItem *item)
{
    try
    {
        curlistItem=item;
        if(!listimg_display)
        {
            QSqlQuery query;
            query.exec("select Path from ResourceDatas where  ParentFile='"+tagtree+"' and Name='"+item->text()+"'");
            while(query.next())
            {
                Listimg_path = query.value(0).toString();
                QDir dir(Listimg_path);
                dir.setSorting(QDir::Name);
                dir.setNameFilters(QStringList()<<"*.max"<<"*.blend"<<"*.FBX"<<"*.json");
                QFileInfoList folder_list = dir.entryInfoList();
                QString temptype;
                for (int i = 0; i!=folder_list.size(); ++i)   //这个用来寻找文件
                {
                    if (folder_list.at(i).baseName()==item->text())
                    {
                        temptype+=folder_list.at(i).completeSuffix()+" ";
                    }
                }
                QImage* img=new QImage();
                img->load(Listimg_path+"/"+item->text()+".jpg");
                ui->label_3->setPixmap(QPixmap::fromImage(*img));
                ui->label_10->setText("Type:"+temptype);
                ui->search_lineEdit->setText(Listimg_path);
                temptype="";
            }
        }
        else
        {
            QDir dir(Listimg_path);
            dir.setSorting(QDir::Name);
            dir.setNameFilters(QStringList()<<"*.max"<<"*.blend"<<"*.FBX"<<"*.json");
            QFileInfoList folder_list = dir.entryInfoList();
            QString temptype;
            for (int i = 0; i!=folder_list.size(); ++i)   //这个用来寻找文件
            {
                if (folder_list.at(i).baseName()==item->text())
                {
                    temptype+=folder_list.at(i).completeSuffix()+" ";
                }
            }
            QImage* img=new QImage;
            img->load(Listimg_path+"/"+item->text()+".jpg");
            ui->label_3->setPixmap(QPixmap::fromImage(*img));
            ui->search_lineEdit->setText(Listimg_path);
            ui->label_10->setText("Type:"+temptype);
            temptype="";
        }
    }
    catch (...)
    {
        QMessageBox::warning(NULL, "warning", "图像显示点击失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}



//文件树删除键
void MainWindow::on_on_delete_data_clicked()
{
    try
    {
        QSqlQuery query;
        if(DelDir(curFileItem->text(1)))
        {
            if(curFileItem->parent() == NULL )
            {
                //得到索引
                int index = 0;
                int count = ui->File_tree->topLevelItemCount();
                for(int i = 0;i<count;i++)
                {
                    QTreeWidgetItem* temp = ui->File_tree->topLevelItem(i);
                    if(curFileItem->text(0) == temp->text(0))
                    {
                        index = i;
                    }
                }
                ui->File_tree->takeTopLevelItem(index);
                if(!query.exec("delete from File_path where File_Path = '"+curFileItem->text(0)+"' "))
                {
                    QSqlError lastError = query.lastError();
                    qDebug() << lastError.driverText() << QString(QObject::tr("表删除失败"));
                }
            }
            else
            {
                QMessageBox::StandardButton rb=QMessageBox::warning(NULL, "warning", "删除会删除系统文件，请确实是否删除！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                if(rb == QMessageBox::Yes)
                {
                    curFileItem->parent()->removeChild(curFileItem);
                    if(!query.exec("delete from File_path where File_Path = '"+curFileItem->text(0)+"' "))
                    {
                        QSqlError lastError = query.lastError();
                        qDebug() << lastError.driverText() << QString(QObject::tr("param表删除失败"));
                    }
                }
            }
        }
        else
        {
            qDebug()<<"删除失败";
        }
    }
    catch (...)
    {
        QMessageBox::warning(NULL, "warning", "文件树删除失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}



//删除时用的文件循环
bool MainWindow::DelDir(const QString &path)
{
    try
    {
        if (path.isEmpty()){
            return false;
        }
    //    QDir dir(path);
    //    if(!dir.exists()){
    //        return true;
    //    }
    //    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤
    //    QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息
    //    foreach (QFileInfo file, fileList){ //遍历文件信息
    //        if (file.isFile()){ // 是文件，删除
    //            file.dir().remove(file.fileName());
    //        }else{ // 递归删除
    //            DelDir(file.absoluteFilePath());
    //        }
    //    }
    //    return dir.rmpath(dir.absolutePath()); // 删除文件夹
        return 1;
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "系统文件删除失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return 0;
    }

}




//打开选中的文件夹
void MainWindow::on_open_dir_clicked()
{
    try
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(curFileItem->text(1)));
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "打开文件失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}



void MainWindow::on_pushButton_clicked()
{
    try
    {
        if(ui->comboBox->currentIndex()==0)
        {
            tcpSocket=new QTcpSocket();
            tcpSocket->abort();
            tcpSocket->connectToHost("127.0.0.1",25630);
            connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMesg()));
        }
        else if(ui->comboBox->currentIndex()==1)
        {
            tcpSocket=new QTcpSocket();
            tcpSocket->abort();
            tcpSocket->connectToHost("127.0.0.1",25631);
            connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMesg()));
        }
        tcpSocket->write("Bye",strlen("Bye"));
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "Tcp连接失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }


}

//选择框激活事件
void MainWindow::on_comboBox_3_activated(int index)
{
    try
    {
        ui->Img_List->clear();
        QDir dir(Listimg_path);
        dir.setSorting(QDir::Name);
    //    dir.setNameFilters(QStringList()<<"*.jpg"<<"*.bmp"<<"*.FBX");
        dir.setNameFilters(QStringList()<<"*."+ui->comboBox_3->currentText());
        QFileInfoList folder_list = dir.entryInfoList();
        qDebug()<<folder_list.size();
        folder_list = dir.entryInfoList();
        if(folder_list.size()!=0)
        {
            ui->verticalScrollBar->setValue(0);
            ui->verticalScrollBar->setRange(0, folder_list.size()/12);
            ui->verticalScrollBar->setPageStep(10);
            ui->verticalScrollBar->setSingleStep(2);
            m_ImageSum = ui->verticalScrollBar->maximum() + 1;
            if(m_ImageSum < 12)
            {
                for(int i = 0; i < m_ImageSum; ++i)
                {
                    QListWidgetItem *item = new QListWidgetItem(folder_list[i].baseName(), ui->Img_List);
                    item->setTextAlignment(Qt::AlignBottom|Qt::AlignHCenter);
                    QWidget *widget = new QWidget;
                    widget->setFixedSize(250,234);
                    QVBoxLayout *widgetLayout = new QVBoxLayout;
                    QLabel *suffixLabel = new QLabel(folder_list[i].completeSuffix());
                    QLabel *imageLabel = new QLabel;
                    imageLabel->setFixedSize(QSize(250,224));
                    widget->setLayout(widgetLayout);
                    widgetLayout->setMargin(0);
                    widgetLayout->setSpacing(0);
                    widgetLayout->addWidget(suffixLabel);
                    widgetLayout->addWidget(imageLabel);
                    QPixmap pixmap(folder_list[i].absoluteFilePath());
                    if(pixmap.isNull())
                    {
                        pixmap.load(tempimg_path);
                    }
                    pixmap=pixmap.scaled(224,224,Qt::KeepAspectRatio);
                    imageLabel->setPixmap(pixmap);
                    imageLabel->setAlignment(Qt::AlignCenter);
                    suffixLabel->setAlignment(Qt::AlignRight);
                    item->setSizeHint(QSize(250,250));
                    ui->Img_List->setItemWidget(item,widget);
                    ui->Img_List->addItem(item);
                }
            }
            else
            {
                for(int i = 0; i < 12; ++i)
                {
                    QListWidgetItem *item = new QListWidgetItem(folder_list[i].baseName(), ui->Img_List);
                    item->setTextAlignment(Qt::AlignBottom|Qt::AlignHCenter);
                    QWidget *widget = new QWidget;
                    widget->setFixedSize(250,234);
                    QVBoxLayout *widgetLayout = new QVBoxLayout;
                    QLabel *suffixLabel = new QLabel(folder_list[i].completeSuffix());
                    QLabel *imageLabel = new QLabel;
                    imageLabel->setFixedSize(QSize(250,224));
                    widget->setLayout(widgetLayout);
                    widgetLayout->setMargin(0);
                    widgetLayout->setSpacing(0);
                    widgetLayout->addWidget(suffixLabel);
                    widgetLayout->addWidget(imageLabel);
                    QPixmap pixmap(folder_list[i].absoluteFilePath());
                    if(pixmap.isNull())
                    {
                        pixmap.load(tempimg_path);
                    }
                    pixmap=pixmap.scaled(224,224,Qt::KeepAspectRatio);
                    imageLabel->setPixmap(pixmap);
                    imageLabel->setAlignment(Qt::AlignCenter);
                    suffixLabel->setAlignment(Qt::AlignRight);
                    item->setSizeHint(QSize(250,250));
                    ui->Img_List->setItemWidget(item,widget);
                    ui->Img_List->addItem(item);
                }
            }
        }
    } catch (...)
    {
        QMessageBox::warning(NULL, "warning", "文件筛选激活失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

//滚轮移动
void MainWindow::on_verticalScrollBar_valueChanged(int value)
{
    try
    {
        if(m_ImageSum>12)
        {
            ui->Img_List->clear();
            if(value<=0)
            {
                for(int i = 0; i < 12; ++i)
                {
                    QListWidgetItem *item = new QListWidgetItem(folder_list[i].baseName(), ui->Img_List);
                    item->setTextAlignment(Qt::AlignBottom|Qt::AlignHCenter);
                    QWidget *widget = new QWidget;
                    widget->setFixedSize(250,234);
                    QVBoxLayout *widgetLayout = new QVBoxLayout;
                    QLabel *suffixLabel = new QLabel(folder_list[i].completeSuffix());
                    QLabel *imageLabel = new QLabel;
                    imageLabel->setFixedSize(QSize(250,224));
                    widget->setLayout(widgetLayout);
                    widgetLayout->setMargin(0);
                    widgetLayout->setSpacing(0);
                    widgetLayout->addWidget(suffixLabel);
                    widgetLayout->addWidget(imageLabel);
                    QPixmap pixmap(folder_list[i].absoluteFilePath());
                    if(pixmap.isNull())
                    {
                        pixmap.load(tempimg_path);
                    }
                    pixmap=pixmap.scaled(224,224,Qt::KeepAspectRatio);
                    imageLabel->setPixmap(pixmap);
                    imageLabel->setAlignment(Qt::AlignCenter);
                    suffixLabel->setAlignment(Qt::AlignRight);
                    item->setSizeHint(QSize(250,250));
                    ui->Img_List->setItemWidget(item,widget);
                    ui->Img_List->addItem(item);
                }
            }
            else if((value+1)*12>m_ImageSum)
            {
                qDebug()<<"dad2";
                for(int i = value*12; i < m_ImageSum; ++i)
                {
                    QListWidgetItem *item = new QListWidgetItem(folder_list[i].baseName(), ui->Img_List);
                    item->setTextAlignment(Qt::AlignBottom|Qt::AlignHCenter);
                    QWidget *widget = new QWidget;
                    widget->setFixedSize(250,234);
                    QVBoxLayout *widgetLayout = new QVBoxLayout;
                    QLabel *suffixLabel = new QLabel(folder_list[i].completeSuffix());
                    QLabel *imageLabel = new QLabel;
                    imageLabel->setFixedSize(QSize(250,224));
                    widget->setLayout(widgetLayout);
                    widgetLayout->setMargin(0);
                    widgetLayout->setSpacing(0);
                    widgetLayout->addWidget(suffixLabel);
                    widgetLayout->addWidget(imageLabel);
                    QPixmap pixmap(folder_list[i].absoluteFilePath());
                    if(pixmap.isNull())
                    {
                        pixmap.load(tempimg_path);
                    }
                    pixmap=pixmap.scaled(224,224,Qt::KeepAspectRatio);
                    imageLabel->setPixmap(pixmap);
                    imageLabel->setAlignment(Qt::AlignCenter);
                    suffixLabel->setAlignment(Qt::AlignRight);
                    item->setSizeHint(QSize(250,250));
                    ui->Img_List->setItemWidget(item,widget);
                    ui->Img_List->addItem(item);
                }
            }
            else
            {
                for(int i = value*12; i < value*12+12; ++i)
                {
                    QListWidgetItem *item = new QListWidgetItem(folder_list[i].baseName(), ui->Img_List);
                    item->setTextAlignment(Qt::AlignBottom|Qt::AlignHCenter);
                    QWidget *widget = new QWidget;
                    widget->setFixedSize(250,234);
                    QVBoxLayout *widgetLayout = new QVBoxLayout;
                    QLabel *suffixLabel = new QLabel(folder_list[i].completeSuffix());
                    QLabel *imageLabel = new QLabel;
                    imageLabel->setFixedSize(QSize(250,224));
                    widget->setLayout(widgetLayout);
                    widgetLayout->setMargin(0);
                    widgetLayout->setSpacing(0);
                    widgetLayout->addWidget(suffixLabel);
                    widgetLayout->addWidget(imageLabel);
                    QPixmap pixmap(folder_list[i].absoluteFilePath());
                    if(pixmap.isNull())
                    {
                        pixmap.load(tempimg_path);
                    }
                    pixmap=pixmap.scaled(224,224,Qt::KeepAspectRatio);
                    imageLabel->setPixmap(pixmap);
                    imageLabel->setAlignment(Qt::AlignCenter);
                    suffixLabel->setAlignment(Qt::AlignRight);
                    item->setSizeHint(QSize(250,250));
                    ui->Img_List->setItemWidget(item,widget);
                    ui->Img_List->addItem(item);
                }
            }
        }
    }
    catch (...)
    {
        QMessageBox::warning(NULL, "warning", "鼠标点击重构失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}



