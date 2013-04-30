#pragma once

#include <QtCore>

#include "logwindow.h"
#include "nagwindow.h"
#include "settingswindow.h"
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
    void showSettings();
    void onSettingsChanged();

private:
    QScopedPointer<StatusIcon> m_statusIcon;
    QScopedPointer<WorkDb> m_db;
    QScopedPointer<NagWindow> m_nagWindow;
    QScopedPointer<LogWindow> m_logWindow;
    QScopedPointer<SettingsWindow> m_settingsWindow;
    QTimer m_nagTimer;
};
