#include "SSSettings.h"
#include <QLocale>
#include <QtWidgets>

SomeSmileSettings::SomeSmileSettings() : QObject()
{
    if(!isCreated)
        qDebug() << "setLanguage",
        ++isCreated,
        setLanguage();
}
int SomeSmileSettings::isCreated = 0;
QSettings SomeSmileSettings::Settings("MySchizophrenia", "SomeSmile");

///////////////////////////////////////////////////////////////////////////////
void SomeSmileSettings::setLanguage(const QString &language)
{
    Settings.setValue("Language", language);
}
QString SomeSmileSettings::language()
{
    QString Language;
    Language = Settings.value("Language").toString();

    if(Language == "")
        Language = QLocale::system().name();
    Language.resize(2);

    return Language;
}

///////////////////////////////////////////////////////////////////////////////
void SomeSmileSettings::setAutorun(const bool &state)
{
    QSettings autorun("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if(state)
        autorun.setValue(qApp->applicationName(), QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
    else autorun.remove(qApp->applicationName());
}

///////////////////////////////////////////////////////////////////////////////
void SomeSmileSettings::setSize(const QString &objectName, const QSize &size)
{
    Settings.setValue("/" + objectName + "/Size", size);
}
QSize SomeSmileSettings::size(const QString &objectName)
{
    return Settings.value("/" + objectName + "/Size").toSize();
}

///////////////////////////////////////////////////////////////////////////////
void SomeSmileSettings::setPos(const QString &objectName, const QPoint &size)
{
    Settings.setValue("/" + objectName + "/Pos", size);
}
QPoint SomeSmileSettings::pos(const QString &objectName)
{
    return Settings.value("/" + objectName + "/Pos").toPoint();
}

///////////////////////////////////////////////////////////////////////////////
void SomeSmileSettings::setSwitcher(const QString &name,const QVariant &value)
{
    Settings.setValue("/Switcher/" + name, value);
}
QVariant SomeSmileSettings::Switcher(const QString &name)
{
    return Settings.value("/Switcher/" + name);
}
