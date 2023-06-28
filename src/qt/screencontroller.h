#pragma once

#include <QQuickItem>
#include <auroraapp.h>

#include "doomdef.h"

class ScreenController : public QQuickItem {
	Q_OBJECT

	event_t leftKeyPressed{ev_keydown, KEY_LEFTARROW, 0, 0};
	event_t upKeyPressed{ev_keydown, KEY_UPARROW, 0, 0};
	event_t rightKeyPressed{ev_keydown, KEY_RIGHTARROW, 0, 0};
	event_t downKeyPressed{ev_keydown, KEY_DOWNARROW, 0, 0};
	event_t enterKeyPressed{ev_keydown, KEY_ENTER, 0, 0};
	event_t escapeKeyPressed{ev_keydown, KEY_ESCAPE, 0, 0};

public:
	ScreenController(QQuickItem* parent = nullptr);

	void waitUntilTap();
	void onMousePressed();

signals:
	void mousePressed();

	void leftPressed();
	void upPressed();
	void rightPressed();
	void downPressed();
	void enterPressed();
	void escapePressed();

	void leftReleased();
	void upReleased();
	void rightReleased();
	void downReleased();
	void enterReleased();
	void escapeReleased();

private:
	QThread loopThread;
	std::atomic_bool tapLock;
};
