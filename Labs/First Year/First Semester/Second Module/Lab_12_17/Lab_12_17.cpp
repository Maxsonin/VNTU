#include <SFML/Graphics.hpp>

#include "Sorceress.h"

class Map
{
private:
	sf::Sprite tileSprite;

	// Tile Settings
	int tileSize = 32;
	float scale = 3.0f;

	// main texture
	sf::Texture tileElements;

	// texture Rect with textures we need
	sf::IntRect grassRect = sf::IntRect(32, 96, 32, 32);
	sf::IntRect pathRect = sf::IntRect(0, 128, 32, 32);
	sf::IntRect WhiteFlowerRect = sf::IntRect(160, 32, 32, 32);
	sf::IntRect YellowFlowerRect = sf::IntRect(160, 96, 32, 32);

	sf::IntRect pathRightTop = sf::IntRect(160, 224, 32, 32);
	sf::IntRect pathLeftTop = sf::IntRect(128, 224, 32, 32);
	sf::IntRect pathRightBottom = sf::IntRect(0, 224, 32, 32);
	sf::IntRect pathLeftBottom = sf::IntRect(32, 224, 32, 32);

	// TileMap using 2d array
	char tileMap[10][10] =
	{
		{'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
		{'w', 't', 's', 'r', 'g', 'g', 'g', 'g', 'g', 'g'},
		{'g', 's', 's', 's', 'g', 'g', 'g', 'g', 'w', 'y'},
		{'g', 'b', 's', 'l', 'g', 'g', 't', 's', 'r', 'w'},
		{'s', 's', 's', 's', 's', 's', 's', 's', 's', 'g'},
		{'s', 's', 's', 's', 's', 's', 's', 's', 's', 'g'},
		{'g', 'g', 'g', 'g', 'g', 'g', 'b', 's', 'l', 'g'},
		{'g', 't', 's', 'r', 'g', 'g', 'y', 'g', 'g', 'g'},
		{'g', 'b', 's', 'l', 'w', 'g', 'g', 'g', 'w', 'g'},
		{'g', 'w', 'g', 'g', 'g', 'w', 'g', 'g', 'g', 'g'}
	};

public:
	Map()
	{
		// Setting up textures
		tileElements.loadFromFile("Resources/WorldTiles.png");
		tileSprite.setTexture(tileElements);
		tileSprite.setScale(scale, scale);
	}

	void DrawTileMap(sf::RenderWindow& window)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				if (tileMap[y][x] == 'g') tileSprite.setTextureRect(grassRect);
				else if (tileMap[y][x] == 's') tileSprite.setTextureRect(pathRect);
				else if (tileMap[y][x] == 'w') tileSprite.setTextureRect(WhiteFlowerRect);
				else if (tileMap[y][x] == 'y') tileSprite.setTextureRect(YellowFlowerRect);
				else if (tileMap[y][x] == 'r') tileSprite.setTextureRect(pathRightTop);
				else if (tileMap[y][x] == 't') tileSprite.setTextureRect(pathLeftTop);
				else if (tileMap[y][x] == 'l') tileSprite.setTextureRect(pathRightBottom);
				else if (tileMap[y][x] == 'b') tileSprite.setTextureRect(pathLeftBottom);
				tileSprite.setPosition(x * tileSize * scale, y * tileSize * scale);
				window.draw(tileSprite);
			}
		}
	}
};

int WinMain()
{
	unsigned int windowX = 960; unsigned int windowY = 960;
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Lab_12_17", sf::Style::Close);

	Map map;

	Sorceress sorceress;

	sf::Texture propsTexture;
	propsTexture.loadFromFile("Resources/props.png");

	sf::Texture plantsTexture;
	plantsTexture.loadFromFile("Resources/plants.png");

	std::vector<Props> propsList = Props::CreatePropsList(propsTexture, plantsTexture);

	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		map.DrawTileMap(window);

		Props::DrawProps(window, propsList);

		sorceress.DrawSorceress(window, propsList);

		sorceress.UpdateDrawPriority(window, propsList);

		window.display();
	}

	return 0;
}
