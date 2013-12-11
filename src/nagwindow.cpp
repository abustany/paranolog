#include "nagwindow.h"
#include "utils.h"

NagWindow::NagWindow(QWidget *parent)
    : QWidget(parent)
    , m_lastNag(QDateTime::currentDateTime())
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    m_titleLabel = new QLabel(makeTitle());
    mainLayout->addWidget(m_titleLabel);

    QPlainTextEdit *answerEdit = new QPlainTextEdit;
    m_document = answerEdit->document();
    mainLayout->addWidget(answerEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    addButtonToLayout(buttonLayout, tr("Go away"), this, SLOT(onGoAwayClicked()));
    addButtonToLayout(buttonLayout, tr("Save"), this, SLOT(onSaveClicked()));

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

#ifdef Q_OS_MAC
    setupMacLayout(mainLayout);
#endif // Q_OS_MAC

    setWindowTitle(tr("ParanoLog report"));
}

void
NagWindow::nag()
{
    m_titleLabel->setText(makeTitle());
    m_document->clear();
    show();
    raise();
    activateWindow();
}

QString
NagWindow::makeTitle() const
{
    return tr("What have you done since %1?").arg(m_lastNag.toString());
}

void
NagWindow::setupMacLayout(QBoxLayout *mainLayout)
{
    mainLayout->addWidget(makeSeparator());

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    addButtonToLayout(buttonLayout, tr("Show log"), this, SIGNAL(showLog()));
    addButtonToLayout(buttonLayout, tr("Show settings"), this, SIGNAL(showSettings()));
    mainLayout->addLayout(buttonLayout);

    mainLayout->addWidget(makeSeparator());

    buttonLayout = new QHBoxLayout;
    addButtonToLayout(buttonLayout, tr("Quit"), this, SLOT(onQuitClicked()));
    mainLayout->addLayout(buttonLayout);
}

void
NagWindow::onGoAwayClicked()
{
    hide();
}

void
NagWindow::onSaveClicked()
{
    const QDateTime now = QDateTime::currentDateTime();
    emit newData(m_lastNag, now, m_document->toPlainText());
    m_lastNag = now;
    hide();
}

void
NagWindow::onQuitClicked()
{
    const QString appName = QApplication::applicationName();
    const QString msg = tr("Do you really want to quit %1?").arg(appName);

    if (QMessageBox::question(this, appName, msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes) {
        qApp->quit();
    }
}
