#pragma once

#include <SFML/Graphics.hpp>

class Props
{
private:
	sf::Sprite sprite;

	// For Collision
	sf::RectangleShape plate;

	// static Textures
	static sf::Texture propsTexture;
	static sf::Texture plantsTexture;

public:
	#pragma region Constructors

	// Problem we encounting(https://stackoverflow.com/questions/62095373/sfml-texture-not-loading-propely)
	Props(char textureType, sf::IntRect textureRect, float scale, sf::Vector2f position, sf::Vector2f plateSize, sf::Vector2f platePosition)
	{
		if (textureType == 'p')
			sprite.setTexture(propsTexture);
		else if (textureType == 't')
			sprite.setTexture(plantsTexture);

		sprite.setTextureRect(textureRect);
		sprite.setScale(scale, scale);
		sprite.setPosition(position);

		plate.setSize(plateSize);
		plate.setPosition(position.x + platePosition.x, position.y + textureRect.height * scale + platePosition.y);
		plate.setFillColor(sf::Color(255, 0, 0, 0)); // To see hitboxes
	}

	#pragma endregion

	#pragma region Geters&Setters

	sf::RectangleShape GetPlateSprite() const { return plate; }
	sf::FloatRect GetPlateBounds() const { return plate.getGlobalBounds(); }

	#pragma endregion

	#pragma region Creation

	static void InitTextures()
	{
		propsTexture.loadFromFile("Resources/props.png");
		plantsTexture.loadFromFile("Resources/plants.png");
	}

	static std::vector<Props> CreatePropsList()
	{
		std::vector<Props> propsList =
		{
			// If plate size equels (0, 0) it will indicate that we wont include it in the priority function
			Props('p', sf::IntRect(350, 265, 98, 80), 2.0f, sf::Vector2f(140, 680), sf::Vector2f(0, 0), sf::Vector2f(0, 0)),       // Elements Plate
			Props('p', sf::IntRect(443, 19, 41, 76), 2.5f, sf::Vector2f(190, 80), sf::Vector2f(85, 30), sf::Vector2f(10, -70)),    // Angel Statue
			Props('p', sf::IntRect(286, 15, 65, 47), 2.0f, sf::Vector2f(335, 280), sf::Vector2f(120, 55), sf::Vector2f(8, -65)),   // Banch
			Props('t', sf::IntRect(20, 10, 117, 143), 2.7f, sf::Vector2f(330, -30), sf::Vector2f(25, 40), sf::Vector2f(150, -40)), // Big Big Tree
			Props('t', sf::IntRect(160, 16, 100, 140), 2.0f, sf::Vector2f(380, 490), sf::Vector2f(25, 40), sf::Vector2f(80, -43)), // Medium Tree
			Props('t', sf::IntRect(20, 10, 117, 143), 2.5f, sf::Vector2f(450, 550), sf::Vector2f(25, 40), sf::Vector2f(135, -40)), // Big Tree
			Props('t', sf::IntRect(210, 175, 50, 50), 2.0f, sf::Vector2f(470, 263), sf::Vector2f(90, 30), sf::Vector2f(12, -30))   // Bush
		};

		return propsList;
	}

	#pragma endregion

	#pragma region Drawing

	void Draw(sf::RenderWindow& window) const { window.draw(sprite); window.draw(plate); }	// To draw single prop

	static void DrawProps(sf::RenderWindow& window, const std::vector<Props>& propsList) { for (const auto& props : propsList) props.Draw(window); }

	#pragma endregion
};

// Initialize static texture members
sf::Texture Props::propsTexture;
sf::Texture Props::plantsTexture;