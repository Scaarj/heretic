import QtQuick 2.6
import QtQuick.Layouts 1.1
import Sailfish.Silica 1.0

Button {
    id: root

    readonly property int base: 90
    property int angle: 0

    Layout.preferredWidth: Theme.buttonWidthTiny
    Layout.preferredHeight: Layout.preferredWidth
    text: "<"

    transform: Rotation {
        angle: root.base + root.angle
        origin.x: root.width / 2
        origin.y: root.height / 2
    }
}
