#pragma once

#include <memory>

#include "../itemsproxy.h"
#include "artifactmodel.h"

namespace items {
namespace artifacts {
	class ArtifactProxy : public ItemsProxy {
		static constexpr int maxArtifactCount = 8;

	public:
		ArtifactProxy();

		ItemProxyModel* model();

	private:
		virtual void syncModel() override;
		virtual void syncSelected() override;
		virtual void endless() override;

	private:
		static const std::vector<Item> allArtifacts;

		std::unique_ptr<ArtifactModel> artifactModel;
		std::unique_ptr<ItemProxyModel> artifactProxyModel;
	};
} // namespace artifacts
} // namespace items
