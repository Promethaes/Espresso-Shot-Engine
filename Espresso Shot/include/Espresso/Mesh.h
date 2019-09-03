#pragma once
#include "IO.h"
namespace Espresso {
	class Mesh {
	public:
		Mesh(const std::string& path) { this->path = path; }

		bool loadMesh(const std::string& path);
		bool loadMesh();

		void unload();
		void draw();
		unsigned VBOverts = 0;
		unsigned VBOuvs = 0;
		unsigned VBOnormals = 0;
		unsigned VAO = 0;

		unsigned getFaces() const { return numFaces; }
		unsigned getVerts() const { return numVerts; }
	private:
		unsigned numFaces = 0;
		unsigned numVerts = 0;
		std::string path;
	};
}