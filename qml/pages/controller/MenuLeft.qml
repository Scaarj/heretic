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
            onPressedChanged: {
                if (pressed) {
                    screenController.upPressed()
                } else {
                    screenController.upReleased()
                }
            }

            onHoveredChanged:  {
                console.log("onHoveredChanged upArrow")
            }
        }

        Keys.LeftArrow {
            id: leftArrow
            Layout.row: 1
            Layout.column: 0
            onPressedChanged: {
                if (pressed) {
                    screenController.leftPressed()
                } else {
                    screenController.leftReleased()
                }
            }

            onHoveredChanged:  {
                console.log("onHoveredChanged leftArrow")
            }
        }

        Keys.RightArrow {
            id: rightArrow
            Layout.row: 1
            Layout.column: 3
            onPressedChanged: {
                if (pressed) {
                    screenController.rightPressed()
                } else {
                    screenController.rightReleased()
                }
            }

            onHoveredChanged:  {
                console.log("onHoveredChanged rightArrow")
            }
        }

        Keys.DownArrow {
            id: downArrow
            Layout.row: 2
            Layout.column: 1
            onPressedChanged: {
                if (pressed) {
                    screenController.downPressed()
                } else {
                    screenController.downReleased()
                }
            }

            onHoveredChanged:  {
                console.log("onHoveredChanged downArrow")
            }
        }
    }
}
