#include "SSSetKeyAndValue.h"
#include "SSSettings.h"

//////////////////////////////////////////////////////////////////////////////////////////

SetKeyAndValue::SetKeyAndValue(QWidget* wgt/*= 0*/) : QDialog(wgt)
{
//-----------------------------for translator---------------------------------------------
    tr("&Default");
    tr("&Cancel");
    tr("&OK");

    tr("Keys");
    tr("Values");

//----------------------------------------------------------------------------------------
    resize(SomeSmileSettings::size("SetKeyAndValue"));

    setWindowFlags(Qt::Window | Qt::WindowSystemMenuHint);

//--------------------------creates the buttons and so on...------------------------------
    QString NamesOfButtons[] = {"&Default", "addStretch", "&Cancel", "&OK"};

    QHBoxLayout* lowHLayout = new QHBoxLayout;
    for(auto name : NamesOfButtons)
        if(name == "addStretch")
            lowHLayout->addStretch(1);
        else
    lowHLayout->addWidget(createButton(name));


//---------------------creates the table and What? right, and so on...----------------------
    QStringList Headers;
    Headers << tr("Keys") << tr("Values");
    Table = new QTableWidget(1, 2, this);
    Table->setHorizontalHeaderLabels(Headers);
    Table->verticalHeader()->setVisible(false);
    Table->setFocusPolicy(Qt::NoFocus);
    Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QObject::connect(Table, SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(PushRow(QTableWidgetItem*)));

    std::wifstream TrFile("TranslationFile.ts");
    TrFile.imbue(std::locale(TrFile.getloc(), new std::codecvt_utf16<wchar_t, 1114111UL, std::little_endian>));

    std::map<std::wstring, std::wstring>::iterator itr;
    std::wstring Key;
    std::wstring Value;
    while(TrFile)
    {
        TrFile >> Key;
        TrFile >> Value;

        setKeysAndValues[Key] = Value;
    }
    Update();

//--------------------------------------Layout--------------------------------------------
    QVBoxLayout* VLayout = new QVBoxLayout(this);
    VLayout->addWidget(Table);
    VLayout->addLayout(lowHLayout);

    setLayout(VLayout);

}

/////////////////////////////////Protected////////////////////////////////////////////////
QPushButton* SetKeyAndValue::createButton(const QString &NameOfButton)
{
    QPushButton* Button = new QPushButton(tr(NameOfButton.toStdString().c_str()), this);
    Button->setCursor(Qt::PointingHandCursor);
    Button->setObjectName(NameOfButton);
    QObject::connect(Button, SIGNAL(clicked()), SLOT(ButtonClicked()));
    return Button;
}

/////////////////////////////////////////Public///////////////////////////////////////////
std::map<std::wstring, std::wstring> SetKeyAndValue::ReadAllOfItems()
{
    std::map<std::wstring, std::wstring> KeysAndValues;
    for(int i = 0; i < Table->rowCount() -1; i++)
    {
        if((Table->item(i,0)         != NULL && Table->item(i,1)         != NULL) &&
           (Table->item(i,0)->text() != NULL && Table->item(i,1)->text() != NULL))
            KeysAndValues[Table->item(i,0)->text().toStdWString()] = Table->item(i,1)->text().toStdWString();
    }
    return KeysAndValues;
}

/////////////////////////////////////////Public///////////////////////////////////////////
/////////////////////////////////////////Slots////////////////////////////////////////////
void SetKeyAndValue::PushRow(QTableWidgetItem* item)
{
    if(item->row() == Table->rowCount() - 1)
        Table->insertRow(Table->rowCount());
}

void SetKeyAndValue::ButtonClicked()
{
    QString str = ((QPushButton*)sender())->text();

    if(str == tr("&Default"))
    {
        ClearTable();
    }
    else if(str == tr("&Cancel"))
    {
        Update();
    }
    else if(str == tr("&OK"))
    {
        setKeysAndValues = ReadAllOfItems();
        Update();

        SomeSmileSettings::setSwitcher("TrFile", QDir::toNativeSeparators(QDir::currentPath()) + "\\TranslationFile.ts");

        std::wofstream TrFile("TranslationFile.ts");
        TrFile.imbue(std::locale(TrFile.getloc(), new std::codecvt_utf16<wchar_t, 1114111UL, std::little_endian>));

        std::map<std::wstring, std::wstring>::iterator itr;
        for(itr = setKeysAndValues.begin(); itr != setKeysAndValues.end(); ++itr)
            TrFile << itr->first << L" " << itr->second << L'\u000D';

        hide();
    }
}

void SetKeyAndValue::ClearTable()
{
    Table->setRowCount(1);
    Table->clearContents();
}

void SetKeyAndValue::Update()
{
    ClearTable();
    std::map<std::wstring, std::wstring>::iterator itr;
    int itrRow = 0;
    for(itr = setKeysAndValues.begin(); itr != setKeysAndValues.end(); ++itr, ++itrRow)
    {
        Table->setItem(itrRow, 0, new QTableWidgetItem(QString::fromStdWString(itr->first)));
        Table->setItem(itrRow, 1, new QTableWidgetItem(QString::fromStdWString(itr->second)));
    }
}

/////////////////////////////////Protected////////////////////////////////////////////////
//////////////////////////////////Events//////////////////////////////////////////////////
/*virtual*/ void SetKeyAndValue::hideEvent(QHideEvent* event)
{
    SomeSmileSettings::setPos("SetKeyAndValue", pos());
    SomeSmileSettings::setSize("SetKeyAndValue", size());
}
