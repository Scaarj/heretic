import QtQuick 2.6
import Sailfish.Silica 1.0

import "../../base" as Base

Base.Button {
    property bool checked: false

    source: "qrc:/resource/image/switch-weapon.svg"
    currentColor: checked ? contentColorPressed : contentColor

    onPressed: checked = true
    onReleased: checked = false
}
