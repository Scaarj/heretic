#include "weaponmodel.h"

#include "doomdef.h"

using namespace items::weapons;

WeaponModel::WeaponModel(const std::vector<Item>& allWeapons, QObject* parent) : ItemModel(allWeapons, parent) {
	for (const auto& it : allWeapons) {
		items.push_back(it);
	}
}

void WeaponModel::sync() {
	const auto& player = players[0];

	auto itemOwned = [](Item item) -> int {
		for (int i = 0; i <= wp_gauntlets; ++i) {
			if (item.code == i) {
				return player.weaponowned[i];
			}
		}
		return false;
	};

	for (const auto& it : items) {
		auto type = it.code;
		auto actualOwned = itemOwned(it);

		if (actualOwned != it.owned) {
			syncItemOwned(it.code, actualOwned);
		}

		if (type >= wp_goldwand && type <= wp_mace) {
			syncItemQuantity(type, player.ammo[type - 1]);
		}
	}
}
