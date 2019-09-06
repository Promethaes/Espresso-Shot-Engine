#pragma once
#include <vector>
namespace Espresso {
	class Camera;
	class Scene {
	public:
		Scene(bool firstScene);

		void baseUpdate(float dt, Camera& defaultCamera);
		virtual bool init() = 0;
		virtual bool exit() = 0;
		static std::vector<Scene*> scenes;

		bool isActive() const { return active; }
		bool isInit() const { return initialized; }
		bool ShouldExit() const { return shouldExit; }
	protected:
		bool active = false;
		bool initialized = false;
		bool shouldExit = false;
		virtual void childUpdate(float dt, Camera& defaultCamera) = 0;
	};
}