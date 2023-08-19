#include "item.h"

Item::Item(QObject* parent) : QObject(parent), code{-1}, name{""}, image{""} {
}

Item::Item(int code, QObject* parent) : QObject(parent), code{code}, name{""}, image{""} {
}

Item::Item(int code, QString name, QString image, int quantity, QObject* parent)
	: QObject(parent)
	, code(code)
	, name(name)
	, image(image)
	, quantity(quantity) {
}

Item::Item(const Item& item) : code(item.code), name(item.name), image(item.image), quantity(item.quantity) {
}

Item& Item::operator=(const Item& item) {
	code = item.code;
	name = item.name;
	image = item.image;
	quantity = item.quantity;
	return *this;
}

bool Item::operator!=(const Item& weapon) const {
	return !operator==(weapon);
}

bool Item::operator==(const Item& weapon) const {
	return code == weapon.code;
}

//int Item::getCode() const {
//	return code;
//}

//const QString& Item::getName() const {
//	return name;
//}

//const QString& Item::getImage() const {
//	return image;
//}

//int Item::getQuantity() const {
//	return quantity;
//}
