#include "game.h"
#include "resource_manager.h"
#include "filesystem.h"
#include "sprite_renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

SpriteRenderer* renderer;

Game::Game(const int width, const int height)
	: m_width(width), m_height(height)
{

}

Game::~Game()
{
	if(renderer != nullptr) delete renderer;
}

bool Game::init()
{
	bool success = true;

	Filesystem::initDirectories();

#ifdef _DEBUG
	std::cout << Filesystem::getExeDir() << "\n" << Filesystem::getShadersDir() << "\n" << Filesystem::getTextureDir() << "\n" << std::endl;
#endif

	glm::mat4 ortho_projection = glm::ortho(0.0f, static_cast<GLfloat>(m_width), 0.0f, static_cast<GLfloat>(m_height));

	ResourceManager::loadShader("sprite.vs", "sprite.fs", nullptr, "sprite");
	ResourceManager::getShader("sprite").use().setInt("texture", 0);
	ResourceManager::getShader("sprite").setMatrix4("projection", ortho_projection);

	ResourceManager::loadTexture("display-box.png", "display_box_1");

	ResourceManager::loadCharset();

	renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));

	return success;
}

void Game::update()
{
}

void Game::close()
{
}

void Game::render()
{
	renderer->drawSprite(ResourceManager::getTexture("display_box_1"), glm::vec2(0, 0), glm::vec2(50, 50), 0.0f);
	renderer->drawSprite(ResourceManager::getChar(CHAR_A), glm::vec2(60, 60), glm::vec2(16, 16), 0.0f);
	renderer->drawSprite(ResourceManager::getChar(CHAR_C), glm::vec2(75, 60), glm::vec2(16, 16), 0.0f);
}
