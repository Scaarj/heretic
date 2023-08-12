#include "gamescreen.h"

#include <QGuiApplication>
#include <QScreen>
#ifdef sailfishapp
	#include <sailfishapp.h>
#else
	#include <auroraapp.h>
#endif

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

	auto screen = screenRect();

	QRectF imageRect = QRectF(screen.x(), screen.y(), image_width, image_height);
	QRectF backgroundRect = QRectF(0, 0, screen.width(), screen.height());

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

QRect GameScreen::activeScreen() const {
	auto screen = screenRect();
	return QRect(screen.x(), screen.y(), image_width, image_height);
}

QRect GameScreen::screenRect() const {
	auto screenWidth{0};
	auto screenHeight{0};
	auto heightOffset{0};
	auto widthOffset{0};

	if (image_width == QGuiApplication::primaryScreen()->size().width()) {
		screenWidth = QGuiApplication::primaryScreen()->size().width();
		screenHeight = QGuiApplication::primaryScreen()->size().height();
		heightOffset = (screenHeight - image_height) / 2;
	} else {
		screenWidth = QGuiApplication::primaryScreen()->size().height();
		screenHeight = QGuiApplication::primaryScreen()->size().width();
		widthOffset = (screenWidth - image_width) / 2;
	}

	return QRect(widthOffset, heightOffset, screenWidth, screenHeight);
}
