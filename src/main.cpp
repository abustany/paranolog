#include "paranolog.h"

#include <QtCore>

int
main(int argc, char **argv)
{
    QApplication app(argc, argv);

    app.setOrganizationName(QString::fromLatin1("bustany.org"));
    app.setApplicationName(QString::fromLatin1("ParanoLog"));
    app.setQuitOnLastWindowClosed(false);

    Paranolog log;

    if (not log.run()) {
        return 1;
    }

    return app.exec();
}
