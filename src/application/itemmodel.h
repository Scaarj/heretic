#pragma once

#include <QAbstractListModel>
#include <vector>

#include "item.h"

class ItemModel : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
	Q_PROPERTY(Item selectedItem READ selectedItem WRITE setSelectedItem NOTIFY selectedItemChanged)

public:
	enum Roles { CodeRole = Qt::UserRole + 1, NameRole, ImageRole, QuantityRole, IndexRole };

	ItemModel(const std::vector<Item>& items, QObject* parent = nullptr);

	virtual int rowCount(const QModelIndex& index = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	void addItem(int code);
	void removeItem(int code);
	bool exist(int code) const;
	Item selectedItem() const;
	void setSelectedItem(Item selItem);
	void syncItemQuantity(int code, int ammo);

signals:
	void rowCountChanged();
	void selectedItemChanged();

protected:
	QHash<int, QByteArray> roleNames() const override;
	virtual void sync() = 0;
	virtual void syncSelected() = 0;

protected:
	const std::vector<Item>& allItems;
	std::vector<Item> items;
	Item selItem;
};
