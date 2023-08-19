#pragma once

#include <QQuickItem>

#include "mn_menu.h"

class ScenePainter;

class ScreenController : public QQuickItem {
	Q_OBJECT

	const event_t leftKeyPressed{ev_keydown, KEY_LEFTARROW, 0, 0};
	const event_t upKeyPressed{ev_keydown, KEY_UPARROW, 0, 0};
	const event_t rightKeyPressed{ev_keydown, KEY_RIGHTARROW, 0, 0};
	const event_t downKeyPressed{ev_keydown, KEY_DOWNARROW, 0, 0};
	const event_t leftKeyReleased{ev_keyup, KEY_LEFTARROW, 0, 0};
	const event_t upKeyReleased{ev_keyup, KEY_UPARROW, 0, 0};
	const event_t rightKeyReleased{ev_keyup, KEY_RIGHTARROW, 0, 0};
	const event_t downKeyReleased{ev_keyup, KEY_DOWNARROW, 0, 0};
	const event_t backspaceKeyPressed{ev_keydown, KEY_BACKSPACE, 0, 0};
	const event_t enterKeyPressed{ev_keydown, KEY_ENTER, 0, 0};
	const event_t enterKeyReleased{ev_keyup, KEY_ENTER, 0, 0};
	const event_t escapeKeyPressed{ev_keydown, KEY_ESCAPE, 0, 0};
	const event_t shiftKeyPressed{ev_keydown, KEY_RSHIFT, 0, 0};
	const event_t shiftKeyReleased{ev_keyup, KEY_RSHIFT, 0, 0};
	const event_t attackKeyPressed{ev_keydown, KEY_RCTRL, 0, 0};
	const event_t attackKeyReleased{ev_keyup, KEY_RCTRL, 0, 0};
	const event_t pauseKeyPressed{ev_keydown, KEY_PAUSE, 0, 0};
	const event_t pauseKeyReleased{ev_keyup, KEY_PAUSE, 0, 0};
	const event_t useKeyPressed{ev_keydown, ' ', 0, 0};
	const event_t useKeyReleased{ev_keyup, ' ', 0, 0};
	const event_t yKeyPressed{ev_keydown, 'y', 0, 0};
	const event_t yKeyReleased{ev_keyup, 'y', 0, 0};
	const event_t nKeyPressed{ev_keydown, 'n', 0, 0};
	const event_t nKeyReleased{ev_keyup, 'n', 0, 0};
	const event_t commaKeyPressed{ev_keydown, ',', 0, 0};
	const event_t commaKeyReleased{ev_keyup, ',', 0, 0};
	const event_t dotKeyPressed{ev_keydown, '.', 0, 0};
	const event_t dotKeyReleased{ev_keyup, '.', 0, 0};
	const event_t invLeftKeyPressed{ev_keydown, 'k', 0, 0};
	const event_t invLeftKeyReleased{ev_keyup, 'k', 0, 0};
	const event_t invRightKeyPressed{ev_keydown, 'l', 0, 0};
	const event_t invRightKeyReleased{ev_keyup, 'l', 0, 0};

	struct MenuItems {
		int pos;
		QRect rect;
	};

	QRect baseScreen{0, 0, 320, 200};

	Q_PROPERTY(bool gameStateActive READ gameStateActive NOTIFY gameStateActiveChanged)

public:
	ScreenController(ScenePainter* painter, QQuickItem* parent = nullptr);
	virtual ~ScreenController() = default;

	void waitUntilTap();
	void initYesNoButton();

	void checkGameState();

public slots:
	void mousePressed(int mouseX, int mouseY);
	void mousePositionChanged(int mouseX, int mouseY);
	void doubleClick(int x, int y);
	void menuPressed();
	bool gameStateActive();
	void forwardPressed(bool pressed);
	void backPressed(bool pressed);
	void leftStrafePressed(bool pressed);
	void rightStrafePressed(bool pressed);
	void shiftPressed(bool pressed);
	void attackPressed(bool pressed);
	void usePressed(bool pressed);
	void selectWeapon(int index);
	void pausePressed(bool pressed);
	void mouseMoved(int offsetX, int offsetY);
	void useArtifact();
	void nextWeapon();
	void selectArtifact(int index);
	void inventoryLeftPressed(bool pressed);
	void inventoryRightPressed(bool pressed);

signals:
	void gameStateActiveChanged();

private slots:
	void onActiveScreenChanged();

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
	void leftSwipe();
	void rightSwipe();

private:
	int swipeWidth;
	bool tapLock;
	ScenePainter* scenePainter;
	QPoint mouseLastPosition;
	QRect activeRect;
	QRect yesButton;
	QRect noButton;
	bool gameState;
};
