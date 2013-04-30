#pragma once

#include <QtCore>

class Settings : public QObject {
    Q_OBJECT
public:
    static Settings* get();

    unsigned int nagInterval() const;
    void setNagInterval(unsigned int ms);

signals:
    void changed();

private:
    Settings();

private:
    QScopedPointer<QSettings> m_settings;
};
