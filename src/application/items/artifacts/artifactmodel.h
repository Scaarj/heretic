#pragma once

#include "../itemmodel.h"

namespace items {
namespace artifacts {
	class ArtifactModel : public ItemModel {
		Q_OBJECT

	public:
		ArtifactModel(const std::vector<Item>& allArtifacts, QObject* parent = nullptr);
		virtual void sync() override;
	};
} // namespace artifacts
} // namespace items
