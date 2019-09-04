#include "Espresso/Scene Manager.h"
#include <string>
namespace Espresso {
	std::vector<Scene*> Scene::scenes = {};
	Scene::Scene()
	{
		scenes.push_back(this);
	}
	void Scene::baseUpdate(float dt)
	{
		for (int i = 0; i < scenes.size(); i++) {
			if (scenes[i]->isActive) {
				scenes[i]->childUpdate(dt);
				for (int j = 0; j < scenes.size(); j++) {
					if (i == j)
						continue;
					scenes[j]->isActive = false;
				}
				break;
			}
		}
	}
}