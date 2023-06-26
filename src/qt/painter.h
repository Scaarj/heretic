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

public:
	ScenePainter(QQuickPaintedItem* parent = nullptr);
	virtual ~ScenePainter() = default;

	void setPallete(byte* palette);
	void setContext(ContextType context);
	void printTextLine(const QString& line);

	Q_INVOKABLE void orientationChanged(int orientation);

protected:
	void paint(QPainter* painter);

private:
	std::vector<std::unique_ptr<Context>> contexts;
	ContextType currentContext;
};
