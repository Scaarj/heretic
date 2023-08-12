#pragma once

#include "context.h"

class GameScreen : public Context {
	static constexpr int pixel_height = 200;
	static constexpr int pixel_width = 320;
	static constexpr float screen_ratio = static_cast<float>(pixel_width) / pixel_height;

public:
	GameScreen();

	virtual void draw(QPainter* painter) override;
	virtual QSize resize(int orientation) override;
	virtual QRect activeScreen() const override;

private:
	QRect screenRect() const;

private:
	unsigned int buffer[pixel_width][pixel_height];
	int image_width, image_height;
};
