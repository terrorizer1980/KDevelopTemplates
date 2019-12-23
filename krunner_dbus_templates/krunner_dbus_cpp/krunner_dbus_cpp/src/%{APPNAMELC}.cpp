#include "%{APPNAMELC}.h"

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusArgument>
#include <QDBusMetaType>
#include <QDebug>
#include <iostream>

// Generated by qt5_add_dbus_adaptor command im CMakeLists.txt file
#include "krunner1adaptor.h"

%{APPNAME}::%{APPNAME}() {
    new Krunner1Adaptor(this);
    qDBusRegisterMetaType<RemoteMatch>();
    qDBusRegisterMetaType<RemoteMatches>();
    qDBusRegisterMetaType<RemoteAction>();
    qDBusRegisterMetaType<RemoteActions>();
    QDBusConnection::sessionBus().registerService(QStringLiteral("net.%{APPNAMELC}2"));
    QDBusConnection::sessionBus().registerObject(QStringLiteral("/%{APPNAMELC}"), this);
}

RemoteMatches %{APPNAME}::Match(const QString &searchTerm) {
    RemoteMatches ms;
    if (searchTerm.contains(QLatin1String("hello"))) {
        RemoteMatch m;
        m.id = QStringLiteral("id");
        m.text = QStringLiteral("Hello There!");
        m.iconName = QStringLiteral("planetkde");
        m.type = Plasma::QueryMatch::ExactMatch;
        m.relevance = 0.8;
        ms.append(m);
    }
    return ms;

}

RemoteActions %{APPNAME}::Actions() {
    RemoteAction action;
    action.id = QStringLiteral("action1");
    action.text = QStringLiteral("Action 1");
    action.iconName = QStringLiteral("document-browser");

    return RemoteActions({action});
}

void %{APPNAME}::Run(const QString &id, const QString &actionId) {
    std::cout << "Running:" << qPrintable(id) << ":" << qPrintable(actionId) << std::endl;
    std::cout.flush();
}

int main(int argc, char **argv) {
    qInfo() << *argv;
    QCoreApplication app(argc, argv);
    %{APPNAME} r;
    app.exec();
}

