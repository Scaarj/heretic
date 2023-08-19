#include "weaponmodel.h"

#include <iostream>
#include <iterator>

#include "doomdef.h"

// clang-format off
const std::vector<Item> WeaponModel::allWeapons = {
	{wp_staff, "staff", QString("qrc:/resource/image/weapons/WSTFA0.png")},
	{wp_goldwand, "elven wand", QString("qrc:/resource/image/weapons/WELVA0.png")},
	{wp_crossbow, "ethereal crossbow", QString("qrc:/resource/image/weapons/WBOWA0.png")},
	{wp_blaster, "dragon claw", QString("qrc:/resource/image/weapons/WBLSA0.png")},
	{wp_skullrod, "hellstaff", QString("qrc:/resource/image/weapons/WSKLA0.png")},
	{wp_phoenixrod, "phoenix rod", QString("qrc:/resource/image/weapons/WPHXA0.png")},
	{wp_mace, "firemace", QString("qrc:/resource/image/weapons/WMCEA0.png")},
	{wp_gauntlets, "gauntles of necromancer", QString("qrc:/resource/image/weapons/WGNTA0.png")}
};
// clang-format on

WeaponModel::WeaponModel(QObject* parent) : ItemModel(allWeapons, parent) {
}

void WeaponModel::sync() {
	auto& player = players[0];

#ifdef ENDLESS_WEAPON
	endlessweapon();
#endif

	for (int i = 0; i <= wp_gauntlets; ++i) {
		if (player.weaponowned[i]) {
			if (!exist(i)) {
				addItem(i);
			}

			if (i >= wp_goldwand && i <= wp_mace) {
				syncItemQuantity(i, player.ammo[i - 1]);
			}
		} else if (!player.weaponowned[i] && exist(i)) {
			removeItem(i);
		}
	}

	syncSelected();
}

void WeaponModel::endlessweapon() {
	auto& player = players[0];

	for (int i = wp_staff; i < NUMWEAPONS; ++i) {
		player.weaponowned[i] = true;
	}

	for (int i = am_goldwand; i < NUMAMMO; ++i) {
		player.ammo[i] = maxammo[i];
	}
}

void WeaponModel::syncSelected() {
	auto readyweapon = players[0].readyweapon;
	if (readyweapon >= wp_goldwand && readyweapon <= wp_gauntlets) {
		setSelectedItem(allWeapons[readyweapon]);
	}
}
