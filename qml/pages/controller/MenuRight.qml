import QtQuick 2.0
import QtQuick.Layouts 1.1
import Sailfish.Silica 1.0
import Painter.Global 1.0

ColumnLayout {
    id: root

    Button {
        text: "enter"
        Layout.fillWidth: true
        onPressed: screenController.enterPressed()
        onReleased: screenController.enterReleased()
    }

    Button {
        text: "escape"
        Layout.fillWidth: true
        onPressed: screenController.escapePressed()
        onReleased: screenController.escapeReleased()
    }
}
