#pragma once

#include <memory>

#include "../itemsproxy.h"
#include "weaponmodel.h"

namespace items {
namespace weapons {
	class WeaponProxy : public ItemsProxy {
	public:
		WeaponProxy();

		ItemProxyModel* model();

	private:
		virtual void syncModel() override;
		virtual void syncSelected() override;
		virtual void endless() override;

	private:
		static const std::vector<Item> allWeapons;

		std::unique_ptr<WeaponModel> weaponModel;
		std::unique_ptr<ItemProxyModel> weaponProxyModel;
	};
} // namespace weapons
} // namespace items
