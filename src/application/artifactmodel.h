#pragma once

#include <QAbstractListModel>
#include <vector>

#include "doomdef.h"
#include "itemmodel.h"

class ArtifactModel : public ItemModel {
	Q_OBJECT

	static constexpr int maxArtifactCount = 8;

public:
	ArtifactModel(QObject* parent = nullptr);

	virtual void sync() override;

private:
	virtual void syncSelected() override;
	void endlessArtifacts();

private:
	static const std::vector<Item> allArtifacts;
};
