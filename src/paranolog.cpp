#include "paranolog.h"

#include <QMessageBox>

#include "settings.h"

Paranolog::Paranolog()
    : m_statusIcon(new StatusIcon)
    , m_db(new WorkDb)
    , m_nagWindow(new NagWindow)
{
    connect(m_statusIcon.data(), SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(onStatusIconActivated(QSystemTrayIcon::ActivationReason)));

    m_nagTimer.setSingleShot(false);
    m_nagTimer.setInterval(Settings::get()->nagInterval());
    connect(&m_nagTimer, SIGNAL(timeout()), this, SLOT(onNagTimerTimeout()));
    m_nagTimer.start();

    connect(m_nagWindow.data(), SIGNAL(newData(QDateTime, QDateTime, QString)),
            this, SLOT(onNewData(QDateTime, QDateTime, QString)));
}

bool
Paranolog::run()
{
    if (not m_db->open()) {
        QMessageBox::critical(0,
                              tr("Cannot open database"),
                              tr("The work database could not be open.\n\n"
                                 "The application will now exit."));
        return false;
    }

    return true;
}

void
Paranolog::onStatusIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason != QSystemTrayIcon::Trigger) {
        return;
    }

    m_statusIcon->setBlinking(false);
    m_nagWindow->nag();
}

void
Paranolog::onNagTimerTimeout()
{
    m_statusIcon->setBlinking(true);
}

void
Paranolog::onNewData(const QDateTime &start, const QDateTime &end, const QString &what)
{
    if (what.isEmpty()) {
        qDebug() << "Ignoring empty work report";
        return;
    }

    m_db->addItem(start, end, what);
}
