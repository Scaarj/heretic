import QtQuick 2.6

MouseArea {
    id: root

    readonly property int widthSwipe: Math.min(root.width, root.height) / 10

    property int pressedX: 0
    property int pressedY: 0

    onPressed: {
        pressedX = mouseX
        pressedY = mouseY
        screenController.mousePressed(mouseX, mouseY)
    }
    onDoubleClicked: screenController.doubleClick(mouseX, mouseY)
    onPositionChanged: {
        if (mouseX - pressedX > widthSwipe)  {
            screenController.rightSwipe()
            pressedX = mouseX
            return
        }

        if (mouseX - pressedX < -widthSwipe)  {
            screenController.leftSwipe()
            pressedX = mouseX
            return
        }

        screenController.mousePressed(mouseX, mouseY)
    }
}
