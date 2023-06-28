#include "screencontroller.h"

#include "doomdef.h"

ScreenController::ScreenController(QQuickItem* parent) : QQuickItem(parent) {
	connect(this, &ScreenController::mousePressed, this, &ScreenController::onMousePressed);

	connect(this, &ScreenController::leftPressed, [&]() { D_PostEvent(event_t{ev_keydown, KEY_LEFTARROW, 0, 0}); });
	connect(this, &ScreenController::upPressed, [&]() { D_PostEvent(event_t{ev_keydown, KEY_UPARROW, 0, 0}); });
	connect(this, &ScreenController::rightPressed, [&]() { D_PostEvent(event_t{ev_keydown, KEY_RIGHTARROW, 0, 0}); });
	connect(this, &ScreenController::downPressed, [&]() { D_PostEvent(event_t{ev_keydown, KEY_DOWNARROW, 0, 0}); });
	connect(this, &ScreenController::enterPressed, [&]() { D_PostEvent(event_t{ev_keydown, KEY_ENTER, 0, 0}); });
	connect(this, &ScreenController::escapePressed, [&]() { D_PostEvent(event_t{ev_keydown, KEY_ESCAPE, 0, 0}); });

	connect(this, &ScreenController::leftReleased, [&]() { D_PostEvent(event_t{ev_keyup, KEY_LEFTARROW, 0, 0}); });
	connect(this, &ScreenController::upReleased, [&]() { D_PostEvent(event_t{ev_keyup, KEY_UPARROW, 0, 0}); });
	connect(this, &ScreenController::rightReleased, [&]() { D_PostEvent(event_t{ev_keyup, KEY_RIGHTARROW, 0, 0}); });
	connect(this, &ScreenController::downReleased, [&]() { D_PostEvent(event_t{ev_keyup, KEY_DOWNARROW, 0, 0}); });
	connect(this, &ScreenController::enterReleased, [&]() { D_PostEvent(event_t{ev_keyup, KEY_ENTER, 0, 0}); });
	connect(this, &ScreenController::escapeReleased, [&]() { D_PostEvent(event_t{ev_keyup, KEY_ESCAPE, 0, 0}); });
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
