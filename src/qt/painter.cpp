#include "painter.h"

#include "gamescreen.h"
#include "introscreen.h"

ScenePainter::ScenePainter(QQuickPaintedItem* parent) : QQuickPaintedItem(parent), currentContext{GameType} {
	contexts.emplace_back(std::make_unique<class IntroScreen>());
	contexts.emplace_back(std::make_unique<class GameScreen>());
}

void ScenePainter::setPallete(byte* palette) {
	Context::setPallete(palette);
}

void ScenePainter::paint(QPainter* painter) {
	return contexts.at(currentContext)->draw(painter);
}

float ScenePainter::screenRatio() const {
	return contexts.at(currentContext)->ratio();
}

void ScenePainter::orientationChanged(int orientation) {
	auto size = contexts.at(currentContext)->resize(orientation);
	setWidth(size.width());
	setHeight(size.height());
}
