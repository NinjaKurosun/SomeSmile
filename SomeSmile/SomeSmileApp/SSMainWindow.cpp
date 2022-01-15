#include "SSMainWindow.h"
#include <string>
#include "SSSettings.h"

//////////////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget* wgt /*= 0*/) : QWidget(wgt)
{
//-----------------------------for translator---------------------------------------------
    tr("&Quit");
    tr("&Set Keys-Values...");
    tr("&Apply");

    tr("Auto-&Translate");
    tr("Auto&run");

//----------------------------------------------------------------------------------------
    move(SomeSmileSettings::pos("MainWindow"));
    resize(SomeSmileSettings::size("MainWindow"));

    setWindowFlags(Qt::Window | Qt::WindowSystemMenuHint);

//--------------------------creates the buttons and so on...------------------------------
    QString NamesOfButtons[] = {"&Quit","&Set Keys-Values...","&Apply"};
    int stretch[]            = {   1   ,           2         ,    1   };

    QHBoxLayout* lowHLayout = new QHBoxLayout;
    for(auto Name : NamesOfButtons)
    {
        static int i = 0;
        lowHLayout->addWidget(createButton(Name), stretch[i++]);
    }

//--------------------------------------Layout--------------------------------------------
    QHBoxLayout* highHLayout = new QHBoxLayout;
    highHLayout->addWidget(createButton("Auto-&Translate", true));
    highHLayout->addWidget(createButton("Auto&run", true));


    QVBoxLayout* VLayout = new QVBoxLayout(this);
    VLayout->addLayout(highHLayout);
    VLayout->addLayout(lowHLayout);
    setLayout(VLayout);

//---------------------------------------Other--------------------------------------------
    setKeyAndValue = new SetKeyAndValue(this);
    RestartHooks();
}

/////////////////////////////////Protected////////////////////////////////////////////////
QPushButton* MainWindow::createButton(const QString &NameOfButton,const bool &IsCheckable/* = false*/)
{
    QPushButton* Button = new QPushButton(tr(NameOfButton.toStdString().c_str()), this);
    Button->setCursor(Qt::PointingHandCursor);
    Button->setObjectName(NameOfButton);
    Button->setCheckable(IsCheckable);

    if(IsCheckable)
        Button->setChecked(SomeSmileSettings::Switcher(NameOfButton).toBool()),
        QObject::connect(Button, SIGNAL(toggled(bool)), SLOT(slotStateChanged(bool)));
    else
        QObject::connect(Button, SIGNAL(clicked()), SLOT(slotButtonClicked()));

    return Button;
}

//////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::RestartHook(LPCWSTR LibraryName, HHOOK &hHook)
{
    UnhookWindowsHookEx(hHook);
    Sleep(1000);//don't delete this line
    //if you deleted the line, don't come to me with your problems

    HINSTANCE hLib = LoadLibrary(LibraryName);
    HOOKPROC hProc = (HOOKPROC)GetProcAddress(hLib, "KeyboardProc");
    hHook = SetWindowsHookEx(WH_KEYBOARD, hProc, hLib, NULL);
}


/////////////////////////////////////////Public///////////////////////////////////////////
/////////////////////////////////////////Slots////////////////////////////////////////////
void MainWindow::RestartHooks()
{
    static HHOOK hHook32 = 0;
    static HHOOK hHook64 = 0;
    RestartHook(L"Switcher32", hHook32);
    RestartHook(L"Switcher64", hHook64);
}

void MainWindow::HideAll()
{
    hide();
    setKeyAndValue->hide();
}

void MainWindow::slotButtonClicked()
{
    QString str = sender()->objectName();

    if(str == "&Quit")
    {
        HideAll();
        qApp->quit();
    }
    else if(str == "&Set Keys-Values...")
    {
        setKeyAndValue->show();
    }
    else if(str == "&Apply")
    {
        HideAll();
        RestartHooks();
    }
}

void MainWindow::slotStateChanged(bool State)
{
    QString str = sender()->objectName();
    SomeSmileSettings::setSwitcher(str, (uint32_t)State);

    if(str == "Auto&run")
        SomeSmileSettings::setAutorun(State);
}

/////////////////////////////////Protected////////////////////////////////////////////////
//////////////////////////////////Events//////////////////////////////////////////////////
/*virtual*/ void MainWindow::hideEvent(QHideEvent *event)
{
    SomeSmileSettings::setPos("MainWindow", pos());
    SomeSmileSettings::setSize("MainWindow", size());
}

//////////////////////////////////////////////////////////////////////////////////////////

