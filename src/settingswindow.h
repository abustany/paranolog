#pragma once

#include <QtGui>

class SettingsWindow : public QWidget {
    Q_OBJECT
public:
    SettingsWindow(QWidget *parent = 0);

protected:
    virtual void hideEvent(QHideEvent *event);

private slots:
    void update();

private:
    QSpinBox *m_nagIntervalSpinBox;
};
