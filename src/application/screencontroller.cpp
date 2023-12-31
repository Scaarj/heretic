#include "screencontroller.h"

#include <QGuiApplication>
#include <QTimer>
#include <math.h>

#include "doomdef.h"
#include "gamescreen.h"
#include "mn_menu.h"
#include "p_local.h"
#include "scenepainter.h"

extern Menu_t* CurrentMenu;
extern boolean MenuActive;
extern int FontBBaseLump;
extern int CurrentItPos;
extern boolean askforquit;
extern int curpos;
extern int inv_ptr;
extern bool inventory;
extern boolean gamekeydown[NUMKEYS];
extern boolean FileMenuKeySteal;

extern long key_right, key_left, key_up, key_down;
extern long key_strafeleft, key_straferight;
extern long key_fire, key_use, key_strafe, key_speed;
extern long key_flyup, key_flydown, key_flycenter;
extern long key_lookup, key_lookdown, key_lookcenter;
extern long key_invleft, key_invright, key_useartifact;

extern QGuiApplication* application;

ScreenController::ScreenController(ScenePainter* painter, QQuickItem* parent)
	: QQuickItem{parent}
	, scenePainter{painter}
	, gameState{false} {
	connect(scenePainter, &ScenePainter::activeScreenChanged, this, &ScreenController::onActiveScreenChanged);
	memset(pressed, 0, sizeof(pressed));
}

void ScreenController::waitUntilTap() {
	tapLock = true;

	while (tapLock) {
		application->processEvents();
	}
}

void ScreenController::initYesNoButton() {
	YesButtonX = 100 - MN_TextAWidth(QuitEndMsgAnswer[0]) / 2;
	NoButtonX = 200 - MN_TextAWidth(QuitEndMsgAnswer[1]) / 2;
	ConfirmationButtonY = Y_DISP + 100;

	yesButton = QRect(YesButtonX, ConfirmationButtonY, itemWidth(YesButtonX, QuitEndMsgAnswer[0]), ITEM_HEIGHT);
	noButton = QRect(NoButtonX, ConfirmationButtonY, itemWidth(NoButtonX, QuitEndMsgAnswer[1]), ITEM_HEIGHT);
}

void ScreenController::checkGameState() {
	auto currentState = GS_LEVEL == gamestate && !demoplayback && !MenuActive && !askforquit;

	if (currentState != gameState) {
		gameState = currentState;
		emit gameStateActiveChanged();
	}
}

bool ScreenController::gameStateActive() {
	return gameState;
}

void ScreenController::forwardPressed(bool pressed) {
	if (pressed) {
		D_PostEvent(upKeyPressed);
	} else {
		D_PostEvent(upKeyReleased);
	}
}

void ScreenController::backPressed(bool pressed) {
	if (pressed) {
		D_PostEvent(downKeyPressed);
	} else {
		D_PostEvent(downKeyReleased);
	}
}

void ScreenController::leftStrafePressed(bool pressed) {
	if (pressed) {
		D_PostEvent(commaKeyPressed);
	} else {
		D_PostEvent(commaKeyReleased);
	}
}

void ScreenController::rightStrafePressed(bool pressed) {
	if (pressed) {
		D_PostEvent(dotKeyPressed);
	} else {
		D_PostEvent(dotKeyReleased);
	}
}

void ScreenController::shiftPressed(bool pressed) {
	if (pressed) {
		D_PostEvent(shiftKeyPressed);
	} else {
		D_PostEvent(shiftKeyReleased);
	}
}

void ScreenController::attackPressed(bool pressed) {
	if (pressed) {
		D_PostEvent(attackKeyPressed);
	} else {
		D_PostEvent(attackKeyReleased);
	}
}

void ScreenController::usePressed(bool pressed) {
	if (pressed) {
		D_PostEvent(useKeyPressed);
	} else {
		D_PostEvent(useKeyReleased);
	}
}

void ScreenController::selectWeapon(int index) {
	players[0].pendingweapon = static_cast<weapontype_t>(index);
}

void ScreenController::pausePressed(bool pressed) {
	sendpause = pressed;
}

void ScreenController::mousePressed(int mouseX, int mouseY) {
	safeLastMousePosition(mouseX, mouseY);

	if (!activeRect.contains(QPoint(mouseX, mouseY))) {
		return;
	}

	if (tapLock) {
		tapLock = false;
		return;
	}

	if (MenuActive && CurrentMenu) {
		auto pos = clickOnMenuPosition(mouseX, mouseY);
		if (pos != -1) {
			CurrentItPos = pos;
		}
	}
}

