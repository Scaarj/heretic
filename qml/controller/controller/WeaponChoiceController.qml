import QtQuick 2.6

ChoiceItemController {
    id: root

    onItemSelect: screenController.selectWeapon(index)
    onVisibleChanged: screenController.pausePressed(true)
    onAnimationStopped: screenController.pausePressed(false)

    model: weaponModel
    itemsScale: 5
}
