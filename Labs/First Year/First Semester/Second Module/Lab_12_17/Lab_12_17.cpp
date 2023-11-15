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

float windowX = 960; float windowY = 960;

int WinMain()
{
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Lab_12_17", sf::Style::Close);

	sf::Texture propsText;
	propsText.loadFromFile("Resources/props.png");

	sf::Texture plantsTexture;
	plantsTexture.loadFromFile("Resources/plants.png");
	plantsTexture.loadFromFile("Resources/plants.png");

	Map gameMap;

	Sorceress sorceress;

	Props elementsPlate(propsText, sf::IntRect(350, 265, 98, 80), 2.0f, sf::Vector2f(140, 680), sf::Vector2f(0, 0), 0, 0); // Elements Plate
	Props AngelStatue(propsText, sf::IntRect(443, 19, 41, 76), 2.5f, sf::Vector2f(190, 80), sf::Vector2f(100, 63), 0, -70); // Angel Statue
	Props BigBigTree(plantsTexture, sf::IntRect(20, 10, 117, 143), 2.7f, sf::Vector2f(330, -30), sf::Vector2f(25, 40), 150, -40); // Big Big Tree
	Props MediumTree(plantsTexture, sf::IntRect(160, 16, 100, 140), 2.0f, sf::Vector2f(380, 490), sf::Vector2f(25, 40), 82, -43); // Medium Tree
	Props BigTree(plantsTexture, sf::IntRect(20, 10, 117, 143), 2.5f, sf::Vector2f(450, 550), sf::Vector2f(25, 40), 135, -40); // Big Tree
	Props Bush(plantsTexture, sf::IntRect(210, 175, 50, 50), 2.0f, sf::Vector2f(470, 270), sf::Vector2f(90, 30), 12, -30); // Bush



	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		gameMap.DrawTileMap(window);
		elementsPlate.Draw(window);

		AngelStatue.Draw(window);
		BigBigTree.Draw(window);
		MediumTree.Draw(window);
		BigTree.Draw(window);
		Bush.Draw(window);

		sorceress.UpdateCollision(AngelStatue);
		sorceress.UpdateCollision(BigBigTree);
		sorceress.UpdateCollision(MediumTree);
		sorceress.UpdateCollision(BigTree);
		sorceress.UpdateCollision(Bush);

		sorceress.DrawSorceress(window);
		if (AngelStatue.GetPlateBounds().top > sorceress.GetPlateBounds().top)
		{
			AngelStatue.Draw(window);
		}
		if (BigBigTree.GetPlateBounds().top > sorceress.GetPlateBounds().top)
		{
			BigBigTree.Draw(window);
		}
		if (MediumTree.GetPlateBounds().top > sorceress.GetPlateBounds().top)
		{
			MediumTree.Draw(window);
		}
		if (BigTree.GetPlateBounds().top > sorceress.GetPlateBounds().top)
		{
			BigTree.Draw(window);
		}
		if (Bush.GetPlateBounds().top > sorceress.GetPlateBounds().top)
		{
			Bush.Draw(window);
		}
		window.display();
	}

	return 0;
}
