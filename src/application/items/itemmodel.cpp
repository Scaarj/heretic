#include "itemmodel.h"

using namespace items;

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
		case OwnedRole: return item.owned;
		case QuantityRole: return item.quantity;
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
				item.name = newValue;
				result = true;
			}
		} break;
		case ImageRole: {
			auto newValue = value.toString();
			if (item.image != newValue) {
				item.image = newValue;
				result = true;
			}
		} break;
		case OwnedRole: {
			auto newValue = value.toBool();
			if (item.owned != newValue) {
				item.owned = newValue;
				result = true;
			}
		} break;
		case QuantityRole: {
			auto newValue = value.toInt();
			if (item.quantity != newValue) {
				item.quantity = newValue;
				result = true;
			}
		} break;
		default: {
			result = false;
		}
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
	}
}

void ItemModel::removeItem(int code) {
	auto item = std::find(items.cbegin(), items.cend(), Item(code));

	if (item != items.end()) {
		auto index = items.size();
		beginRemoveRows(QModelIndex(), index, index);
		items.erase(std::remove(items.begin(), items.end(), *item), items.end());
		endRemoveRows();
	}
}

void ItemModel::syncItemQuantity(int type, int count) {
	auto item = std::find(items.cbegin(), items.cend(), type);
	QModelIndex modelIndex = index(static_cast<int>(std::distance(items.cbegin(), item)));
	if (setData(modelIndex, count, QuantityRole)) {
		emit dataChanged(modelIndex, modelIndex, {QuantityRole});
	}
}

void ItemModel::syncItemOwned(int type, bool owned) {
	auto item = std::find(items.cbegin(), items.cend(), type);
	QModelIndex modelIndex = index(static_cast<int>(std::distance(items.cbegin(), item)));
	if (setData(modelIndex, owned, OwnedRole)) {
		emit dataChanged(modelIndex, modelIndex, {OwnedRole});
	}
}

QHash<int, QByteArray> ItemModel::roleNames() const {
	return {
		{CodeRole, "code"},
		{NameRole, "name"},
		{ImageRole, "image"},
		{OwnedRole, "owned"},
		{QuantityRole, "quantity"},
	};
}

ItemProxyModel::ItemProxyModel(QObject* parent) : QSortFilterProxyModel(parent) {
	setDynamicSortFilter(true);
}

bool ItemProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const {
	QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
	return sourceModel()->data(index, ItemModel::OwnedRole).toBool();
}
