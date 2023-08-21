#pragma once

#include <QObject>
#include <QSGTransformNode>

struct Item : public QObject {
	Q_GADGET
	Q_PROPERTY(int code MEMBER code)
	Q_PROPERTY(QString name MEMBER name)
	Q_PROPERTY(QString image MEMBER image)
	Q_PROPERTY(bool owned MEMBER owned)
	Q_PROPERTY(int quantity MEMBER quantity)

public:
	explicit Item(QObject* parent = nullptr);
	explicit Item(int code, QObject* parent = nullptr);
	Item(int code, QString name, QString image, bool owned = false, int quantity = -1, QObject* parent = nullptr);
	Item(const Item&);
	Item& operator=(const Item&);

	bool operator<(const Item& item) const;
	bool operator!=(const Item& item) const;
	bool operator==(const Item& item) const;
	bool operator!=(int code) const;
	bool operator==(int code) const;

public:
	int code;
	QString name;
	QString image;
	bool owned = false;
	int quantity = -1;
};

Q_DECLARE_METATYPE(Item)
