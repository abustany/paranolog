#include "settings.h"

static const QString SettingsOrganization = QString::fromLatin1("bustany.org");
static const QString SettingsApp = QString::fromLatin1("paranolog");

static const QString SettingsKeyNagInterval = QString::fromLatin1("NagInterval");
static const int DefaultNagInterval = 30 * 60 * 1000;

Settings::Settings()
    : m_settings(new QSettings(SettingsOrganization, SettingsApp))
{
    qDebug() << "Loading settings from " << m_settings->fileName();
}

Settings*
Settings::get()
{
    static Settings instance;

    return &instance;
}

unsigned int
Settings::nagInterval() const
{
    return m_settings->value(SettingsKeyNagInterval, DefaultNagInterval).toInt();
}

void
Settings::setNagInterval(unsigned int ms)
{
    if (ms == nagInterval()) {
        return;
    }

    m_settings->setValue(SettingsKeyNagInterval, ms);

    emit changed();
}
