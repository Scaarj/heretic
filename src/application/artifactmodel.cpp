#include "artifactmodel.h"

#include <QQmlEngine>

#include "doomdef.h"

// clang-format off
const std::vector<Item> ArtifactModel::allArtifacts = {
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

ArtifactModel::ArtifactModel(QObject* parent) : ItemModel(allArtifacts, parent) {
}

void ArtifactModel::sync() {
	const auto& inventory = players[0].inventory;
	const auto& slotsNum = players[0].inventorySlotNum;

#ifdef ENDLESS_WEAPON
	endlessArtifacts();
#endif
	for (int i = 0; i < slotsNum; ++i) {
		auto artifact = inventory[i];
		auto artifcatCode = i + 1;
		if (artifact.count) {
			if (!exist(artifcatCode)) {
				addItem(artifcatCode);
			}

			if (artifcatCode > arti_none && artifcatCode < NUMARTIFACTS) {
				syncItemQuantity(artifcatCode, artifact.count);
			}
		} else if (!inventory[i].count && exist(artifcatCode)) {
			removeItem(artifcatCode);
		}
	}

	syncSelected();
}

void ArtifactModel::syncSelected() {
	auto readyArtifact = players[0].readyArtifact;
	if (readyArtifact > arti_none && readyArtifact < NUMARTIFACTS) {
		setSelectedItem(allArtifacts[readyArtifact]);
	}
}

void ArtifactModel::endlessArtifacts() {
	auto& inventory = players[0].inventory;
	auto& slotsNum = players[0].inventorySlotNum;
	slotsNum = NUMARTIFACTS - 1;

	for (int i = 0; i < slotsNum; ++i) {
		inventory[i].count = maxArtifactCount;
		inventory[i].type = i + 1;
	}
}
