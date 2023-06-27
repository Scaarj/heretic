#include "screencontroller.h"

#include <chrono>
#include <thread>

ScreenController::ScreenController(QQuickItem* parent) : QQuickItem(parent) {
	connect(this, &ScreenController::mousePressed, this, &ScreenController::onMousePressed);
}

void ScreenController::waitUntilTap() {
	tapLock = true;

	while (tapLock) {
		QGuiApplication::processEvents();
	}
}

void ScreenController::onMousePressed() {
	tapLock = false;
}
