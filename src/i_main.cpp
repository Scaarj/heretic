#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include <QtQuick>
#include <auroraapp.h>
#include <functional>

#include "painter.h"

ScenePainter* painter = nullptr;

int main(int argc, char* argv[]) {
	QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
	qmlRegisterType<ScenePainter>("Painter.Global", 1, 0, "Painter");

	application->setOrganizationName(QStringLiteral("ru.auroraos"));
	application->setApplicationName(QStringLiteral("heretic"));

	QScopedPointer<QQuickView> view(Aurora::Application::createView());
	view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/heretic.qml")));
	view->show();

	painter = view->rootObject()->findChild<ScenePainter*>("painter");

	myargc = argc;
	myargv = argv;

	D_DoomMain();

	return 0;
}
