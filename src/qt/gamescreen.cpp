#include "gamescreen.h"

#include <QScreen>
#include <auroraapp.h>

extern byte* screen;

GameScreen::GameScreen() {
}

void GameScreen::draw(QPainter* painter) {
	for (int i = 0; i < pixel_width; ++i) {
		for (int j = 0; j < pixel_height; ++j) {
			auto color = colors[screen[i * pixel_height + j]];
			// NOTE: user bit offset 2 for brightness
			buffer[i][j] = 0xFF000000 | (color.r << 18) | (color.g << 10) | (color.b << 2);
		}
	}
	QByteArray data = QByteArray::fromRawData(reinterpret_cast<const char*>(buffer), pixel_width * pixel_height);
	QImage image(reinterpret_cast<const uchar*>(data.constData()), pixel_width, pixel_height, QImage::Format_RGB32);
	QBrush brush(QColor(0, 0, 0));

	QRectF imageRect;
	QRectF backgroundRect;

	if (image_width == QGuiApplication::primaryScreen()->size().width()) {
		auto screenWidth = QGuiApplication::primaryScreen()->size().width();
		auto screenHeight = QGuiApplication::primaryScreen()->size().height();
		auto heightOffset = (screenHeight - image_height) / 2;

		imageRect = QRectF(0, heightOffset, image_width, image_height);
		backgroundRect = QRectF(0, 0, screenWidth, screenHeight);
	} else {
		auto screenWidth = QGuiApplication::primaryScreen()->size().height();
		auto screenHeight = QGuiApplication::primaryScreen()->size().width();
		auto widthOffset = (screenWidth - image_width) / 2;

		imageRect = QRectF(widthOffset, 0, image_width, image_height);
		backgroundRect = QRectF(0, 0, screenWidth, screenHeight);
	}

	painter->fillRect(backgroundRect, brush);
	painter->drawImage(imageRect, image);
	painter->save();
	painter->restore();
}

QSize GameScreen::resize(int orientation) {
	QSize screenSize;

	if (orientation == 1) {
		image_width = QGuiApplication::primaryScreen()->size().width();
		image_height = image_width / screen_ratio;
		screenSize = {
			QGuiApplication::primaryScreen()->size().width(), QGuiApplication::primaryScreen()->size().height()};
	} else {
		image_height = QGuiApplication::primaryScreen()->size().width();
		image_width = image_height * screen_ratio;
		screenSize = {
			QGuiApplication::primaryScreen()->size().height(), QGuiApplication::primaryScreen()->size().width()};
	}

	return screenSize;
}
