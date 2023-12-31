#pragma once

#include <QQuickPaintedItem>
#include <memory>
#include <vector>

#include "context.h"
#include "doomdef.h"

class ScenePainter : public QQuickPaintedItem {
	Q_OBJECT

public:
	enum ContextType : int { IntroType = 0, GameType };

	Q_PROPERTY(QRect activeScreen READ activeScreen NOTIFY activeScreenChanged)

public:
	ScenePainter(QQuickPaintedItem* parent = nullptr);
	virtual ~ScenePainter() = default;

	void setPallete(byte* palette);
	void setContext(ContextType context);
	void printTextLine(const QString& line);

	QRect activeScreen() const;
	QRect fromGameCoord(const QRect& rect, const QRect& base);

public slots:
	void orientationChanged(int orientation);

signals:
	void activeScreenChanged();

protected:
	void paint(QPainter* painter) override;

private:
	std::vector<std::unique_ptr<Context>> contexts;
	ContextType currentContext;
	QRect activeScreenRect;
};
