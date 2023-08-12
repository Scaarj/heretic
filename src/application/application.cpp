#include "application.h"

Application::Application(int& argc, char** argv) {
#ifdef sailfishapp
	instance = std::unique_ptr<QGuiApplication>(SailfishApp::application(argc, argv));
	view = std::make_unique<QQuickView>(SailfishApp::createView());
#elif auroraapp
	instance = std::unique_ptr<QGuiApplication>(Aurora::Application::application(argc, argv));
	view = std::make_unique<QQuickView>(Aurora::Application::createView());
#endif

	loopTimer = std::make_unique<QTimer>();
	qmlRegisterType<ScenePainter>("Painter.Global", 1, 0, "ScenePainter");
	QObject::connect(loopTimer.get(), &QTimer::timeout, [&]() { D_DoomLoop(); });
}

void Application::setOrganizationName(const QString& organizationName) {
	instance->setOrganizationName(organizationName);
}

void Application::setApplicationName(const QString& applicationName) {
	instance->setApplicationName(applicationName);
}

void Application::setSource(const QString& path) {
#ifdef sailfishapp
	view->setSource(SailfishApp::pathTo(path));
#elif auroraapp
	view->setSource(Aurora::Application::pathTo(path));
#endif
}

void Application::show() {
	view->show();
}

void Application::loop() {
	weaponModel->actualizeWeapon();
	loopTimer->start();
}

void Application::updateDraw(gamestate_t state, bool menuactive) {
	screenController->checkGameState(state, menuactive);
	scenePainter->update();
}

void Application::setDrawPallete(byte* palette) {
	scenePainter->setPallete(palette);
}

int Application::exec() {
	scenePainter = view->rootObject()->findChild<ScenePainter*>("scenePainter");
	Q_ASSERT(scenePainter);
	screenController = std::make_unique<ScreenController>(scenePainter);
	weaponModel = std::make_unique<WeaponModel>();
	view->rootContext()->setContextProperty("screenController", screenController.get());
	view->rootContext()->setContextProperty("weaponModel", weaponModel.get());

	D_DoomMain();

	screenController->initYesNoButton();

	return instance->exec();
}

void Application::setGameContext() {
	scenePainter->setContext(ScenePainter::GameType);
	loopTimer->start();
}

void Application::setIntroContext() {
	scenePainter->setContext(ScenePainter::IntroType);
	scenePainter->printTextLine("");
	scenePainter->printTextLine("");
	scenePainter->printTextLine("HERETIC v0.0.1"); // TODO: read version from pri/rpm
	scenePainter->printTextLine("");
	scenePainter->printTextLine("Works on x86, armv7hl Aurora OS");
	scenePainter->printTextLine("");
	scenePainter->printTextLine("Heretic was ported to Aurora OS");
	scenePainter->printTextLine("by Steve Dubrov");
	scenePainter->printTextLine("You can download the latest versions under:");
	scenePainter->printTextLine("https://github.com/Scaarj/heretic");
	scenePainter->printTextLine("");
	scenePainter->printTextLine("");
	scenePainter->printTextLine("Tap on Screen to go on.");
	scenePainter->printTextLine("");
	scenePainter->printTextLine("");
	scenePainter->update();

	screenController->waitUntilTap();
}
