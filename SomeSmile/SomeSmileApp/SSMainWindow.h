#ifndef MAINWIND_H
#define MAINWIND_H

#include <QtWidgets>
#include "SSSetKeyAndValue.h"

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    SetKeyAndValue* setKeyAndValue;

protected:
    QPushButton* createButton(const QString &NameOfButton, const bool &IsCheckable = false);
    void RestartHook(LPCWSTR LibraryName, HHOOK &hHook);

    virtual void hideEvent(QHideEvent *event);

protected slots:
    void slotButtonClicked();

public:
    MainWindow(QWidget* wgt = 0);

public slots:
    void HideAll();
    void RestartHooks();
    void slotStateChanged(bool);
};

#endif //MAINWIND_H
