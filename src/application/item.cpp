#include "item.h"

Item::Item(QObject* parent) : QObject(parent), code{-1}, name{""}, image{""} {
}

Item::Item(int code, QObject* parent) : QObject(parent), code{code}, name{""}, image{""} {
}

Item::Item(int code, QString name, QString image, bool owned, int quantity, QObject* parent)
	: QObject(parent)
	, code(code)
	, name(name)
	, image(image)
	, owned(owned)
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

bool Item::operator<(const Item& item) const {
	return code < item.code;
}

bool Item::operator!=(const Item& item) const {
	return !operator==(item);
}

bool Item::operator==(const Item& item) const {
	return code == item.code;
}

bool Item::operator!=(int code) const {
	return !operator==(code);
}

bool Item::operator==(int code) const {
	return this->code == code;
}
