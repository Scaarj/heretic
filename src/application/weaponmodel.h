#pragma once

#include <QAbstractListModel>
#include <vector>

#include "itemmodel.h"

class WeaponModel : public ItemModel {
	Q_OBJECT

public:
	WeaponModel(QObject* parent = nullptr);

	virtual void sync() override;

private:
	virtual void syncSelected() override;
	void endlessweapon();

private:
	static const std::vector<Item> allWeapons;
};
