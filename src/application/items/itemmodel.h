#pragma once

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <vector>

#include "item.h"

namespace items {
class ItemProxyModel : public QSortFilterProxyModel {
	Q_OBJECT
public:
	explicit ItemProxyModel(QObject* parent = nullptr);

protected:
	bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
};

class ItemModel : public QAbstractListModel {
	Q_OBJECT

public:
	enum Roles { CodeRole = Qt::UserRole + 1, NameRole, ImageRole, OwnedRole, QuantityRole };

	ItemModel(const std::vector<Item>& items, QObject* parent = nullptr);

	virtual int rowCount(const QModelIndex& index = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	void addItem(int code);
	void removeItem(int code);
	void syncItemQuantity(int type, int count);
	void syncItemOwned(int type, bool owned);

protected:
	QHash<int, QByteArray> roleNames() const override;
	virtual void sync() = 0;

protected:
	const std::vector<Item>& allItems;
	std::vector<Item> items;
};
} // namespace items
