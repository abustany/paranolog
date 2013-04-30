#include "statusicon.h"

static const QString IconPathIdle = QString::fromLatin1(":icons/icon_idle.png");
static const QString IconPathRed = QString::fromLatin1(":icons/icon_red.png");
static const int BlinkInterval = 500; // ms

StatusIcon::StatusIcon()
    : QSystemTrayIcon()
    , m_idleIcon(IconPathIdle)
    , m_redIcon(IconPathRed)
{
    setIcon(m_idleIcon);

    m_blinkTimer.setSingleShot(false);
    m_blinkTimer.setInterval(BlinkInterval);
    connect(&m_blinkTimer, SIGNAL(timeout()), this, SLOT(onBlinkTimerTimeout()));

    show();
}

void
StatusIcon::setBlinking(bool blinking)
{
    if (blinking == m_blinkTimer.isActive()) {
        return;
    }

    if (blinking) {
        m_blinkTimer.start();
    } else {
        m_blinkTimer.stop();
        setIcon(m_idleIcon);
    }
}

void
StatusIcon::onBlinkTimerTimeout()
{
    static bool flip = false;

    setIcon(flip ? m_redIcon : m_idleIcon);
    flip = !flip;
}
