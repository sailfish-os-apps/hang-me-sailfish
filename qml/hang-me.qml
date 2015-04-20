import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

ApplicationWindow
{
    initialPage: Component { FirstPage { } }

    cover: Qt.resolvedUrl("cover/CoverPage.qml")

    Conversation {
            id: conversation
        }

    Roster {
            id: roster
    }

    FullscreenImage {
            id: fsImage
    }

    ImagePicker {
            id: imagepicker
    }
}


