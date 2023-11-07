import QtQuick 2.6
import Sailfish.Silica 1.0

import "../../base" as Base

Base.Button {
    id: root

    property bool checked: false
    property color contentColorBase: contentColor

    source: "qrc:/resource/image/action_run.svg"
    currentColor: clickAnimation.running ? contentColorPressed : contentColorBase

    onClicked: {
        checked = !checked
        if (checked) {
            animation.start()
        } else {
            animation.stop()
        }
    }

    SequentialAnimation {
        id: animation

        PropertyAnimation {
            target: root
            property: "contentColorBase"
            to: contentColor
            duration: 1000
        }

        PropertyAnimation {
            target: root
            property: "contentColorBase"
            to: contentColorPressed
            duration: 1000
        }

        onStopped: {
            if (checked) {
                running = true
            } else {
                contentColorBase = contentColor
            }
        }
    }
}
