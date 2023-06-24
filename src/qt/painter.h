#pragma once

#include <QQuickPaintedItem>
#include <memory>
#include <vector>

#include "context.h"
#include "doomdef.h"

class ScenePainter : public QQuickPaintedItem {
	Q_OBJECT
	Q_PROPERTY(float screen_ratio READ screenRatio NOTIFY screenRatioChanged)

	enum ContextType : int { IntroType = 0, GameType };

public:
	ScenePainter(QQuickPaintedItem* parent = nullptr);
	virtual ~ScenePainter() = default;

	void setPallete(byte* palette);
	float screenRatio() const;

	Q_INVOKABLE void orientationChanged(int orientation);

protected:
	void paint(QPainter* painter);

signals:
	void screenRatioChanged(float);

private:
	std::vector<std::unique_ptr<Context>> contexts;
	ContextType currentContext;
};
