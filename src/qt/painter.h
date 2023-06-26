#pragma once

#include <QQuickPaintedItem>
#include <memory>
#include <vector>

#include "context.h"
#include "doomdef.h"

class ScenePainter : public QQuickPaintedItem {
	Q_OBJECT
	Q_PROPERTY(float screen_ratio READ screenRatio NOTIFY screenRatioChanged)

public:
	enum ContextType : int { IntroType = 0, GameType };

public:
	ScenePainter(QQuickPaintedItem* parent = nullptr);
	virtual ~ScenePainter() = default;

	float screenRatio() const;
	void setPallete(byte* palette);
	void setContext(ContextType context);
	void printTextLine(const QString& line);

	Q_INVOKABLE void orientationChanged(int orientation);

protected:
	void paint(QPainter* painter);

signals:
	void screenRatioChanged(float);

private:
	std::vector<std::unique_ptr<Context>> contexts;
	ContextType currentContext;
};
