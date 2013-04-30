#pragma once

#include <QtSql>

struct WorkItem {
    QDateTime start, end;
    QString what;
};

class WorkDb {
public:

    WorkDb();

    bool open();
    void close();

    bool addItem(const QDateTime &start, const QDateTime &end, const QString &what);
    QList<WorkItem> getItems();

private:
    QSqlDatabase m_db;
    QSqlQuery m_insertItemQuery;
    QSqlQuery m_getAllItemsQuery;
};
