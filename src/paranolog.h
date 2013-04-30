#pragma once

#include <QtCore>

#include "logwindow.h"
#include "nagwindow.h"
#include "statusicon.h"
#include "workdb.h"

class Paranolog : public QObject {
    Q_OBJECT

public:
    Paranolog();
    bool run();

private slots:
    void onStatusIconActivated(QSystemTrayIcon::ActivationReason reason);
    void onNagTimerTimeout();
    void onNewData(const QDateTime &start, const QDateTime &end, const QString &what);
    void showLog();

private:
    QScopedPointer<StatusIcon> m_statusIcon;
    QScopedPointer<WorkDb> m_db;
    QScopedPointer<NagWindow> m_nagWindow;
    QScopedPointer<LogWindow> m_logWindow;
    QTimer m_nagTimer;
};
