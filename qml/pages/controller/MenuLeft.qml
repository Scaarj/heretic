import QtQuick 2.0
import QtQuick.Layouts 1.1
import Sailfish.Silica 1.0

import "keys" as Keys

Item {
    id: root

    GridLayout {

        columns: 3
        rows: 3

        Keys.UpArrow {
            id: upArrow
            Layout.row: 0
            Layout.column: 1
            onPressed: screenController.upPressed()
            onReleased: screenController.upReleased()
        }

        Keys.LeftArrow {
            id: leftArrow
            Layout.row: 1
            Layout.column: 0
            onPressed: screenController.leftPressed()
            onReleased: screenController.leftReleased()
        }

        Keys.RightArrow {
            id: rightArrow
            Layout.row: 1
            Layout.column: 3
            onPressed: screenController.rightPressed()
            onReleased: screenController.rightReleased()
        }

        Keys.DownArrow {
            id: downArrow
            Layout.row: 2
            Layout.column: 1
            onPressed: screenController.downPressed()
            onReleased: screenController.leftReleased()
        }
    }
}
