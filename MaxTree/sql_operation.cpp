#include "sql_operation.h"
Sql_operation::Sql_operation()
{

}
bool Sql_operation::createConnection()
{
    //以后就可以用"sqlite1"与数据库进行连接了
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
    db.setDatabaseName("MyDataBase.db");
    if(!db.open())
    {
//        qDebug()<<"无法建立数据库连接";
        return false;
    }
    return true;
}

//创建数据库表
bool Sql_operation::createTable()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("create table ResourceData(id int primary key, rootId int, rootName varchar, FileName varchar, FilePath varchar, FileStye varchar, FileSize long, Tags varchar, ParentId int)");
    if(success)
    {
//        qDebug() << QObject::tr("数据库表创建成功！\n");
        return true;
    }
    else
    {
//        qDebug() << QObject::tr("数据库表创建失败！\n");
        return false;
    }
}

//向数据库中插入记录
bool Sql_operation::insert()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare("insert into ResourceData values(?, ?, ?, ?, ?, ?, ?, ?, ?)");

    long records = 10;
    for(int i=0; i<records; i++)
    {
        query.bindValue(0, i);
        query.bindValue(1, "四轮");
        query.bindValue(2, "轿车");
        query.bindValue(3, "富康");
        query.bindValue(4, rand()%100);
        query.bindValue(5, rand()%10000);
        query.bindValue(6, rand()%300);
        query.bindValue(7, rand()%200000);
        query.bindValue(8, rand()%52);
        query.bindValue(9, rand()%100);

        bool success=query.exec();
        if(!success)
        {
            QSqlError lastError = query.lastError();
            qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
            return false;
        }
    }
    return true;
}

//查询所有信息
bool Sql_operation::queryAll()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select * from automobil");
    QSqlRecord rec = query.record();
//    qDebug() << QObject::tr("automobil表字段数：" ) << rec.count();
    while(query.next())
    {
        for(int index = 0; index < 10; index++)
            qDebug() << query.value(index) << " ";
        qDebug() << "\n";
    }
    return 1;
}

//根据ID删除记录
bool Sql_operation::deleteById(int id)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString("delete from automobil where id = %1").arg(id));
    if(!query.exec())
    {
//        qDebug() << "删除记录失败！";
        return false;
    }
    return true;
}

//根据ID更新记录
bool Sql_operation::updateById(int id)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString("update automobil set attribute=?,type=?,"
                             "kind=?, nation=?,"
                             "carnumber=?, elevaltor=?,"
                             "distance=?, oil=?,"
                             "temperature=? where id=%1").arg(id));

     query.bindValue(0,"四轮");
     query.bindValue(1,"轿车");
     query.bindValue(2,"富康");
     query.bindValue(3,rand()%100);
     query.bindValue(4,rand()%10000);
     query.bindValue(5,rand()%300);
     query.bindValue(6,rand()%200000);
     query.bindValue(7,rand()%52);
     query.bindValue(8,rand()%100);

     bool success=query.exec();
     if(!success)
     {
          QSqlError lastError = query.lastError();
          qDebug() << lastError.driverText() << QString(QObject::tr("更新失败"));
     }
    return true;
}

//排序
bool Sql_operation::sortById()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success=query.exec("select * from automobil order by id desc");
    if(success)
    {
        qDebug() << QObject::tr("排序成功");
        return 1;
    }
    else
    {
//        qDebug() << QObject::tr("排序失败！");
        return 0;
    }
}
