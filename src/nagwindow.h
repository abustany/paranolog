#pragma once

#include <QtGui>

class NagWindow : public QWidget {
    Q_OBJECT
public:
    NagWindow(QWidget *parent = 0);

    void nag();

signals:
    void newData(const QDateTime &start, const QDateTime &end, const QString &what);

    // Those signals are only used on OS X where the UI is slightly different
    void showLog();
    void showSettings();

private:
    QString makeTitle() const;

    void setupMacLayout(QBoxLayout *layout);

private slots:
    void onGoAwayClicked();
    void onSaveClicked();
    void onQuitClicked();

private:
    QDateTime m_lastNag;
    QLabel *m_titleLabel;
    QTextDocument *m_document;
};
