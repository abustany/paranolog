#pragma once

#include <QtGui>

class StatusIcon : public QSystemTrayIcon {
    Q_OBJECT

public:
    StatusIcon();

    void setBlinking(bool blinking);

private slots:
    void onBlinkTimerTimeout();

private:
    QIcon m_idleIcon;
    QIcon m_redIcon;
    QTimer m_blinkTimer;
};
