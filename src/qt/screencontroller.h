#pragma once

#include <QQuickItem>
#include <auroraapp.h>

#include "mn_menu.h"

class ScenePainter;

class ScreenController : public QQuickItem {
	Q_OBJECT

	event_t leftKeyPressed{ev_keydown, KEY_LEFTARROW, 0, 0};
	event_t upKeyPressed{ev_keydown, KEY_UPARROW, 0, 0};
	event_t rightKeyPressed{ev_keydown, KEY_RIGHTARROW, 0, 0};
	event_t downKeyPressed{ev_keydown, KEY_DOWNARROW, 0, 0};
	event_t enterKeyPressed{ev_keydown, KEY_ENTER, 0, 0};
	event_t escapeKeyPressed{ev_keydown, KEY_ESCAPE, 0, 0};

	struct MenuItems {
		int pos;
		QRect rect;
	};

public:
	ScreenController(ScenePainter* painter, QQuickItem* parent = nullptr);

	void waitUntilTap();

private slots:
	void onMousePressed(int x, int y);
	void onDoubleClick(int x, int y);
	void onActiveScreenRectChanged(const QRect& screen);
	void onLeftSwipe();
	void onRightSwipe();

signals:
	void mousePressed(int x, int y);
	void doubleClick(int x, int y);
	void leftSwipe();
	void rightSwipe();

private:
	QVector<MenuItems> menuItems() const;
	int itemWidth(int x, int y, const char* text) const;
	int clickOnMenuPosition(int x, int y);

private:
	std::atomic_bool tapLock;
	ScenePainter* scenePainter;
	QRect activeRect;
};
