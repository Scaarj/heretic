#include "screencontroller.h"

#include "doomdef.h"
#include "gamescreen.h"
#include "scenepainter.h"

extern Menu_t* CurrentMenu;
extern boolean MenuActive;
extern int FontBBaseLump;
extern int CurrentItPos;

ScreenController::ScreenController(ScenePainter* painter, QQuickItem* parent)
	: QQuickItem{parent}
	, scenePainter{painter} {
	connect(scenePainter, &ScenePainter::activeScreenRectChanged, this, &ScreenController::onActiveScreenRectChanged);

	connect(this, &ScreenController::mousePressed, this, &ScreenController::onMousePressed);
	connect(this, &ScreenController::doubleClick, this, &ScreenController::onDoubleClick);
	connect(this, &ScreenController::leftSwipe, this, &ScreenController::onLeftSwipe);
	connect(this, &ScreenController::rightSwipe, this, &ScreenController::onRightSwipe);
}

void ScreenController::waitUntilTap() {
	tapLock = true;

	while (tapLock) {
		QGuiApplication::processEvents();
	}
}

void ScreenController::onMousePressed(int x, int y) {
	if (!activeRect.contains(QPoint(x, y))) {
		return;
	}

	if (tapLock) {
		tapLock = false;
		return;
	}

	if (MenuActive && CurrentMenu) {
		auto pos = clickOnMenuPosition(x, y);
		if (pos != -1) {
			CurrentItPos = pos;
		}
	}
}

void ScreenController::onDoubleClick(int x, int y) {
	if (!activeRect.contains(QPoint(x, y))) {
		return;
	}

	auto pos = clickOnMenuPosition(x, y);

	if (MenuActive && pos != -1) {
		D_PostEvent(event_t{ev_keydown, KEY_ENTER, 0, 0});
	} else if (!MenuActive && pos == -1) {
		D_PostEvent(event_t{ev_keydown, KEY_ESCAPE, 0, 0});
	} else if (MenuActive && pos == -1) {
		D_PostEvent(event_t{ev_keydown, KEY_BACKSPACE, 0, 0});
	}
}

void ScreenController::onActiveScreenRectChanged(const QRect& screen) {
	activeRect = QRect(screen.x(), screen.y(), screen.width(), screen.height());
}

void ScreenController::onLeftSwipe() {
	D_PostEvent(event_t{ev_keydown, KEY_LEFTARROW, 0, 0});
}

void ScreenController::onRightSwipe() {
	D_PostEvent(event_t{ev_keydown, KEY_RIGHTARROW, 0, 0});
}

QVector<ScreenController::MenuItems> ScreenController::menuItems() const {
	QVector<MenuItems> menuItems;

	if (MenuActive && CurrentMenu) {
		for (int i = 0; i < CurrentMenu->itemCount; ++i) {
			if (CurrentMenu->items[i].text) {
				auto width = itemWidth(CurrentMenu->x, CurrentMenu->y + i * ITEM_HEIGHT, CurrentMenu->items[i].text);
				auto coordX = CurrentMenu->x;
				auto coordY = CurrentMenu->y + i * ITEM_HEIGHT;
				auto rect = QRect(coordX, coordY, width, ITEM_HEIGHT);
				menuItems.push_back({i, scenePainter->fromGameCoord(rect, QRect(0, 0, 320, 200))});
			}
		}
	}

	return menuItems;
}

int ScreenController::itemWidth(int x, [[maybe_unused]] int y, const char* text) const {
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
