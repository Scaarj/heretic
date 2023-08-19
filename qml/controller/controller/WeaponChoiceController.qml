import QtQuick 2.6

ChoiceItemController {
    id: root

    onItemSelect: screenController.selectWeapon(index)

    model: weaponModel
    itemsScale: 5
}
