#ifndef GLOBAL_H
#define GLOBAL_H

#include <QSqlDatabase>
#include <QString>




extern QString temp_name;
extern QString temp_path;
extern QSqlDatabase db;
class Global
{
public:
    Global();
};

#endif // GLOBAL_H
