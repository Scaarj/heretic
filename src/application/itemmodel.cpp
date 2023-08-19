#include "itemmodel.h"

#include <iostream>

#include "doomdef.h"

ItemModel::ItemModel(const std::vector<Item>& items, QObject* parent) : QAbstractListModel(parent), allItems(items) {
}

int ItemModel::rowCount([[maybe_unused]] const QModelIndex& index) const {
	return items.size();
}

QVariant ItemModel::data(const QModelIndex& index, int role) const {
	if (index.row() < 0 || index.row() >= rowCount()) {
		return QVariant();
	}

	const auto& item = items.at(static_cast<size_t>(index.row()));

	switch (role) {
		case CodeRole: return item.code;
		case NameRole: return item.name;
		case ImageRole: return item.image;
		case QuantityRole: return item.quantity;
		case IndexRole: return index.row();
		default: return QVariant();
	}
}

bool ItemModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	auto result = false;

	if (index.row() < 0 || index.row() >= rowCount()) {
		return result;
	}

	auto& item = items.at(static_cast<size_t>(index.row()));

	switch (role) {
		case CodeRole: {
			auto newValue = value.toInt();
			if (item.code != newValue) {
				item.code = newValue;
				result = true;
			}
		} break;
		case NameRole: {
			auto newValue = value.toString();
			if (item.name != newValue) {
				item.name = value.toString();
				result = true;
			}
		} break;
		case ImageRole: {
			auto newValue = value.toString();
			if (item.image != newValue) {
				item.image = value.toString();
				result = true;
			}
		} break;
		case QuantityRole: {
			auto newValue = value.toInt();
			if (item.quantity != newValue) {
				item.quantity = value.toInt();
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

void ItemModel::addItem(int code) {
	auto item = std::find(allItems.cbegin(), allItems.cend(), Item(code));

	if (item != allItems.end()) {
		auto index = items.size();
		beginInsertRows(QModelIndex(), index, index);
		items.push_back(*item);
		endInsertRows();
		emit rowCountChanged();
	}
}

void ItemModel::removeItem(int code) {
	auto weapon = std::find(items.cbegin(), items.cend(), Item(code));

	if (weapon != items.end()) {
		auto index = items.size();
		beginRemoveRows(QModelIndex(), index, index);
		items.erase(std::remove(items.begin(), items.end(), *weapon), items.end());
		endRemoveRows();
		emit rowCountChanged();
	}
}

bool ItemModel::exist(int code) const {
	return std::find(items.begin(), items.end(), Item(code)) != items.cend();
}

Item ItemModel::selectedItem() const {
	return selItem;
}

void ItemModel::setSelectedItem(Item selItem) {
	if (this->selItem == selItem) {
		return;
	}
	this->selItem = selItem;
	emit selectedItemChanged();
}

void ItemModel::syncItemQuantity(int code, int ammo) {
	auto weapon = std::find(items.cbegin(), items.cend(), code);
	QModelIndex modelIndex = index(static_cast<int>(std::distance(items.cbegin(), weapon)));
	setData(modelIndex, ammo, QuantityRole);
}

QHash<int, QByteArray> ItemModel::roleNames() const {
	return {
		{CodeRole, "code"},
		{NameRole, "name"},
		{ImageRole, "image"},
		{QuantityRole, "quantity"},
	};
}
