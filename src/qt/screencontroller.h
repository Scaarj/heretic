#pragma once

#include <QQuickItem>
#ifdef sailfishapp
	#include <sailfishapp.h>
#elif auroraapp
	#include <auroraapp.h>
#endif

#include "mn_menu.h"

class ScenePainter;

class ScreenController : public QQuickItem {
	Q_OBJECT

	event_t leftKeyPressed{ev_keydown, KEY_LEFTARROW, 0, 0};
	event_t upKeyPressed{ev_keydown, KEY_UPARROW, 0, 0};
	event_t rightKeyPressed{ev_keydown, KEY_RIGHTARROW, 0, 0};
	event_t downKeyPressed{ev_keydown, KEY_DOWNARROW, 0, 0};
	event_t leftKeyReleased{ev_keyup, KEY_LEFTARROW, 0, 0};
	event_t upKeyReleased{ev_keyup, KEY_UPARROW, 0, 0};
	event_t rightKeyReleased{ev_keyup, KEY_RIGHTARROW, 0, 0};
	event_t downKeyReleased{ev_keyup, KEY_DOWNARROW, 0, 0};
	event_t backspaceKeyPressed{ev_keydown, KEY_BACKSPACE, 0, 0};
	event_t enterKeyPressed{ev_keydown, KEY_ENTER, 0, 0};
	event_t escapeKeyPressed{ev_keydown, KEY_ESCAPE, 0, 0};
	event_t yKeyPressed{ev_keydown, 'y', 0, 0};
	event_t nKeyPressed{ev_keydown, 'n', 0, 0};

	struct MenuItems {
		int pos;
		QRect rect;
	};

	QRect baseScreen{0, 0, 320, 200};

	Q_PROPERTY(bool isGameState READ isGameState NOTIFY isGameStateChanged)

public:
	ScreenController(ScenePainter* painter, QQuickItem* parent = nullptr);

	void waitUntilTap();
	void init();

	void checkGameState(gamestate_t state);

public slots:
	void mousePressed(int mouseX, int mouseY);
	void mousePositionChanged(int mouseX, int mouseY);
	void doubleClick(int x, int y);
	void menuPressed();
	bool isGameState();
	void forwardPressed(bool pressed);
	void backPressed(bool pressed);
	void leftPressed(bool pressed);
	void rightPressed(bool pressed);

signals:
	void isGameStateChanged();

private slots:
	void onActiveScreenRectChanged(const QRect& screen);

private:
	bool yesButtonPressed(int x, int y);
	bool noButtonPressed(int x, int y);
	int itemWidth(int x, const char* text) const;
	int clickOnMenuPosition(int x, int y);

	QVector<MenuItems> menuItems() const;
	void menuMissClicked();
	void menuItemClicked();
	void checkNoneGameMenuInteraction(int x, int y);
	void checkMenuInteraction(int x, int y);
	void safeLastMousePosition(int mouseX, int mouseY);
	void mouseMoved(int offsetX, int offsetY);
	void leftSwipe();
	void rightSwipe();

private:
	int swipeWidth;
	std::atomic_bool tapLock;
	ScenePainter* scenePainter;
	QPoint mouseLastPosition;
	QRect activeRect;
	QRect yesButton;
	QRect noButton;
	bool m_isGameState;
};
