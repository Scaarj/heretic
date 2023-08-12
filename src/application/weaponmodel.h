#pragma once

#include <QAbstractListModel>
#include <QUrl>
#include <vector>

class Weapon {
public:
	Weapon() {
	}
	Weapon(int code) : code(code) {
	}

	Weapon(int code, QString name, QString image, int quantity = -1)
		: code(code)
		, name(name)
		, image(image)
		, quantity(quantity) {
	}

	bool operator!=(const Weapon& weapon) const {
		return code != weapon.code;
	}

	bool operator==(const Weapon& weapon) const {
		return code == weapon.code;
	}

	int code;
	QString name;
	QString image;
	int quantity = -1;
};

class WeaponModel : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)

public:
	enum Roles {
		CodeRole = Qt::UserRole + 1,
		NameRole,
		ImageRole,
		QuantityRole,
	};

	WeaponModel(QObject* parent = nullptr);

	virtual int rowCount(const QModelIndex& index = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	void addWeapon(int code);
	void removeWeapon(int code);
	bool weaponExist(int code) const;
	void actualizeWeapon();

signals:
	void rowCountChanged();

protected:
	QHash<int, QByteArray> roleNames() const override;

private:
	void actualizeAmmo(int code, int ammo);
	void endlessweapon();

private:
	static const std::vector<Weapon> allWeapons;
	std::vector<Weapon> weapons;
	int m_rowCount;
};
