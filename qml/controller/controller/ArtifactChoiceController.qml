import QtQuick 2.6

ChoiceItemController {
    id: root

    onItemSelect: screenController.selectArtifact(index)
    onItemAction: screenController.useArtifact(index)
    onVisibleChanged: screenController.pausePressed(true)
    onAnimationStopped: screenController.pausePressed(false)

    model: artifactModel
    itemsScale: 6
}
