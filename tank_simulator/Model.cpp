#include "Model.h"

#include <fstream>

const Model *Model::antenna1, *Model::antenna2, *Model::body, *Model::cannon, *Model::hatch, *Model::leftEngineWheel,
	*Model::leftSmallWheel, *Model::leftWheel, *Model::frontLight, *Model::rearLight, *Model::machineGun,
	*Model::rightEngineWheel, *Model::rightSmallWheel, *Model::rightWheel, *Model::track, *Model::turret;


Model::Model(const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<float>& uvs) :
	_vertices(vertices), _normals(normals), _uvs(uvs), _count(vertices.size() / 4)
{}

void Model::render() const
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, _vertices.data());
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, _normals.data());
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, _uvs.data());
	glDrawArrays(GL_TRIANGLES, 0, _count);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Model::loadModels()
{	antenna1 = fromOBJfile("models/antenna_1.obj", false);
	antenna2 = fromOBJfile("models/antenna_2.obj", false);
	body = fromOBJfile("models/body.obj", true);
	cannon = fromOBJfile("models/cannon.obj", false);
	hatch = fromOBJfile("models/hatch.obj", false);
	leftEngineWheel = fromOBJfile("models/left_engine_wheel.obj", false);
	leftSmallWheel = fromOBJfile("models/left_small_wheel.obj", false);
	leftWheel = fromOBJfile("models/left_wheel.obj", false);
	frontLight = fromOBJfile("models/light_front.obj", false);
	rearLight = fromOBJfile("models/light_rear.obj", false);
	machineGun = fromOBJfile("models/machine_gun.obj", false);
	rightEngineWheel = fromOBJfile("models/right_engine_wheel.obj", false);
	rightSmallWheel = fromOBJfile("models/right_small_wheel.obj", false);
	rightWheel = fromOBJfile("models/right_wheel.obj", false);
	track = fromOBJfile("models/track.obj", false);
	turret = fromOBJfile("models/turret.obj", true);
}

void Model::deleteModels()
{
	delete antenna1;
	delete antenna2;
	delete body;
	delete cannon;
	delete hatch;
	delete leftEngineWheel;
	delete leftSmallWheel;
	delete leftWheel;
	delete frontLight;
	delete rearLight;
	delete machineGun;
	delete rightEngineWheel;
	delete rightSmallWheel;
	delete rightWheel;
	delete track;
	delete turret;
}

Model* Model::fromOBJfile(const std::string& filename, bool reverseNormals)
{
	std::vector<glm::vec4> tmpVertices, tmpNormals;
	std::vector<glm::vec2> tmpUvs;
	std::vector<unsigned int> vertexIndices, normalIndices, uvIndices;
	std::ifstream file(filename);
	std::string head, line;
	float x, y, z;
	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

	while (file >> head) {
		if (head == "v") {
			file >> x >> y >> z;
			tmpVertices.push_back(glm::vec4(x, y, z, 1.0f));
		}
		else if (head == "vt") {
			file >> x >> y;
			tmpUvs.push_back(glm::vec2(x, y));
		}
		else if (head == "vn") {
			file >> x >> y >> z;
			if (reverseNormals)
				y = -y;
			tmpNormals.push_back(glm::vec4(x, y, z, .0f));
		}
		else if (head == "f") {
			std::getline(file, line);
			if (sscanf_s(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", vertexIndex, uvIndex, normalIndex,
				vertexIndex + 1, uvIndex + 1, normalIndex + 1, vertexIndex + 2, uvIndex + 2, normalIndex + 2) != 9)
				return nullptr;
			vertexIndices.push_back(vertexIndex[0] - 1);
			vertexIndices.push_back(vertexIndex[1] - 1);
			vertexIndices.push_back(vertexIndex[2] - 1);
			uvIndices.push_back(uvIndex[0] - 1);
			uvIndices.push_back(uvIndex[1] - 1);
			uvIndices.push_back(uvIndex[2] - 1);
			normalIndices.push_back(normalIndex[0] - 1);
			normalIndices.push_back(normalIndex[1] - 1);
			normalIndices.push_back(normalIndex[2] - 1);
		}
	}

	std::vector<float> vertices, normals, uvs;
	for (int i = 0; i < vertexIndices.size(); i++) {
		glm::vec4 vertex = tmpVertices[vertexIndices[i]];
		vertices.push_back(vertex.x);
		vertices.push_back(vertex.y);
		vertices.push_back(vertex.z);
		vertices.push_back(vertex.w);
	}
	for (int i = 0; i < normalIndices.size(); i++) {
		glm::vec4 normal = tmpNormals[normalIndices[i]];
		normals.push_back(normal.x);
		normals.push_back(normal.y);
		normals.push_back(normal.z);
		normals.push_back(normal.w);
	}
	for (int i = 0; i < uvIndices.size(); i++) {
		glm::vec2 uv = tmpUvs[uvIndices[i]];
		uvs.push_back(uv.x);
		uvs.push_back(uv.y);
	}

	file.close();

	return new Model(vertices, normals, uvs);
}

