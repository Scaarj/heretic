import QtQuick 2.6
import Sailfish.Silica 1.0

import "../../base" as Base

Base.Button {
    source: "qrc:/resource/image/action_attack.svg"
    currentColor: pressed ? contentColorPressed : contentColor
    size: Theme.buttonWidthTiny
}
