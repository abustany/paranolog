#include "nagwindow.h"

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

    QPushButton *goAwayButton = new QPushButton(tr("Go away"));
    connect(goAwayButton, SIGNAL(clicked()), this, SLOT(onGoAwayClicked()));
    buttonLayout->addWidget(goAwayButton);

    QPushButton *saveButton = new QPushButton(tr("Save"));
    saveButton->setShortcut(QKeySequence::Save);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
    buttonLayout->addWidget(saveButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    setWindowTitle(tr("ParanoLog report"));
}

void
NagWindow::nag()
{
    m_titleLabel->setText(makeTitle());
    m_document->clear();
    show();
}

QString
NagWindow::makeTitle() const
{
    return tr("What have you done since %1?").arg(m_lastNag.toString());
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