void ScreenController::mousePositionChanged(int mouseX, int mouseY) {
	if (MenuActive) {
		if (mouseX - mouseLastPosition.x() > swipeWidth) {
			auto offset = abs(trunc((mouseX - mouseLastPosition.x()) / swipeWidth));
			while (offset--) {
				rightSwipe();
			}
		} else if (mouseX - mouseLastPosition.x() < -swipeWidth) {
			auto offset = abs(trunc((mouseX - mouseLastPosition.x()) / swipeWidth));
			while (offset--) {
				leftSwipe();
			}
		} else {
			mousePressed(mouseX, mouseY);
		}
		safeLastMousePosition(mouseX, mouseY);
	} else {
		if (gameStateActive()) {
			auto offsetX = mouseX - mouseLastPosition.x();
			auto offsetY = mouseY - mouseLastPosition.y();
			// TODO: Search why got double click with same coords on viewing and attacking
			if (offsetX || offsetY) {
				mouseMoved(offsetX, offsetY);
				safeLastMousePosition(mouseX, mouseY);
			}
		}
	}
}

void ScreenController::doubleClick(int x, int y) {
	if (!activeRect.contains(QPoint(x, y))) {
		return;
	}

	if (askforquit) {
		if (yesButtonPressed(x, y)) {
			keyPressedAndReleased(yKeyPressed);
		}
		if (noButtonPressed(x, y)) {
			keyPressedAndReleased(nKeyPressed);
		}
	} else {
		if (MenuActive) {
			if (!FileMenuKeySteal) {
				checkMenuInteraction(x, y);
			} else {
				checkMenuStealKeyInteraction(x, y);
			}
		}
		if (!MenuActive && !gameStateActive()) {
			checkNoneGameMenuInteraction(x, y);
		}
	}
}

void ScreenController::onActiveScreenChanged() {
	auto screen = scenePainter->activeScreen();
	activeRect = QRect(screen.x(), screen.y(), screen.width(), screen.height());
	swipeWidth = std::min(scenePainter->width(), scenePainter->height()) / 16;
}

QVector<ScreenController::MenuItems> ScreenController::menuItems() const {
	QVector<MenuItems> menuItems;

	if (MenuActive && CurrentMenu) {
		for (int i = 0; i < CurrentMenu->itemCount; ++i) {
			if (CurrentMenu->items[i].text) {
				auto width = itemWidth(CurrentMenu->x, CurrentMenu->items[i].text);
				auto coordX = CurrentMenu->x;
				auto coordY = CurrentMenu->y + i * ITEM_HEIGHT;
				auto rect = QRect(coordX, coordY, width, ITEM_HEIGHT);
				menuItems.push_back({i, scenePainter->fromGameCoord(rect, baseScreen)});
			}
		}
	}

	return menuItems;
}

QVector<ScreenController::MenuItems> ScreenController::savesItems() const {
	QVector<MenuItems> menuItems;
	auto slot = static_cast<patch_t*>(W_CacheLumpName("M_FSLOT", PU_CACHE));

	if (MenuActive && CurrentMenu) {
		for (int i = 0; i < CurrentMenu->itemCount; ++i) {
			auto width = slot->width;
			auto coordX = CurrentMenu->x;
			auto coordY = CurrentMenu->y + i * ITEM_HEIGHT;
			auto rect = QRect(coordX, coordY, width, ITEM_HEIGHT);
			menuItems.push_back({i, scenePainter->fromGameCoord(rect, baseScreen)});
		}
	}

	return menuItems;
}

int ScreenController::itemWidth(int x, const char* text) const {
	char c;
	patch_t* p = nullptr;
	int startX = x;

	while ((c = *text++) != 0) {
		if (c < 33) {
			x += 8;
		} else {
			p = static_cast<patch_t*>(W_CacheLumpNum(FontBBaseLump + c - 33, PU_CACHE));
			x += SHORT(p->width) - 1;
		}
	}

	return x - startX;
}

