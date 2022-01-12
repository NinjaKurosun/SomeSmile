#include "SSSystemTray.h"
#include <QString>
#include "SSSettings.h"

SystemTray::SystemTray(QWidget* wgt/*= 0*/) : MainWindow(wgt)
{
//-----------------------------for translator---------------------------------------------
    tr("Show/Hide");
    tr("About");
    tr("About Qt");
    tr("Quit");

//----------------------------------------------------------------------------------------
    SysTrayIcon = new QSystemTrayIcon(this);
    SysTrayIcon->setIcon(QPixmap(":/Resource/SomeSmileIcon.ico"));

    QString NamesOfActions[] = {"Show/Hide", "addSeparator", "About", "About Qt", "addSeparator", "Quit"};
    trayIconMenu = new QMenu(this);
    for(auto Name : NamesOfActions)
        if(Name == "addSeparator")
            trayIconMenu->addSeparator();
        else
            trayIconMenu->addAction(createAction(Name));

    QFile Style(":/Resource/QStyle/SystemTray/Menu.qss");
    Style.open(QFile::ReadOnly);
    trayIconMenu->setStyleSheet(Style.readAll());

    SysTrayIcon->setContextMenu(trayIconMenu);
//----------------------------------------------------------------------------------------

    SysTrayIcon->show();
    show();
}

QAction* SystemTray::createAction(const QString& NameOfAction)
{
    QLabel* text = new QLabel(tr(NameOfAction.toStdString().c_str()), this);
    text->setObjectName(NameOfAction);

    QFile Style(":/Resource/QStyle/SystemTray/Buttons.qss");
    Style.open(QFile::ReadOnly);
    text->setStyleSheet(Style.readAll());

    QWidgetAction* Action = new QWidgetAction(this);
    Action->setDefaultWidget(text);
    Action->setObjectName(NameOfAction);
    connect(Action, SIGNAL(triggered()), SLOT(ButtonClicked()));
    return Action;
}

void SystemTray::ButtonClicked()
{
    QString str = sender()->objectName();
    if(str == "Show/Hide")
    {
        (isVisible())? HideAll() : show();
    }
    else if (str == "About")
    {

        QFile AboutHTML(":/Resource/Translations/About/About_" + SomeSmileSettings::language() + ".html");
        if(!AboutHTML.exists())
            AboutHTML.setFileName(":/Resource/Translations/About/About_en.html");
        AboutHTML.open(QFile::ReadOnly);

        QMessageBox msg(this);
        msg.setIconPixmap(QPixmap(":/Resource/AboutIcon.png"));
        msg.setWindowTitle(tr("About %1").arg(qApp->applicationName()));
        msg.setText(tr(AboutHTML.readAll()).arg(qApp->applicationName(),
                                                qApp->applicationVersion()));
        msg.exec();
    }
    else if (str == "About Qt")
    {
        qApp->aboutQt();
    }
    else if(str == "Quit")
    {
        qApp->quit();
    }
}
