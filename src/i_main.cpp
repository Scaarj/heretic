#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include <QtQuick>
#include <functional>

#include "scenepainter.h"
#include "screencontroller.h"
#include "weaponmodel.h"

QGuiApplication* app;
ScenePainter* scenePainter = nullptr;
std::unique_ptr<ScreenController> screenController;
std::unique_ptr<WeaponModel> weaponModel;

int main(int argc, char* argv[]) {
#ifdef sailfishapp
	QScopedPointer<QGuiApplication> application(SailfishApp::application(argc, argv));
#elif auroraapp
	QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
#endif
	qmlRegisterType<ScenePainter>("Painter.Global", 1, 0, "ScenePainter");

	application->setOrganizationName(QStringLiteral("ru.auroraos"));
	application->setApplicationName(QStringLiteral("heretic"));

#ifdef sailfishapp
	QScopedPointer<QQuickView> view(SailfishApp::createView());
	view->setSource(SailfishApp::pathTo(QStringLiteral("qml/heretic.qml")));
#elif auroraapp
	QScopedPointer<QQuickView> view(Aurora::Application::createView());
	view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/heretic.qml")));
#endif
	view->show();

	scenePainter = view->rootObject()->findChild<ScenePainter*>("scenePainter");
	Q_ASSERT(scenePainter);

	screenController = std::make_unique<ScreenController>(scenePainter);
	view->rootContext()->setContextProperty("screenController", screenController.get());

	weaponModel = std::make_unique<WeaponModel>();
	view->rootContext()->setContextProperty("weaponModel", weaponModel.get());

	myargc = argc;
	myargv = argv;

	D_DoomMain();

	return 0;
}
