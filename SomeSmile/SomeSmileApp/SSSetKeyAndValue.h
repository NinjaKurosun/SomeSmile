#ifndef SSSETKEYANDVALUE_H
#define SSSETKEYANDVALUE_H

#include <QtWidgets>
#include <fstream>
#include <codecvt>
#include <string>
#include <Windows.h>

class SetKeyAndValue : public QDialog
{
    Q_OBJECT
private:
    QTableWidget* Table;

    std::map<std::wstring, std::wstring> setKeysAndValues;

protected:
    QPushButton* createButton(const QString &NameOfButton);
    virtual void hideEvent(QHideEvent* event);

protected slots:
    void ButtonClicked();

public:
    SetKeyAndValue(QWidget* wgt = 0);
    std::map<std::wstring, std::wstring> ReadAllOfItems();

public slots:
    void PushRow(QTableWidgetItem*);
    void ClearTable();
    void Update();
};

#endif // SSSETKEYANDVALUE_H
