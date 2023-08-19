import QtQuick 2.6

ChoiceItem {
    borderColor: "transparent"

    onAnimationComplete: startAnimation()
    Component.onCompleted: startAnimation()

    animationDuration: 2000
    imageGlow.color: "lightblue"
}
