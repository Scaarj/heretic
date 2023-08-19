#pragma once

#ifdef sailfishapp
	#include <sailfishapp.h>
#elif auroraapp
	#include <auroraapp.h>
#endif

#include <QGuiApplication>
#include <QtQuick>
#include <memory>

#include "artifactmodel.h"
#include "doomdef.h"
#include "scenepainter.h"
#include "screencontroller.h"
#include "weaponmodel.h"

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
	std::unique_ptr<WeaponModel> weaponModel;
	std::unique_ptr<ArtifactModel> artifactModel;

	ScenePainter* scenePainter = nullptr;
};
