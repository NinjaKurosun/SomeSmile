TEMPLATE = app
QT += widgets
RC_ICONS = Resource/SomeSmileIcon.ico
VERSION = 1.7.0.0

CONFIG += c++17

# SS = SomeSmile
SOURCES = main.cpp \
    SSMainWindow.cpp \
    SSSetKeyAndValue.cpp \
    SSSystemTray.cpp \
    SSSettings.cpp

HEADERS = \
    SSMainWindow.h \
    SSSetKeyAndValue.h \
    SSSystemTray.h \
    SSSettings.h

RESOURCES = Resource.qrc

TRANSLATIONS = \
Resource/Translations/Translations_ru.ts
