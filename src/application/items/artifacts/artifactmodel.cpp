#include "artifactmodel.h"

#include "doomdef.h"

using namespace items::artifacts;

ArtifactModel::ArtifactModel(const std::vector<Item>& allArtifacts, QObject* parent) : ItemModel(allArtifacts, parent) {
	for (const auto& it : allArtifacts) {
		items.push_back(it);
	}
}

void ArtifactModel::sync() {
	const auto& inventory = players[0].inventory;
	const auto& slotsNum = players[0].inventorySlotNum;

	auto itemCount = [](Item item) -> int {
		for (int i = 0; i < slotsNum; ++i) {
			auto artifact = inventory[i];
			if (artifact.type == item.code) {
				return artifact.count;
			}
		}
		return 0;
	};

	for (const auto& it : items) {
		auto actualCount = itemCount(it);
		if ((actualCount != 0) ^ (it.quantity == 0)) {
			syncItemOwned(it.code, actualCount != 0);
		}

		if (actualCount != it.quantity) {
			syncItemQuantity(it.code, actualCount);
		}
	}
}
