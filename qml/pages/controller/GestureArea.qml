import QtQuick 2.6
import Sailfish.Silica 1.0

import "keys" as Keys

MouseArea {
    id: root

    onPressed: screenController.mousePressed(mouseX, mouseY)
    onDoubleClicked: screenController.doubleClick(mouseX, mouseY)
    onPositionChanged: screenController.mousePositionChanged(mouseX, mouseY)

    Keys.MenuButton {
        anchors { left: parent.left; top: parent.top; leftMargin: Theme.paddingMedium; topMargin: anchors.leftMargin }
        visible: screenController.isGameState

        onClicked: screenController.menuPressed()
    }
}
