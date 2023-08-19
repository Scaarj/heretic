#pragma once

#include <QObject>
#include <QSGTransformNode>

struct Item : public QObject {
	Q_GADGET
	Q_PROPERTY(int code MEMBER code)
	Q_PROPERTY(QString name MEMBER name)
	Q_PROPERTY(QString image MEMBER image)
	Q_PROPERTY(int quantity MEMBER quantity)
	//	Q_PROPERTY(int code READ getCode)
	//	Q_PROPERTY(QString name READ getName)
	//	Q_PROPERTY(QString image READ getImage)
	//	Q_PROPERTY(int quantity READ getQuantity)

public:
	explicit Item(QObject* parent = nullptr);
	Item(int code, QObject* parent = nullptr);
	Item(int code, QString name, QString image, int quantity = -1, QObject* parent = nullptr);
	Item(const Item&);
	Item& operator=(const Item&);

	bool operator!=(const Item& weapon) const;
	bool operator==(const Item& weapon) const;

	//	int getCode() const;
	//	const QString& getName() const;
	//	const QString& getImage() const;
	//	int getQuantity() const;

public:
	int code;
	QString name;
	QString image;
	int quantity = -1;
};

Q_DECLARE_METATYPE(Item)
