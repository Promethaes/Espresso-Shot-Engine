#pragma once
#include <vector>
namespace Espresso {
	class Scene {
	public:
		Scene();

		void baseUpdate(float dt);
		virtual void init() = 0;
		virtual void exit() = 0;
		bool isActive = false;
		static std::vector<Scene*> scenes;
	private:
		virtual void childUpdate(float dt) = 0;
	};
}