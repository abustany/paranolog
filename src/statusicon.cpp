#include "statusicon.h"

static const QString IconPathIdle = QString::fromLatin1(":icons/icon_idle.png");
static const QString IconPathRed = QString::fromLatin1(":icons/icon_red.png");
static const int BlinkInterval = 500; // ms

StatusIcon::StatusIcon()
    : QSystemTrayIcon()
    , m_idleIcon(IconPathIdle)
    , m_redIcon(IconPathRed)
    , m_contextMenu(new QMenu)
{
    setIcon(m_idleIcon);

    m_blinkTimer.setSingleShot(false);
    m_blinkTimer.setInterval(BlinkInterval);
    connect(&m_blinkTimer, SIGNAL(timeout()), this, SLOT(onBlinkTimerTimeout()));

    m_contextMenu->setTitle(QCoreApplication::applicationName());

    m_contextMenu->addAction(tr("Show log"), this, SIGNAL(showLog()));
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(tr("Show settings"), this, SIGNAL(showSettings()));
    m_contextMenu->addAction(tr("Quit"), this, SIGNAL(quit()));

    // On OS X, we don't want a context menu since the top menu bar icons behave
    // as menus and we want to use the clic events for showing the nag window
#ifndef Q_OS_MAC
    setContextMenu(m_contextMenu.data());
#endif // Q_OS_MAC

    setToolTip(QCoreApplication::applicationName());

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
