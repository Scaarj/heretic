#pragma once

#ifdef sailfishapp
	#include <sailfishapp.h>
#elif auroraapp
	#include <auroraapp.h>
#endif

#include <QGuiApplication>
#include <QtQuick>
#include <memory>

#include "doomdef.h"
#include "items/artifacts/artifactproxy.h"
#include "items/weapons/weaponproxy.h"
#include "scenepainter.h"
#include "screencontroller.h"

class QGuiApplication;
class QQuickView;
class QTimer;

class Application
{
public:
	Application(int& argc, char** argv);
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	~Application() = default;

	void setOrganizationName(const QString& organizationName);
	void setApplicationName(const QString& applicationName);
	void setApplicationVersion(const QString& applicationVersion);
	void setSource(const QString& path);
	void updateDraw();
	void setDrawPallete(byte* palette);
	void setGameContext();
	void setIntroContext();
	void show();
	void loop();

	int exec();

private:
	std::unique_ptr<QGuiApplication> instance;
	std::unique_ptr<QQuickView> view;
	std::unique_ptr<QTimer> loopTimer;
	std::unique_ptr<ScreenController> screenController;
	std::unique_ptr<items::weapons::WeaponProxy> weaponProxy;
	std::unique_ptr<items::artifacts::ArtifactProxy> artifactProxy;

	ScenePainter* scenePainter = nullptr;
};
