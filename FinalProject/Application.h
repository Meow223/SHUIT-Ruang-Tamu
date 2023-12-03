#pragma once

#include "RenderEngine.h"
#include "Cube.h"
#include "CubeColor.h"
#include "Shader.h"
#include "Texture.h"
#include "Glass.h"

class Application :
    public RenderEngine
{
public:
    Application();
    ~Application();
private:
	Shader *shader, *shaderColor, *shaderGlass;
	Texture* cubeDiffTex, * cubeSpecTex, * redDiffTex, * redSpecTex, * kotakDiffTex, * kotakSpecTex, * floorDiffTex, * floorSpecTex, * wallDiffTex, * wallSpecTex;
	Texture* woodDiffTex, * woodSpecTex, * wood1DiffTex, * wood1SpecTex, * wood2DiffTex, * wood2SpecTex;
	Texture* figDiffTex, * figSpecTex, * fig1DiffTex, * fig1SpecTex, * fig2DiffTex, * fig2SpecTex;
	Texture* glassDiffTex, * glassSpecTex;
	Texture* grassDiffTex, * grassSpecTex;

	CubeColor *tv, *lamp, *cable;
	Glass *gl;

	Cube *cube;
	Cube* red;
	Cube* grass;
	Cube* wall;
	Cube* wood, * wood1, * wood2;
	Cube* floor;
	Cube* figura, * figura1, * figura2;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	float angle = 0;
	glm::vec3 viewPos;
	void setupPerspective();
	void setupCamera();
	void setupLighting();
	void setupLighting1();
	virtual void Init();
	virtual void DeInit(); 
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);
	void BuildShaders();
	void BuildText();
	void BuildObject();

	//Camera
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();

	//Objek
	void Sofa();
	void Meja();
	void Tembok();
	void TV();
	void Pintu();
	void Figura();
	void Lampu();
	void Vegetation();
};

