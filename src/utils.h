#pragma once

#include <QtGui>

QWidget* makeSeparator();
void addButtonToLayout(QLayout *layout, const QString &label, QObject *receiver, const char *slot);
