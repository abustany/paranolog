#include "utils.h"

QWidget*
makeSeparator()
{
    QFrame *separator = new QFrame;
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    return separator;
}

void
addButtonToLayout(QLayout *layout, const QString &label, QObject *receiver, const char *slot)
{
    QPushButton *button = new QPushButton(label);
    QObject::connect(button, SIGNAL(clicked()), receiver, slot);
    layout->addWidget(button);
}
