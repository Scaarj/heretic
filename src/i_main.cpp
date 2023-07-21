#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include <QtQuick>
#include <auroraapp.h>
#include <functional>

#include "scenepainter.h"
#include "screencontroller.h"

QGuiApplication* app;
ScenePainter* scenePainter = nullptr;
std::unique_ptr<ScreenController> screenController;

int main(int argc, char* argv[]) {
	QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
	qmlRegisterType<ScenePainter>("Painter.Global", 1, 0, "Painter");
	qmlRegisterType<ScenePainter>("Controller.Global", 1, 0, "ScreenController");

	application->setOrganizationName(QStringLiteral("ru.auroraos"));
	application->setApplicationName(QStringLiteral("heretic"));

	QScopedPointer<QQuickView> view(Aurora::Application::createView());
	view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/heretic.qml")));
	view->show();

	scenePainter = view->rootObject()->findChild<ScenePainter*>("scenePainter");
	Q_ASSERT(scenePainter);

	screenController = std::make_unique<ScreenController>(scenePainter);
	view->rootContext()->setContextProperty("screenController", screenController.get());

	myargc = argc;
	myargv = argv;

	D_DoomMain();

	return 0;
}
