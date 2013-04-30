#pragma once

#include <QtSql>

class WorkDb {
public:
    WorkDb();

    bool open();
    void close();

    bool addItem(const QDateTime &start, const QDateTime &end, const QString &what);

private:
    QSqlDatabase m_db;
    QSqlQuery m_insertItemQuery;
};
