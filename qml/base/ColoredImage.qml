import QtQuick 2.6
import QtGraphicalEffects 1.0

Item {
    id: root

    property alias color: overlay.color
    property alias source: image.source

    Image {
        id: image
        width:  parent.width
        height: parent.height
        smooth:  true
        visible: false
        sourceSize: Qt.size(width, height)
    }

    ColorOverlay {
        id: overlay
        anchors.fill: image
        source: image
    }
}
