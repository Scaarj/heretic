import QtQuick 2.6
import Sailfish.Silica 1.0

Item {
    id: root

    property int touchId: -1
    property point baseCursorPosition: Qt.point(0, 0)
    property point cursorPosition: baseCursorPosition

    function setBaseTouchPoint(id, point)
    {
        touchId = id
        baseCursorPosition = point
    }

    function handleTouch(point) {
        cursorPosition = point
        screenController.mousePositionChanged(cursorPosition.x, cursorPosition.y)
    }

    function stopHandling()
    {
        cursorPosition = baseCursorPosition
        touchId = -1
    }
}
