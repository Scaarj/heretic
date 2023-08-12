#include "application.h"
#include "doomdef.h"

std::unique_ptr<Application> application;

int main(int argc, char* argv[]) {
	application = std::make_unique<Application>(argc, argv);
	myargc = argc;
	myargv = argv;

	application->setOrganizationName(QStringLiteral("ru.auroraos"));
	application->setApplicationName(QStringLiteral("heretic"));
	application->setSource(QStringLiteral("qml/heretic.qml"));
	application->show();

	return application->exec();
}
