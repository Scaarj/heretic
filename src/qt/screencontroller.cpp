#include "screencontroller.h"

#include "doomdef.h"
#include "gamescreen.h"
#include "mn_menu.h"
#include "scenepainter.h"

extern Menu_t* CurrentMenu;
extern boolean MenuActive;
extern int FontBBaseLump;
extern int CurrentItPos;
extern boolean askforquit;

ScreenController::ScreenController(ScenePainter* painter, QQuickItem* parent)
	: QQuickItem{parent}
	, scenePainter{painter}
	, m_isGameState{false} {
	connect(scenePainter, &ScenePainter::activeScreenRectChanged, this, &ScreenController::onActiveScreenRectChanged);
}

void ScreenController::waitUntilTap() {
	tapLock = true;

	while (tapLock) {
		QGuiApplication::processEvents();
	}
}

void ScreenController::init() {
	YesButtonX = 100 - MN_TextAWidth(QuitEndMsgAnswer[0]) / 2;
	NoButtonX = 200 - MN_TextAWidth(QuitEndMsgAnswer[1]) / 2;
	ConfirmationButtonY = Y_DISP + 100;

	yesButton = QRect(YesButtonX, ConfirmationButtonY, itemWidth(YesButtonX, QuitEndMsgAnswer[0]), ITEM_HEIGHT);
	noButton = QRect(NoButtonX, ConfirmationButtonY, itemWidth(NoButtonX, QuitEndMsgAnswer[1]), ITEM_HEIGHT);
}

void ScreenController::checkGameState(gamestate_t state) {
	auto currentState = GS_LEVEL == state;

	if (currentState != m_isGameState) {
		m_isGameState = currentState;
		emit isGameStateChanged();
	}
}

bool ScreenController::isGameState() {
	return m_isGameState;
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
		if (isGameState()) {
			auto offsetX = mouseX - mouseLastPosition.x();
			auto offsetY = mouseY - mouseLastPosition.y();
			mouseMoved(offsetX, offsetY);
			safeLastMousePosition(mouseX, mouseY);
		}
	}
}

void ScreenController::doubleClick(int x, int y) {
	if (!activeRect.contains(QPoint(x, y))) {
		return;
	}

	if (askforquit) {
		if (yesButtonPressed(x, y)) {
			D_PostEvent(event_t{ev_keydown, 'y', 0, 0});
		}
		if (noButtonPressed(x, y)) {
			D_PostEvent(event_t{ev_keydown, 'n', 0, 0});
		}
	} else {
		if (MenuActive) {
			checkMenuInteraction(x, y);
		}
		if (!MenuActive && !isGameState()) {
			checkNoneGameMenuInteraction(x, y);
		}
	}
}

void ScreenController::onActiveScreenRectChanged(const QRect& screen) {
	activeRect = QRect(screen.x(), screen.y(), screen.width(), screen.height());
	swipeWidth = std::min(scenePainter->width(), scenePainter->height()) / 32;
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
	auto items = menuItems();

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
	D_PostEvent(backspaceKeyPressed);
}

void ScreenController::menuItemClicked() {
	D_PostEvent(enterKeyPressed);
}

void ScreenController::menuPressed() {
	D_PostEvent(escapeKeyPressed);
}

void ScreenController::leftSwipe() {
	if (MenuActive) {
		D_PostEvent(leftKeyPressed);
	}
}

void ScreenController::rightSwipe() {
	if (MenuActive) {
		D_PostEvent(rightKeyPressed);
	}
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

void ScreenController::safeLastMousePosition(int mouseX, int mouseY) {
	mouseLastPosition = QPoint(mouseX, mouseY);
}

void ScreenController::mouseMoved(int offsetX, int offsetY) {
}
