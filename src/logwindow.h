#pragma once

#include <QtGui>

#include "workdb.h"

class LogWindow : public QWidget {
public:
    LogWindow(WorkDb *db, QWidget *parent = 0);

    bool refresh();

private:
    WorkDb *m_db;
    QTextDocument *m_document;
};
