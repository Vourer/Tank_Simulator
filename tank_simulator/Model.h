#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Model
{
private:
	int _count;
	const std::vector<float> _vertices, _normals, _uvs, _tangents, _bitangents;

	static Model* fromOBJfile(const std::string&);

public:
	Model(const std::vector<float>&, const std::vector<float>&, const std::vector<float>&, const std::vector<float>&, const std::vector<float>&);
	void render() const;
	void renderNormalMapping() const;

	static void loadModels();
	static void deleteModels();

	static const Model *antenna1, *antenna2, *body, *cannon, *hatch, *leftEngineWheel,
		*leftSmallWheel, *leftWheel, *frontLight, *rearLight, *machineGun,
		*rightEngineWheel, *rightSmallWheel, *rightWheel, *track, *turret;
};

