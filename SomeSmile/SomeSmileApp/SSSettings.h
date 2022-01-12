#ifndef SSSETTINGS_H
#define SSSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QStringList>
#include <QByteArray>

class SomeSmileSettings : public QObject
{
    static QSettings Settings;
    static int isCreated;
public:
    SomeSmileSettings();

    static void setLanguage(const QString &language = "");
    static QString language();
    static void setAutorun(const bool &state);

    static void setSize(const QString &objectName, const QSize &size);
    static QSize size(const QString &objectName);
    static void setPos(const QString &objectName, const QPoint &pos);
    static QPoint pos(const QString &objectName);

    static void setSwitcher(const QString &name,const QVariant &value);
    static QVariant Switcher(const QString &name);
};

#endif //SSSETTINGS_H
