#include "SSMainWindow.h"
#include <QSystemTrayIcon>

class SystemTray : public MainWindow
{
    Q_OBJECT
private:
    QSystemTrayIcon* SysTrayIcon;
    QMenu*           trayIconMenu;

protected:
    QAction* createAction(const QString& NameOfAction);

protected slots:
    void ButtonClicked();

public:
    SystemTray(QWidget* wgt = 0);
};
