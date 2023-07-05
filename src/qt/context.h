#pragma once

#include <QPainter>
#include <QVariant>
#include <QVector>

#include "doomdef.h"

class Context {
public:
	static struct rgbTable {
		int r;
		int g;
		int b;
	} colors[256];

public:
	Context() = default;
	virtual ~Context() = default;

	virtual void draw(QPainter* painter) = 0;
	virtual QSize resize(int orientation) = 0;
	virtual QRect activeScreen() const = 0;

	static void setPallete(byte* palette);

	void addDrawData(const QVariant& drawData);
	void clearDrawData();

protected:
	QVector<QVariant> drawData;
};
