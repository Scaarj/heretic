#pragma once

#include <QObject>

#include "../item.h"

namespace items {
class ItemsProxy : public QObject {
	Q_OBJECT
	Q_PROPERTY(Item selectedItem READ selectedItem WRITE setSelectedItem NOTIFY selectedItemChanged)

public:
	ItemsProxy(QObject* parent = nullptr);

	void sync();

	const Item& selectedItem() const;
	void setSelectedItem(const Item& newSelectedItem);

protected:
	virtual void syncModel() = 0;
	virtual void syncSelected() = 0;
	virtual void endless() = 0;

signals:
	void selectedItemChanged();

private:
	Item m_selectedItem;
};
} // namespace items