int ScreenController::clickOnMenuPosition(int x, int y) {
	QVector<ScreenController::MenuItems> items;
	if (CurrentMenu && (CurrentMenu->type == MENU_SAVE || CurrentMenu->type == MENU_LOAD)) {
		items = savesItems();
	} else {
		items = menuItems();
	}

	for (const auto it : items) {
		if (it.rect.contains({x, y})) {
			return it.pos;
		}
	}

	return -1;
}

bool ScreenController::yesButtonPressed(int x, int y) {
	return scenePainter->fromGameCoord(yesButton, baseScreen).contains(x, y);
}

bool ScreenController::noButtonPressed(int x, int y) {
	return scenePainter->fromGameCoord(noButton, baseScreen).contains(x, y);
}

void ScreenController::menuMissClicked() {
	keyPressedAndReleased(backspaceKeyPressed);
}

void ScreenController::menuStealKeyMissClicked() {
	keyPressedAndReleased(escapeKeyPressed);
}

void ScreenController::menuStealKeyClicked() {
	keyPressedAndReleased(enterKeyPressed);
}

void ScreenController::menuItemClicked() {
	keyPressedAndReleased(enterKeyPressed);
}

void ScreenController::menuPressed() {
	keyPressedAndReleased(escapeKeyPressed);
}

void ScreenController::leftSwipe() {
	keyPressedAndReleased(leftKeyPressed, 10);
}

void ScreenController::rightSwipe() {
	keyPressedAndReleased(rightKeyPressed, 10);
}

void ScreenController::checkNoneGameMenuInteraction(int x, int y) {
	auto pos = clickOnMenuPosition(x, y);

	if (pos == -1) {
		menuPressed();
	}
}

void ScreenController::checkMenuInteraction(int x, int y) {
	auto pos = clickOnMenuPosition(x, y);

	if (pos == -1) {
		menuMissClicked();
	} else {
		menuItemClicked();
	}
}

void ScreenController::checkMenuStealKeyInteraction(int x, int y) {
	auto pos = clickOnMenuPosition(x, y);

	if (pos == -1) {
		menuStealKeyMissClicked();
	} else {
		menuStealKeyClicked();
	}
}

void ScreenController::safeLastMousePosition(int mouseX, int mouseY) {
	mouseLastPosition = QPoint(mouseX, mouseY);
}

void ScreenController::keyPressedAndReleased(event_t pressedKey, int timeup) {
	if (pressed[pressedKey.data1]) {
		return;
	}
	pressed[pressedKey.data1] = true;
	D_PostEvent(pressedKey);

	QTimer::singleShot(timeup, [&, pressedKey]() {
		event_t releasedKey{ev_keyup, pressedKey.data1, pressedKey.data2, pressedKey.data3};
		D_PostEvent(releasedKey);
		pressed[releasedKey.data1] = false;
	});
}

void ScreenController::mouseMoved(int offsetX, int offsetY) {
	int minSide = std::min(scenePainter->height(), scenePainter->width());
	int maxOffsetX = minSide;
	int maxOffsetY = minSide / 4;
	int finalOffsetX = offsetX << 5;
	int finalOffsetY = offsetY << 5;

	if (abs(finalOffsetX) >= maxOffsetX) {
		finalOffsetX = finalOffsetX > 0 ? maxOffsetX : -maxOffsetX;
	}

	if (abs(finalOffsetY) >= maxOffsetY) {
		finalOffsetY = finalOffsetY > 0 ? maxOffsetY : -maxOffsetY;
	}

	D_PostEvent(event_t{ev_mouse, 0, finalOffsetX, finalOffsetY});
}

void ScreenController::useArtifact() {
	keyPressedAndReleased(enterKeyPressed);
}

void ScreenController::nextWeapon() {
}

void ScreenController::selectArtifact(int index) {
	int offset = index - inv_ptr;
	inventory = true; // NOTE: force open inventory

	if (offset < 0) {
		for (int i = 0; i < abs(offset); ++i) {
			inventoryLeftPressed();
		}
	} else {
		for (int i = 0; i < abs(offset); ++i) {
			inventoryRightPressed();
		}
	}

	// NOTE: force hide inventory, after selecting
	if (offset) {
		useArtifact();
	}
}

void ScreenController::inventoryLeftPressed() {
	D_PostEvent(invLeftKeyPressed);
	D_PostEvent(invLeftKeyReleased);
}

void ScreenController::inventoryRightPressed() {
	D_PostEvent(invRightKeyPressed);
	D_PostEvent(invRightKeyReleased);
}
