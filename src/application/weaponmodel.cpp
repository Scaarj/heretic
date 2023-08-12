#include "weaponmodel.h"

#include <iostream>
#include <iterator>

#include "doomdef.h"

WeaponModel::WeaponModel(QObject* parent) : QAbstractListModel(parent) {
}

// clang-format off
const std::vector<Weapon> WeaponModel::allWeapons = {
	{wp_staff, "staff", QString("qrc:/resource/image/weapons/WSTFA0.png")},
	{wp_gauntlets, "gauntles of necromancer", QString("qrc:/resource/image/weapons/WGNTA0.png")},
	{wp_goldwand, "elven wand", QString("qrc:/resource/image/weapons/WELVA0.png")},
	{wp_crossbow, "ethereal crossbow", QString("qrc:/resource/image/weapons/WBOWA0.png")},
	{wp_blaster, "dragon claw", QString("qrc:/resource/image/weapons/WBLSA0.png")},
	{wp_skullrod, "hellstaff", QString("qrc:/resource/image/weapons/WSKLA0.png")},
	{wp_phoenixrod, "phoenix rod", QString("qrc:/resource/image/weapons/WPHXA0.png")},
	{wp_mace, "firemace", QString("qrc:/resource/image/weapons/WMCEA0.png")}
};
// clang-format on

int WeaponModel::rowCount([[maybe_unused]] const QModelIndex& index) const {
	return weapons.size();
}

QVariant WeaponModel::data(const QModelIndex& index, int role) const {
	if (index.row() < 0 || index.row() >= rowCount()) {
		return QVariant();
	}

	const auto& weapon = weapons.at(static_cast<size_t>(index.row()));

	switch (role) {
		case CodeRole: return weapon.code;
		case NameRole: return weapon.name;
		case ImageRole: return weapon.image;
		case QuantityRole: return weapon.quantity;
		default: return QVariant();
	}
}

bool WeaponModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	auto result = false;

	if (index.row() < 0 || index.row() >= rowCount()) {
		return result;
	}

	auto& weapon = weapons.at(static_cast<size_t>(index.row()));

	switch (role) {
		case CodeRole: {
			auto newValue = value.toInt();
			if (weapon.code != newValue) {
				weapon.code = newValue;
				result = true;
			}
		} break;
		case NameRole: {
			auto newValue = value.toString();
			if (weapon.name != newValue) {
				weapon.name = value.toString();
				result = true;
			}
		} break;
		case ImageRole: {
			auto newValue = value.toString();
			if (weapon.image != newValue) {
				weapon.image = value.toString();
				result = true;
			}
		} break;
		case QuantityRole: {
			auto newValue = value.toInt();
			if (weapon.quantity != newValue) {
				weapon.quantity = value.toInt();
				result = true;
			}
		} break;
		default: return result;
	}

	if (result) {
		emit dataChanged(index, index, {role});
	}

	return result;
}

void WeaponModel::addWeapon(int code) {
	auto weapon = std::find(allWeapons.cbegin(), allWeapons.cend(), Weapon(code));

	if (weapon != allWeapons.end()) {
		auto index = weapons.size();
		beginInsertRows(QModelIndex(), index, index);
		weapons.push_back(*weapon);
		endInsertRows();
		emit rowCountChanged();
	}
}

void WeaponModel::removeWeapon(int code) {
	auto weapon = std::find(weapons.cbegin(), weapons.cend(), Weapon(code));

	if (weapon != weapons.end()) {
		auto index = weapons.size();
		beginRemoveRows(QModelIndex(), index, index);
		weapons.erase(std::remove(weapons.begin(), weapons.end(), *weapon), weapons.end());
		endRemoveRows();
		emit rowCountChanged();
	}
}

bool WeaponModel::weaponExist(int code) const {
	return std::find(weapons.begin(), weapons.end(), Weapon(code)) != weapons.cend();
}

void WeaponModel::actualizeWeapon() {
	auto& player = players[0];

#ifdef ENDLESS_WEAPON
	endlessweapon();
#endif

	for (int i = 0; i <= wp_gauntlets; ++i) {
		if (player.weaponowned[i]) {
			if (!weaponExist(i)) {
				addWeapon(i);
			}

			if (i >= wp_goldwand && i <= wp_mace) {
				actualizeAmmo(i, player.ammo[i - 1]);
			}
		} else if (!player.weaponowned[i] && weaponExist(i)) {
			removeWeapon(i);
		}
	}
}

QHash<int, QByteArray> WeaponModel::roleNames() const {
	return {
		{CodeRole, "code"},
		{NameRole, "name"},
		{ImageRole, "image"},
		{QuantityRole, "quantity"},
	};
}

void WeaponModel::actualizeAmmo(int code, int ammo) {
	auto weapon = std::find(weapons.cbegin(), weapons.cend(), code);
	QModelIndex modelIndex = index(static_cast<int>(std::distance(weapons.cbegin(), weapon)));
	setData(modelIndex, ammo, QuantityRole);
}

void WeaponModel::endlessweapon() {
	auto& player = players[0];

	player.weaponowned[0] = true;
	player.weaponowned[1] = true;
	player.weaponowned[2] = true;
	player.weaponowned[3] = true;
	player.weaponowned[4] = true;
	player.weaponowned[5] = true;
	player.weaponowned[6] = true;
	player.weaponowned[7] = true;

	player.ammo[0] = 100;
	player.ammo[1] = 50;
	player.ammo[2] = 200;
	player.ammo[3] = 200;
	player.ammo[4] = 20;
	player.ammo[5] = 150;
}
