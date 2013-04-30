#pragma once

#include <QtGui>

class NagWindow : public QWidget {
    Q_OBJECT
public:
    NagWindow(QWidget *parent = 0);

    void nag();

signals:
    void newData(const QDateTime &start, const QDateTime &end, const QString &what);

private:
    QString makeTitle() const;

private slots:
    void onGoAwayClicked();
    void onSaveClicked();

private:
    QDateTime m_lastNag;
    QLabel *m_titleLabel;
    QTextDocument *m_document;
};
