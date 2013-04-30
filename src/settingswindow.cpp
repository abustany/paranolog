#include "settingswindow.h"

#include "settings.h"

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(new QLabel(tr("Settings")));

    QFormLayout *formLayout = new QFormLayout;

    m_nagIntervalSpinBox = new QSpinBox;
    m_nagIntervalSpinBox->setMinimum(1);
    formLayout->addRow(tr("Nag interval (in min.)"), m_nagIntervalSpinBox);

    mainLayout->addLayout(formLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(hide()));
    buttonLayout->addWidget(closeButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(Settings::get(), SIGNAL(changed()), this, SLOT(update()));
    update();

    setWindowTitle(tr("ParanoLog settings"));
}

void
SettingsWindow::hide()
{
    Settings *s = Settings::get();

    s->setNagInterval(1000 * 60 * m_nagIntervalSpinBox->value());

    QWidget::hide();
}

void
SettingsWindow::update()
{
    Settings *s = Settings::get();

    m_nagIntervalSpinBox->setValue(s->nagInterval() / 60 / 1000);
}
