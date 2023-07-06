#include "scenepainter.h"

#include "gamescreen.h"
#include "introscreen.h"

ScenePainter::ScenePainter(QQuickPaintedItem* parent) : QQuickPaintedItem(parent), currentContext{GameType} {
	contexts.emplace_back(std::make_unique<class IntroScreen>());
	contexts.emplace_back(std::make_unique<class GameScreen>());
}

void ScenePainter::setPallete(byte* palette) {
	Context::setPallete(palette);
}

void ScenePainter::setContext(ContextType context) {
	currentContext = context;
	update();
	emit activeScreenRectChanged(activeScreen());
}

void ScenePainter::printTextLine(const QString& line) {
	contexts.at(currentContext)->addDrawData(line);
}

QRect ScenePainter::activeScreen() const {
	return contexts.at(currentContext)->activeScreen();
}

QRect ScenePainter::fromGameCoord(const QRect& rect, const QRect& base) {
	// TODO: look orientation and side of scaling
	float ratio = std::min(width() / base.width(), height() / base.height());
	auto screen = activeScreen();
	return QRect(
		rect.x() * ratio + screen.x(), rect.y() * ratio + screen.y(), rect.width() * ratio, rect.height() * ratio);
}

void ScenePainter::paint(QPainter* painter) {
	return contexts.at(currentContext)->draw(painter);
}

void ScenePainter::orientationChanged(int orientation) {
	if (currentContext == IntroType) {
		contexts.at(GameType)->resize(orientation);
	} else if (currentContext == IntroType) {
		contexts.at(IntroType)->resize(orientation);
	}
	auto size = contexts.at(currentContext)->resize(orientation);
	setWidth(size.width());
	setHeight(size.height());
	emit activeScreenRectChanged(activeScreen());
}
