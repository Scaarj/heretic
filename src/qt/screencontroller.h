#pragma once

#include <QQuickItem>
#include <QThread>
#include <auroraapp.h>

class ScreenController : public QQuickItem {
	Q_OBJECT

public:
	ScreenController(QQuickItem* parent = nullptr);

	void waitUntilTap();
	void onMousePressed();

signals:
	void mousePressed();

private:
	QThread loopThread;
	std::atomic_bool tapLock;
};
