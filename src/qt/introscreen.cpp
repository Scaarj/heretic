#include "introscreen.h"

#include <QScreen>
#include <auroraapp.h>

IntroScreen::IntroScreen() {
}

void IntroScreen::draw(QPainter* painter) {
	auto screen = QGuiApplication::primaryScreen();
	auto isPortraitOrientation = screen->orientation() == Qt::ScreenOrientation::PortraitOrientation;
	auto screenWidth = isPortraitOrientation ? screen->size().width() : screen->size().height();
	auto screenHeight = isPortraitOrientation ? screen->size().height() : screen->size().width();

	painter->setPen(QPen(QColor(255, 255, 255), Qt::SolidPattern));
	painter->setFont(QFont(QFont().defaultFamily(), 20));

	painter->fillRect(QRectF(0, 0, screenWidth, screenHeight), QBrush(QColor(0, 0, 0)));
	drawText(painter, screenWidth, screenHeight);

	painter->save();
	painter->restore();
}

QSize IntroScreen::resize(int orientation) {
	QSize screenSize;

	if (orientation == 1) {
		screenSize = {
			QGuiApplication::primaryScreen()->size().width(), QGuiApplication::primaryScreen()->size().height()};
	} else {
		screenSize = {
			QGuiApplication::primaryScreen()->size().height(), QGuiApplication::primaryScreen()->size().width()};
	}

	return screenSize;
}

void IntroScreen::drawText(QPainter* painter, int screenWidth, int screenHeight) {
	auto stringHeight = painter->font().pointSize() * 2;
	auto textHeight = stringHeight * drawData.size();
	auto topBottom = (screenHeight - textHeight) / 2;

	for (int i = 0; i < drawData.size(); ++i) {
		auto text = drawData.at(i).toString();
		auto textRect = painter->boundingRect(
			QRect(0, topBottom + (i * stringHeight), screenWidth, stringHeight), Qt::AlignHCenter, text);
		painter->drawText(textRect.left(), textRect.bottom(), text);
	}
}
