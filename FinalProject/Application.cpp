#include "Application.h"

Application::Application()
{
	angle = 0;
}

Application::~Application()
{
}

void Application::InitCamera() {
	posCamX = 0.0f;
	posCamY = 0.5f;
	posCamZ = 3.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.001f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::setupPerspective()
{
	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	shader->setMat4("projection", projection);
	shaderColor->setMat4("projection", projection);
	shaderGlass->setMat4("projection", projection);
	GLint projLoc = glGetUniformLocation(shaderGlass->shaderID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

}

void Application::setupCamera()
{
	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	shader->setMat4("view", view);
	shaderColor->setMat4("view", view);
	shaderGlass->setMat4("view", view);

}

void Application::setupLighting()
{
	// set lighting attributes
	viewPos = glm::vec3(0, 1, 0);
	glm::vec3 lightPos = glm::vec3(0, 1, 3);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", viewPos);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader->setVec3("lightColor", lightColor);

	shaderGlass->setVec3("lightPos", lightPos);
	shaderGlass->setVec3("viewPos", viewPos);
	shaderGlass->setVec3("lightColor", lightColor);
}

void Application::setupLighting1()
{
	// set lighting attributes
	viewPos = glm::vec3(0, 1, 0);
	glm::vec3 lightPos = glm::vec3(0, 1, 1);
	shaderColor->setVec3("lightPos", lightPos);
	shaderColor->setVec3("viewPos", viewPos);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shaderColor->setVec3("lightColor", lightColor);
}


void Application::Init()
{

	//BuildShader
	BuildShaders();

	//Building Texture
	BuildText();

	//Building Object Cube
	BuildObject();

	//Camera
	InitCamera();

	// setup perspective 
	setupPerspective();

	// setup lighting
	setupLighting();
	setupLighting1();
}

void Application::DeInit()
{
	delete cube;
}

void Application::Update(double deltaTime)
{
	angle += (float)((deltaTime * 1.5f) / 1000);
	cube->SetRotation(angle, 0, 1, 0);
}

void Application::Render()
{
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// setup camera
	setupCamera();

	Vegetation();
	Tembok();
	Sofa();
	Meja();
	TV();
	Pintu();
	Figura();
	Lampu();



	//glass !!! Render  paling akhir dulu biar objek dapat terlihat semua sisi kaca
	gl->SetPosition(-1.83f, 0.55f, 1.0f);
	gl->SetScale(0.02f, 1.3f, 2.895f);
	gl->Draw();

	gl->SetPosition(0.0f, 0.105f, 1.0f); // Papan atas
	gl->SetScale(0.8f, 0.01f, 1.1f);
	gl->Draw();

	glDisable(GL_DEPTH_TEST);

}

void Application::BuildShaders()
{
	// shader program
	// ------------------------------------

	//Shader Cube RGB
	shaderColor = new Shader("cube.vert", "cube.frag");
	shaderColor->Init();

	//Shader Cube Glass
	shaderGlass = new Shader("texturedCube.vert", "texturedCube.frag");
	shaderGlass->Init();

	//Shader Cube Texture
	shader = new Shader("texturedCube.vert", "texturedCube.frag");
	shader->Init();
}

void Application::BuildText()
{
	// Building Texture for Object
	// ------------------------------------

	// Create cube diffuse texture and specular texture
	glassDiffTex = new Texture("Glasss.png");
	glassDiffTex->Init();
	glassSpecTex = new Texture("Glasss.png");
	glassSpecTex->Init();

	// Create cube diffuse texture and specular texture
	cubeDiffTex = new Texture("Grass.jpg");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("Grass.jpg");
	cubeSpecTex->Init();

	// Create red diffuse texture and specular texture
	redDiffTex = new Texture("red.png");
	redDiffTex->Init();
	redSpecTex = new Texture("red.png");
	redSpecTex->Init();

	// Create wood diffuse texture and specular texture
	woodDiffTex = new Texture("whiteoak.png");
	woodDiffTex->Init();
	woodSpecTex = new Texture("whiteoak.png");
	woodSpecTex->Init();

	// Create wood diffuse texture and specular texture
	wood1DiffTex = new Texture("wood.png");
	wood1DiffTex->Init();
	wood1SpecTex = new Texture("wood.png");
	wood1SpecTex->Init();

	// Create wood diffuse texture and specular texture
	wood2DiffTex = new Texture("oak.png");
	wood2DiffTex->Init();
	wood2SpecTex = new Texture("oak.png");
	wood2SpecTex->Init();


	// Create floor diffuse texture and specular texture
	floorDiffTex = new Texture("wood_floor.png");
	floorDiffTex->Init();
	floorSpecTex = new Texture("wood_floor.png");
	floorSpecTex->Init();

	// Create wall diffuse texture and specular texture
	wallDiffTex = new Texture("wallp.png");
	wallDiffTex->Init();
	wallSpecTex = new Texture("wallp.png");
	wallSpecTex->Init();

	// Create wall diffuse texture and specular texture
	figDiffTex = new Texture("cat.png");
	figDiffTex->Init();
	figSpecTex = new Texture("cat.png");
	figSpecTex->Init();

	// Create wall diffuse texture and specular texture
	fig1DiffTex = new Texture("cat1.png");
	fig1DiffTex->Init();
	fig1SpecTex = new Texture("cat1.png");
	fig1SpecTex->Init();


	// Create wall diffuse texture and specular texture
	fig2DiffTex = new Texture("war.jpg");
	fig2DiffTex->Init();
	fig2SpecTex = new Texture("war.jpg");
	fig2SpecTex->Init();

	// Create grass diffuse texture and specular texture
	grassDiffTex = new Texture("Grass.jpg");
	grassDiffTex->Init();
	grassSpecTex = new Texture("Grass.jpg");
	grassSpecTex->Init();

}

void Application::BuildObject()
{
	// Build object after inisilies the shader and texture
	// ------------------------------------

	// Create instance of cube
	cube = new Cube(shader, cubeDiffTex, cubeSpecTex);
	cube->Init();
	cube->SetScale(0.2f, 0.2f, 0.2f);
	// Create instance of red
	red = new Cube(shader, redDiffTex, redSpecTex);
	red->Init();
	red->SetScale(0.2f, 0.2f, 0.2f);
	// Create instance of wood
	wood = new Cube(shader, woodDiffTex, woodSpecTex);
	wood->Init();
	wood->SetScale(0.2f, 0.2f, 0.2f);
	// Create instance of wood1
	wood1 = new Cube(shader, wood1DiffTex, wood1SpecTex);
	wood1->Init();
	wood1->SetScale(0.2f, 0.2f, 0.2f);
	// Create instance of wood2
	wood2 = new Cube(shader, wood2DiffTex, wood2SpecTex);
	wood2->Init();
	wood2->SetScale(0.2f, 0.2f, 0.2f);
	// Create instance of floor
	floor = new Cube(shader, floorDiffTex, floorSpecTex);
	floor->Init();
	floor->SetScale(0.2f, 0.2f, 0.2f);
	// Create instance of wall
	wall = new Cube(shader, wallDiffTex, wallSpecTex);
	wall->Init();
	wall->SetScale(0.1f, 0.1f, 0.1f);
	// Create instance of figura
	figura = new Cube(shader, figDiffTex, figSpecTex);
	figura->Init();
	figura->SetScale(0.1f, 0.1f, 0.1f);
	// Create instance of figura1
	figura1 = new Cube(shader, fig1DiffTex, fig1SpecTex);
	figura1->Init();
	figura1->SetScale(0.1f, 0.1f, 0.1f);
	// Create instance of figura2
	figura2 = new Cube(shader, fig2DiffTex, fig2SpecTex);
	figura2->Init();
	figura2->SetScale(0.1f, 0.1f, 0.1f);
	// Create instance of grass
	grass = new Cube(shader, grassDiffTex, grassSpecTex);
	grass->Init();
	grass->SetScale(0.2f, 0.2f, 0.2f);
	// Create instance of tv
	tv = new CubeColor(shaderColor);
	tv->Init();
	tv->SetRotation(0, 0, 1, 0);
	// Create instance of lamp
	lamp = new CubeColor(shaderColor);
	lamp->Init();
	lamp->SetRotation(0, 0, 1, 0);
	// Create instance of cable
	cable = new CubeColor(shaderColor);
	cable->Init();
	cable->SetRotation(0, 0, 1, 0);
	// Create instance of glass
	gl = new Glass(shaderGlass, glassDiffTex, glassSpecTex);
	gl->Init();
	gl->SetScale(0.1f, 0.1f, 0.1f);
}

void Application::Meja()
{
	// Meja Tamu
	/*wood->SetPosition(0.0f, 0.1f, 1.0f); // Papan atas
	wood->SetScale(0.8f, 0.1f, 1.1f);
	wood->Draw();*/

	wood->SetPosition(-0.35f, 0.0f, 0.5f); // Kaki 1
	wood->SetScale(0.1f, 0.2f, 0.1f);
	wood->Draw();
	wood->SetPosition(0.35f, 0.0f, 0.5f); // Kaki 2
	wood->SetScale(0.1f, 0.2f, 0.1f);
	wood->Draw();
	wood->SetPosition(-0.35f, 0.0f, 1.5f); // Kaki 3
	wood->SetScale(0.1f, 0.2f, 0.1f);
	wood->Draw();
	wood->SetPosition(0.35f, 0.0f, 1.5f); // Kaki 4
	wood->SetScale(0.1f, 0.2f, 0.1f);
	wood->Draw();
	//Meja TV
	wood->SetPosition(-1.4f, 0.07f, 1.0f); // Papan atas
	wood->SetScale(0.4f, 0.05f, 0.5f);
	wood->Draw();
	wood->SetPosition(-1.4f, 0.0f, 1.0f); // Papan bawah
	wood->SetScale(0.4f, 0.02f, 0.5f);
	wood->Draw();
	wood->SetPosition(-1.225f, 0.0f, 1.225f); // Kaki1
	wood->SetScale(0.05f, 0.19f, 0.05f);
	wood->Draw();
	wood->SetPosition(-1.575f, 0.0f, 1.225f); // Kaki2
	wood->SetScale(0.05f, 0.19f, 0.05f);
	wood->Draw();
	wood->SetPosition(-1.225f, 0.0f, 0.775f); // Kaki3
	wood->SetScale(0.05f, 0.19f, 0.05f);
	wood->Draw();
	wood->SetPosition(-1.575f, 0.0f, 0.775f); // Kaki4
	wood->SetScale(0.05f, 0.19f, 0.05f);
	wood->Draw();
}

void Application::Sofa()
{
	// Sofa
	red->SetPosition(0.0f, 0.0f, 0.0f);
	red->SetScale(1.0f, 0.2f, 0.5f);
	red->Draw();
	red->SetPosition(-0.4f, 0.2f, 0.0f);
	red->SetScale(0.2f, 0.2f, 0.5f);
	red->Draw();
	red->SetPosition(0.4f, 0.2f, 0.0f);
	red->SetScale(0.2f, 0.2f, 0.5f);
	red->Draw();
	red->SetPosition(0.0f, 0.2f, -0.2f);
	red->SetScale(0.6f, 0.2f, 0.1f);
	red->Draw();

	// Sofa1
	red->SetPosition(0.0f, 0.0f, 2.0f);
	red->SetScale(1.0f, 0.2f, 0.5f);
	red->Draw();
	red->SetPosition(-0.4f, 0.2f, 2.0f);
	red->SetScale(0.2f, 0.2f, 0.5f);
	red->Draw();
	red->SetPosition(0.4f, 0.2f, 2.0f);
	red->SetScale(0.2f, 0.2f, 0.5f);
	red->Draw();
	red->SetPosition(0.0f, 0.2f, 2.2f);
	red->SetScale(0.6f, 0.2f, 0.1f);
	red->Draw();

	// Sofa2
	red->SetPosition(0.8f, 0.0f, 1.0f);
	red->SetScale(0.5f, 0.2f, 1.0f);
	red->Draw();
	red->SetPosition(0.8f, 0.2f, 0.6f);
	red->SetScale(0.5f, 0.2f, 0.2f);
	red->Draw();
	red->SetPosition(0.8f, 0.2f, 1.4f);
	red->SetScale(0.5f, 0.2f, 0.2f);
	red->Draw();
	red->SetPosition(1.0f, 0.2f, 1.0f);
	red->SetScale(0.1f, 0.2f, 0.6f);
	red->Draw();
}

void Application::Tembok()
{
	//tembok
	wall->SetPosition(0.55f, 0.55f, -0.475f);
	wall->SetScale(2.5f, 1.3f, 0.05f);
	wall->Draw();

	wall->SetPosition(-1.625f, 0.55f, -0.475f);
	wall->SetScale(0.45f, 1.3f, 0.05f);
	wall->Draw();

	wall->SetPosition(-1.05f, 1.0f, -0.475f);
	wall->SetScale(0.7f, 0.4f, 0.05f);
	wall->Draw();

	//tembok
	wall->SetPosition(0.55f, 0.55f, 2.475f);
	wall->SetScale(2.5f, 1.3f, 0.05f);
	wall->Draw();

	wall->SetPosition(-1.625f, 0.55f, 2.475f);
	wall->SetScale(0.45f, 1.3f, 0.05f);
	wall->Draw();

	wall->SetPosition(-1.05f, 1.0f, 2.475f);
	wall->SetScale(0.7f, 0.4f, 0.05f);
	wall->Draw();


	//tembok
	wall->SetPosition(1.8f, 0.55f, 1.0f);
	wall->SetScale(0.05f, 1.3f, 3.0f);
	wall->Draw();

	/*
	//tembok
	wall->SetPosition(-1.7f, 0.55f, 1.0f);
	wall->SetScale(0.05f, 1.3f, 3.0f);
	wall->Draw();
	*/

	//floor
	floor->SetPosition(-0.0f, -0.15f, 1.0f);
	floor->SetScale(3.7f, 0.1f, 3.0f);
	floor->Draw();

	//Ceiling
	floor->SetPosition(-0.0f, 1.25f, 1.0f);
	floor->SetScale(3.7f, 0.1f, 3.0f);
	floor->Draw();
}

void Application::Lampu()
{
	//Lampu
	lamp->SetColor(255.0f, 255.0f, 255.0f);
	lamp->SetPosition(0.0f, 1.0f, 1.0f);
	lamp->SetScale(0.05f, 0.1f, 0.05f);
	lamp->Draw();
	lamp->SetColor(44.0f, 44.0f, 44.0f);
	lamp->SetPosition(0.0f, 1.1f, 1.0f);
	lamp->SetScale(0.003f, 0.1f, 0.003f);
	lamp->Draw();
}

void Application::TV()
{
	//TV
	tv->SetColor(7.0f, 7.0f, 7.0f);
	tv->SetPosition(-1.4f, 0.1f, 1.0f);
	tv->SetScale(0.1f, 0.01f, 0.1f);
	tv->Draw();
	tv->SetPosition(-1.4f, 0.15f, 1.0f);
	tv->SetScale(0.01f, 0.1f, 0.01f);
	tv->Draw();
	tv->SetPosition(-1.4f, 0.4f, 1.0f);
	tv->SetScale(0.02f, 0.4f, 0.7f);
	tv->Draw();
}

void Application::Figura()
{
	//figura cat
	figura->SetPosition(0.0f, 0.6f, -0.45f);
	figura->SetScale(0.4f, 0.5f, 0.01f);
	figura->Draw();
	//figura cat 2
	figura1->SetPosition(0.6f, 0.6f, -0.45f);
	figura1->SetScale(0.4f, 0.5f, 0.01f);
	figura1->Draw();
	//figura war
	figura2->SetPosition(1.76f, 0.6f, 1.0f);
	figura2->SetScale(0.01f, 0.5f, 2.5f);
	figura2->Draw();
}

void Application::Vegetation()
{
	//Hedge
	cube->SetPosition(-5.0f, 0.046f, 1.0f);
	cube->SetScale(0.3f, 0.4f, 3.0f);
	cube->Draw();

	//Grass
	grass->SetPosition(-3.35f, -0.175f, 1.0f);
	grass->SetScale(3.0f, 0.05f, 3.0f);
	grass->Draw();
}

void Application::Pintu()
{
	//Door arch 1
	wood->SetPosition(-1.05f, 0.78f, -0.475f);
	wood->SetScale(0.7f, 0.04f, 0.05f);
	wood->Draw();

	wood->SetPosition(-1.38f, 0.33f, -0.475f);
	wood->SetScale(0.04f, 0.87f, 0.05f);
	wood->Draw();

	wood->SetPosition(-0.72f, 0.33f, -0.475f);
	wood->SetScale(0.04f, 0.87f, 0.05f);
	wood->Draw();

	//Door arch 2
	wood->SetPosition(-1.05f, 0.78f, 2.475f);
	wood->SetScale(0.7f, 0.04f, 0.05f);
	wood->Draw();

	wood->SetPosition(-1.38f, 0.33f, 2.475f);
	wood->SetScale(0.04f, 0.87f, 0.05f);
	wood->Draw();

	wood->SetPosition(-0.72f, 0.33f, 2.475f);
	wood->SetScale(0.04f, 0.87f, 0.05f);
	wood->Draw();
}

void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);

}

void Application::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Application::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Application::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}

int main(int argc, char** argv) {
	Application app = Application();
	app.Start("Cube Example", 
		1280, 800, 
		false, 
		false);
}