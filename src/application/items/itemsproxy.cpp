#include "itemsproxy.h"

using namespace items;

ItemsProxy::ItemsProxy(QObject* parent) : QObject(parent) {
}

void ItemsProxy::sync() {
	syncModel();
	syncSelected();
#ifdef ENDLESS_WEAPON
	endless();
#endif
}

const Item& ItemsProxy::selectedItem() const {
	return m_selectedItem;
}

void ItemsProxy::setSelectedItem(const Item& newSelectedItem) {
	if (m_selectedItem == newSelectedItem)
		return;
	m_selectedItem = newSelectedItem;
	emit selectedItemChanged();
}
