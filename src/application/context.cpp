#include "context.h"

struct Context::rgbTable Context::colors[256];

void Context::setPallete(byte* palette) {
	for (unsigned int i = 0; i < sizeof(gammatable[0]); i++) {
		colors[i].r = gammatable[usegamma][*palette++] >> 2;
		colors[i].g = gammatable[usegamma][*palette++] >> 2;
		colors[i].b = gammatable[usegamma][*palette++] >> 2;
	}
}

void Context::addDrawData(const QVariant& drawData) {
	this->drawData.push_back(drawData);
}

void Context::clearDrawData() {
	drawData.clear();
}
