#pragma once

#include "context.h"
#include "doomdef.h"

class IntroScreen : public Context {
public:
	IntroScreen();

	virtual void draw(QPainter* painter) override;
	virtual QSize resize(int orientation) override;
	virtual float ratio() const override;

private:
	void drawText(QPainter* painter, int screenWidth, int screenHeight);
};
