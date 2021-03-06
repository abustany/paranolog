#include <workdb.h>

#include <QDesktopServices>

static const QStringList SqliteDriverNames = QStringList()
        << QString::fromLatin1("QSQLITE")
        << QString::fromLatin1("QSQLITE3");
static const QString CreateSchemaQuery = QString::fromLatin1(
    "CREATE TABLE IF NOT EXISTS work (start TEXT, end TEXT, what TEXT)"
);

WorkDb::WorkDb()
{
}

bool
WorkDb::open()
{
    static const QString dbName = QString::fromLatin1("paranolog.db");

    QString driverName;

    foreach(const QString &driver, SqliteDriverNames) {
        if (QSqlDatabase::isDriverAvailable(driver)) {
            driverName = driver;
            break;
        }
    }

    if (driverName.isNull()) {
        qWarning() << "SQLite driver is not available";
        return false;
    }

    QString dbFolderPath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);

    if (dbFolderPath.isEmpty()) {
        dbFolderPath = QString::fromLatin1("%1/%2").arg(QDir::homePath(), QString::fromLatin1(".paranolog"));
    }

    if (not QDir(dbFolderPath).mkpath(QString::fromLatin1("."))) {
        qWarning() << "Cannot create DB directory";
        return false;
    }

    const QString dbPath = QString::fromLatin1("%1/%2").arg(dbFolderPath, dbName);

    qDebug() << "Opening work DB in " << dbPath;

    m_db = QSqlDatabase::addDatabase(driverName);
    m_db.setDatabaseName(dbPath);

    if (not m_db.open()) {
        qWarning() << "Could not open SQLite database: " << m_db.lastError().text();
        return false;
    }

    m_db.exec(CreateSchemaQuery);

    if (m_db.lastError().isValid()) {
        qWarning() << "Could not create DB schema: " << m_db.lastError().text();
        return false;
    }

    m_insertItemQuery = QSqlQuery(m_db);

    if (not m_insertItemQuery.prepare(QString::fromLatin1("INSERT INTO work VALUES(:start, :end, :what)"))) {
        qWarning() << "Could not prepare DB statement: " << m_db.lastError().text();
        return false;
    }

    m_getAllItemsQuery = QSqlQuery(m_db);

    if (not m_getAllItemsQuery.prepare(QString::fromLatin1("SELECT * FROM work"))) {
        qWarning() << "Could not prepare DB statement: " << m_db.lastError().text();
        return false;
    }

    return true;
}

void
WorkDb::close()
{
    if (m_db.isValid()) {
        m_db.close();
    }
}

bool
WorkDb::addItem(const QDateTime &start, const QDateTime &end, const QString &what)
{
    static const QString StartColumn = QString::fromLatin1(":start");
    static const QString EndColumn = QString::fromLatin1(":end");
    static const QString WhatColumn = QString::fromLatin1(":what");

    m_insertItemQuery.bindValue(StartColumn, start);
    m_insertItemQuery.bindValue(EndColumn, end);
    m_insertItemQuery.bindValue(WhatColumn, what);

    const bool success = m_insertItemQuery.exec();

    if (not success) {
        qWarning() << "Could not insert item in DB: " << m_db.lastError().text();
    }

    return success;
}

QList<WorkItem>
WorkDb::getItems()
{
    QList<WorkItem> items;

    if (not m_getAllItemsQuery.exec()) {
        qWarning() << "Could not fetch items from DB: " << m_db.lastError().text();
        return items;
    }

    while (m_getAllItemsQuery.next()) {
        WorkItem i;

        i.start = m_getAllItemsQuery.value(0).toDateTime();
        i.end = m_getAllItemsQuery.value(1).toDateTime();
        i.what = m_getAllItemsQuery.value(2).toString();

        items.append(i);
    }

    return items;
}
