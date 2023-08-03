import QtQuick 2.6
import Sailfish.Silica 1.0

import "../../base" as Base

Base.Button {
    property bool checked: false

    source: "qrc:/resource/image/action_attack.svg"
    currentColor: checked ? contentColorPressed : contentColor
    size: Theme.buttonWidthTiny * 1.5

    onPressed: checked = true
    onReleased: checked = false
}
