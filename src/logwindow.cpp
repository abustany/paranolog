#include "logwindow.h"

static const QString DefaultStyleSheet = QString::fromLatin1(
    "h1 {\n"
    "  font-size: medium;\n"
    "  font-weight: bold;\n"
    "}\n"
    "body {\n"
    "  font-size: medium;\n"
    "}\n"
);

LogWindow::LogWindow(WorkDb *db, QWidget *parent)
    : QWidget(parent)
    , m_db(db)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QTextEdit *logEdit = new QTextEdit;
    logEdit->setReadOnly(true);
    m_document = logEdit->document();
    m_document->setDefaultStyleSheet(DefaultStyleSheet);
    mainLayout->addWidget(logEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(hide()));
    buttonLayout->addWidget(closeButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

static QString
formatItemTitle(const WorkItem &item)
{
    static const QString TitleTemplate = QString::fromLatin1("<h1>From %1 to %2</h1>");

    return TitleTemplate.arg(item.start.toString(), item.end.toString());
}

static QString
nl2br(const QString &in)
{
    static const QString lf = QString::fromLatin1("\n");
    static const QString br = QString::fromLatin1("<br/>");

    QString ret = in;

    return ret.replace(lf, br);
}

static QString
formatItemBody(const WorkItem &item)
{
    static const QString BodyTemplate = QString::fromLatin1("<blockquote>%1</blockquote>");

    return BodyTemplate.arg(nl2br(Qt::escape(item.what)));
}

static QString
formatItem(const WorkItem &item)
{
    return formatItemTitle(item) % formatItemBody(item);
}

bool
LogWindow::refresh()
{
    const QList<WorkItem> items = m_db->getItems();

    QString html;

    foreach(const WorkItem &item, items) {
        html += formatItem(item);
    }

    m_document->setHtml(html);

    return true;
}
