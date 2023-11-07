#pragma once

#include <vector>

#include "../itemmodel.h"

namespace items {
namespace weapons {
	class WeaponModel : public ItemModel {
		Q_OBJECT

	public:
		WeaponModel(const std::vector<Item>& allWeapons, QObject* parent = nullptr);
		virtual void sync() override;
	};
} // namespace weapons
} // namespace items
