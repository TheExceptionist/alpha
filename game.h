#pragma once
class Game
{
public:
	Game(const int width, const int height);
	~Game();

	bool init();
	void update();
	void close();
	void render();

private:
	const int m_width;
	const int m_height;
};

