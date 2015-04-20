import QtQuick 2.0
import Sailfish.Silica 1.0
import "../delegates"

Page {
    id: page;
    objectName: "roster";
    onStatusChanged: {
        console.log(page.status)
        if (page.status==2) {
            Client.setFocus(conversationModel.cid, 2)
            console.log("Resetting conv")
            conversationModel.cid = ""
        }
    }

    SilicaListView {
        id: listView;
        model: rosterModel;
        anchors.fill: parent;
        header: PageHeader {
            title: qsTr ("Conversations");
        }
        delegate: BackgroundItem {
            id: delegate;
            height: img.height;
            anchors {
                left: parent.left;
                right: parent.right;
            }
            onClicked: {
                //var convPage = Qt.createComponent("Conversation.qml");
                console.log("Clicked " + id)
                conversation.loadConversationModel(id);
                rosterModel.readConv = id;
                conversation.conversationName = name;
                pageStack.push (conversation);
            }

            Image {
                id: img;
                source: model.imagePath;
                width: Theme.iconSizeLarge;
                height: width;
                asynchronous: true;
                anchors {
                    left: parent.left;
                    verticalCenter: parent.verticalCenter;
                }
            }
            Label {
                text: (model.unread ? model.name + " " + model.unread : model.name);
                color: (delegate.highlighted ? Theme.highlightColor : Theme.primaryColor);
                elide: Text.ElideRight;
                font.bold: model.unread;
                anchors {
                    left: img.right;
                    right: bubble.left;
                    margins: Theme.paddingMedium;
                    verticalCenter: parent.verticalCenter;
                }
            }
            Rectangle {
                id: bubble;
                color: Qt.rgba (1,1,1,0.15);
                width: Theme.itemSizeExtraSmall;
                height: width;
                radius: (width / 2);
                visible: model.unread;
                antialiasing: true;
                border {
                    width: 1;
                    color: Theme.highlightColor;
                }
                anchors {
                    right: parent.right;
                    margins: Theme.paddingMedium;
                    verticalCenter: parent.verticalCenter;
                }

                Label {
                    text: model.unread;
                    color: Theme.primaryColor;
                    anchors.centerIn: parent;
                }
            }
        }
        VerticalScrollDecorator { }
    }
    Connections {
        target: rosterModel;
        onDataChanged: {
            //console.log("Changing data")
        }
    }
    Connections {
        target: Qt.application;
        onActiveChanged: {
            if(!Qt.application.active) {
                // Pauze the game here
                console.log("app paused")
                if (conversationModel.cid != "")
                    Client.setFocus(conversationModel.cid, 2)
                Client.setAppPaused()
            }
            else {
                console.log("app opened")
                if (conversationModel.cid != "")
                    Client.setFocus(conversationModel.cid, 1)
                Client.setAppOpened()
            }
        }
    }
}
