#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Sorceress.h"
#include "Wizard.h"
#include "HUD.h"

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
		{'w', 't', 's', 'r', 'g', 'g', 'g', 'y', 'g', 'g'},
		{'g', 's', 's', 's', 'g', 'y', 'g', 'g', 'w', 'y'},
		{'y', 'b', 's', 'l', 'g', 'g', 't', 's', 'r', 'w'},
		{'s', 's', 's', 's', 's', 's', 's', 's', 's', 'g'},
		{'s', 's', 's', 's', 's', 's', 's', 's', 's', 'g'},
		{'g', 'g', 'w', 'g', 'g', 'g', 'b', 's', 'l', 'g'},
		{'g', 't', 's', 'r', 'g', 'g', 'y', 'g', 'g', 'y'},
		{'y', 'b', 's', 'l', 'w', 'g', 'y', 'g', 'w', 'g'},
		{'g', 'w', 'g', 'w', 'g', 'w', 'g', 'g', 'g', 'g'}
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

class Key
{
private:
	sf::Texture keysTexture;
	sf::Sprite spriteForKey;
	sf::Vector2f position;
	float keySize = 0.0f;

public:
	Key(const sf::Vector2f& position)
		: position(position)
	{
		keysTexture.loadFromFile("Resources/keys.png");
		spriteForKey.setTexture(keysTexture);
		spriteForKey.setTextureRect(sf::IntRect(85, 26, 13, 13));
		spriteForKey.setPosition(position);
		spriteForKey.setOrigin(spriteForKey.getLocalBounds().width / 2, spriteForKey.getLocalBounds().height / 2);
	}

	void ShowToTalk(sf::RenderWindow& window, Wizard& wizard, Sorceress& sorceress)
	{
		if (!sorceress.HasTalkedToWizard())
		{
			if (sorceress.CheckCollisionWithWizard(wizard) && keySize <= 3.5f)
			{
				keySize += 0.01f;
				spriteForKey.setScale(keySize, keySize);
			}
			else if (keySize >= 0.0f)
			{
				keySize -= 0.01f;
				spriteForKey.setScale(keySize, keySize);
			}
			window.draw(spriteForKey);

			if (sorceress.CheckCollisionWithWizard(wizard))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					sorceress.ChangeIsTalking(true);
					sorceress.ChangeIfHasTalked(true);
				}
			}
		}
		else if (keySize >= 0.0f)
		{
			keySize -= 0.01f;
			spriteForKey.setScale(keySize, keySize);
			window.draw(spriteForKey);
		}
	}
};

int WinMain()
{
	sf::RenderWindow window(sf::VideoMode(960, 960), "Lab_12_17", sf::Style::Close);

	// Music for background
	sf::Music st;
	st.openFromFile("Resources/st.mp3");
	st.setVolume(30);
	st.play();

	// Initializaing
	Map map;
	Wizard wizard;
	Sorceress sorceress;
	HUD hud;
	Key key(sf::Vector2f(365, 270));

	// Props Initialization
	Props::InitTextures(); // Becouse of the vector we will initialize texture for props here
	std::vector<Props> propsList = Props::CreatePropsList();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear();

		// Draw map
		map.DrawTileMap(window);
		Props::DrawProps(window, propsList);

		// We will add some conditions to make it work properly
		if (sorceress.HasTalkedToWizard() && !wizard.IsVenished() && !sorceress.IsTalking())
		{
			wizard.Vanish(window);
		}
		else
		{
			wizard.Draw(window);
		}

		// Draw our Sorceress
		sorceress.DrawSorceress(window, propsList, wizard);
		sorceress.UpdateDrawPriority(window, propsList, wizard);

		key.ShowToTalk(window, wizard, sorceress); // For key that appears 

        if (sorceress.IsTalking()) wizard.Talk(window); // If Sorceress is talking it means that wizard should talk too

		hud.HandleHUD(window, sorceress); // All HUD drawn here

		window.display();
	}

	return EXIT_SUCCESS;
}