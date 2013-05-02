#include "paranolog.h"

#include <QtCore>

#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/signalfd.h>

static void
setupUnixSignalHandler()
{
    int sigFd;

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGTERM);
    sigaddset(&mask, SIGINT);

    if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1
    || (sigFd = signalfd(-1, &mask, 0)) == -1) {
        qWarning() << "Cannot setup UNIX signal handler: " << strerror(errno);
        return;
    }

    QSocketNotifier *notifier = new QSocketNotifier(sigFd, QSocketNotifier::Read, qApp);
    QObject::connect(notifier, SIGNAL(activated(int)), qApp, SLOT(quit()));
}

int
main(int argc, char **argv)
{
    QApplication app(argc, argv);

    setupUnixSignalHandler();

    app.setOrganizationName(QString::fromLatin1("bustany.org"));
    app.setApplicationName(QString::fromLatin1("ParanoLog"));
    app.setQuitOnLastWindowClosed(false);

    Paranolog log;

    if (not log.run()) {
        return 1;
    }

    const int ret = app.exec();

    qDebug() << "Exiting" << app.applicationName();

    return ret;
}
