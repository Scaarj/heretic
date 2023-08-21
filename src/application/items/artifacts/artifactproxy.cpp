#include "artifactproxy.h"

#include "doomdef.h"

using namespace items::artifacts;

// clang-format off
const std::vector<Item> ArtifactProxy::allArtifacts = {
	{pw_None, "", QString("")},
	{arti_invulnerability, "Ring of Invincibility", QString("qrc:/resource/image/artifacts/ARTIINVU.png")},
	{arti_invisibility, "Shadowsphere", QString("qrc:/resource/image/artifacts/ARTIINVS.png")},
	{arti_health, "Quartz Flask", QString("qrc:/resource/image/artifacts/ARTIPTN2.png")},
	{arti_superhealth, "Mystic Urn", QString("qrc:/resource/image/artifacts/ARTISPHL.png")},
	{arti_tomeofpower, "Tome of Power", QString("qrc:/resource/image/artifacts/ARTIPWBK.png")},
	{arti_torch, "Torch", QString("qrc:/resource/image/artifacts/ARTITRCH.png")},
	{arti_firebomb, "Timebomb of the Ancients", QString("qrc:/resource/image/artifacts/ARTIFBMB.png")},
	{arti_egg, "Morph Ovum", QString("qrc:/resource/image/artifacts/ARTIEGGC.png")},
	{arti_fly, "Wings of Wrath", QString("qrc:/resource/image/artifacts/ARTISOAR.png")},
	{arti_teleport, "Chaos Device", QString("qrc:/resource/image/artifacts/ARTIATLP.png")}};
// clang-format on

items::ItemProxyModel* ArtifactProxy::model() {
	return artifactProxyModel.get();
}

void ArtifactProxy::syncModel() {
	artifactModel->sync();
}

ArtifactProxy::ArtifactProxy() {
	artifactModel = std::make_unique<ArtifactModel>(allArtifacts);
	artifactProxyModel = std::make_unique<ItemProxyModel>();
	artifactProxyModel->setSourceModel(artifactModel.get());
}

void ArtifactProxy::syncSelected() {
	auto readyArtifact = players[0].readyArtifact;
	if (readyArtifact > arti_none && readyArtifact < NUMARTIFACTS) {
		setSelectedItem(allArtifacts[readyArtifact]);
	}
}

void ArtifactProxy::endless() {
	auto& inventory = players[0].inventory;
	auto slotsNums = players[0].inventorySlotNum = NUMARTIFACTS - 1;

	for (int i = 0; i < slotsNums; ++i) {
		inventory[i].count = maxArtifactCount;
		inventory[i].type = i + 1;
	}
}
