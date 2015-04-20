
#include <QScopedPointer>

#include <sailfishapp.h>

#include "client.h"
#include "conversationmodel.h"
#include "rostermodel.h"
#include "contactsmodel.h"
#include "filemodel.h"

int main (int argc, char * argv []) {
    QScopedPointer<QGuiApplication> app (SailfishApp::application (argc, argv));
    QScopedPointer<QQuickView> view (SailfishApp::createView ());
    ConversationModel conversationModel;
    RosterModel rosterModel;
    ContactsModel contactsModel;
    FileModel fileModel;
    Client client (&rosterModel, &conversationModel, &contactsModel);
    view->rootContext ()->setContextProperty ("conversationModel", &conversationModel);
    view->rootContext ()->setContextProperty ("rosterModel",       &rosterModel);
    view->rootContext ()->setContextProperty ("contactsModel",     &contactsModel);
    view->rootContext ()->setContextProperty ("fileModel",         &fileModel);
    view->rootContext ()->setContextProperty ("Client",            &client);
    QDBusConnection system = QDBusConnection::systemBus ();
    if (!system.isConnected ()) {
        qFatal("Cannot connect to the D-Bus session bus.");
        return 1;
    }
    system.connect ("net.connman",
                    "/net/connman/technology/wifi",
                    "net.connman.Technology",
                    "PropertyChanged",
                    &client,
                    SLOT (connectivityChanged (QString, QDBusVariant)));
    system.connect ("net.connman",
                    "/net/connman/technology/cellular",
                    "net.connman.Technology",
                    "PropertyChanged",
                    &client,
                    SLOT (connectivityChanged (QString, QDBusVariant)));
    view->setSource (QUrl ("qrc:///qml/hang-me.qml"));
    view->showFullScreen ();
    app->exec ();
}

