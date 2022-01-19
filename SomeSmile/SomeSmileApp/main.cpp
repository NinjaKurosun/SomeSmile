#include <QtWidgets>
#include "SSMainWindow.h"
#include "SSSystemTray.h"
#include "SSSettings.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

//---------------------------to open in a single instance--------------------------------------
    QSystemSemaphore semaphore("<uniq id>", 1);
    semaphore.acquire();

#ifndef Q_OS_WIN32
    QSharedMemory nix_fix_shared_memory("<uniq id 2>");
    if(nix_fix_shared_memory.attach())
        nix_fix_shared_memory.detach();
#endif

    QSharedMemory sharedMemory("<uniq id 2>");
    bool isRunning = false;
    if (!sharedMemory.attach())
        sharedMemory.create(1);
    else
        isRunning = true;
    semaphore.release();

    if(isRunning)
        exit(1);

//---------------------------------------------------------------------------------------------
    QFile StyleFile(":/Resource/QStyle/GlobalStyle.qss");
    StyleFile.open(QFile::ReadOnly);
    QString StringOfCSS = QLatin1String(StyleFile.readAll());
    qApp->setStyleSheet(StringOfCSS);

    QTranslator translator;
    translator.load(":/Resource/Translations/Translations_" + SomeSmileSettings::language() + ".qm");
    qApp->installTranslator(&translator);

    if(translator.language() == QString("ar") ||
       translator.language() == QString("he"))
        qApp->setLayoutDirection(Qt::RightToLeft);

    QPalette newPal(qApp->palette());
    newPal.setColor(QPalette::Link, QColor("#3498db"));
    newPal.setColor(QPalette::LinkVisited, QColor("#3498db"));
    qApp->setPalette(newPal);

    SystemTray Stray;
    return app.exec();
}
