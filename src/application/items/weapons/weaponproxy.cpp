#include "weaponproxy.h"

#include "doomdef.h"

using namespace items::weapons;

// clang-format off
const std::vector<Item> WeaponProxy::allWeapons = {
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

WeaponProxy::WeaponProxy() {
	weaponModel = std::make_unique<WeaponModel>(allWeapons);
	weaponProxyModel = std::make_unique<ItemProxyModel>();
	weaponProxyModel->setSourceModel(weaponModel.get());
}

items::ItemProxyModel* WeaponProxy::model() {
	return weaponProxyModel.get();
}

void WeaponProxy::syncModel() {
	weaponModel->sync();
}

void WeaponProxy::syncSelected() {
	auto readyweapon = players[0].readyweapon;
	if (readyweapon >= wp_goldwand && readyweapon <= wp_gauntlets) {
		setSelectedItem(allWeapons[readyweapon]);
	}
}

void WeaponProxy::endless() {
	auto& player = players[0];

	for (int i = wp_staff; i < NUMWEAPONS; ++i) {
		player.weaponowned[i] = true;
	}

	for (int i = am_goldwand; i < NUMAMMO; ++i) {
		player.ammo[i] = maxammo[i];
	}
}
