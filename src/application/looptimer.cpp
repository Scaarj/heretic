#include "looptimer.h"

#include "doomdef.h"

LoopTimer::LoopTimer()
{
	QObject::connect(this, &QTimer::timeout, [&]() { D_DoomLoop(); });
}
