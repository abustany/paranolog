#include "settingswindow.h"

#include "settings.h"
#include "utils.h"

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QFormLayout *formLayout = new QFormLayout;

    m_nagIntervalSpinBox = new QSpinBox;
    m_nagIntervalSpinBox->setMinimum(1);
    formLayout->addRow(tr("Nag interval (in min.)"), m_nagIntervalSpinBox);

    mainLayout->addLayout(formLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

#ifndef Q_OS_MAC // on mac people are used to just close setting windows
    addButtonToLayout(buttonLayout, tr("Close"), this, SLOT(hide()));
#endif

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(Settings::get(), SIGNAL(changed()), this, SLOT(update()));
    update();

    setWindowTitle(tr("ParanoLog settings"));
}

void
SettingsWindow::hideEvent(QHideEvent*)
{
    Settings *s = Settings::get();

    s->setNagInterval(1000 * 60 * m_nagIntervalSpinBox->value());
}

void
SettingsWindow::update()
{
    Settings *s = Settings::get();

    m_nagIntervalSpinBox->setValue(s->nagInterval() / 60 / 1000);
}
