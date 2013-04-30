#pragma once

#include <QtCore>

class Settings {
public:
    static Settings* get();

    unsigned long nagInterval() const;

private:
    Settings();

private:
    QScopedPointer<QSettings> m_settings;
};
