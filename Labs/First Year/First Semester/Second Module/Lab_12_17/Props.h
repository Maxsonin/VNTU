#pragma once

#include <SFML/Graphics.hpp>

#include "Sorceress.h"

class Props
{
private:
	sf::Sprite sprite;
	sf::IntRect textureRect;

	// For Collision
	sf::RectangleShape plate;

public:

	Props(const sf::Texture& texture, sf::IntRect rect, float scale, sf::Vector2f position, sf::Vector2f plateSize, int positionX, int positionY)
		: textureRect(rect)
	{
		sprite.setTexture(texture);
		sprite.setTextureRect(textureRect);
		sprite.setScale(scale, scale);
		sprite.setPosition(position);

		plate.setSize(plateSize);
		plate.setPosition(position.x + positionX, position.y + textureRect.height * scale + positionY);

		plate.setFillColor(sf::Color(255, 0, 0, 0)); // To see hitboxs
	}

	static std::vector<Props> CreatePropsList(sf::Texture& propsTexture, sf::Texture& plantsTexture)
	{

		std::vector<Props> propsList =
		{
			Props(propsTexture, sf::IntRect(350, 265, 98, 80), 2.0f, sf::Vector2f(140, 680), sf::Vector2f(0, 0), 0, 0),		   // Elements Plate
			Props(propsTexture, sf::IntRect(443, 19, 41, 76), 2.5f, sf::Vector2f(190, 80), sf::Vector2f(100, 63), 0, -70),        // Angel Statue
			Props(plantsTexture, sf::IntRect(20, 10, 117, 143), 2.7f, sf::Vector2f(330, -30), sf::Vector2f(25, 40), 150, -40), // Big Big Tree
			Props(plantsTexture, sf::IntRect(160, 16, 100, 140), 2.0f, sf::Vector2f(380, 490), sf::Vector2f(25, 40), 82, -43), // Medium Tree
			Props(plantsTexture, sf::IntRect(20, 10, 117, 143), 2.5f, sf::Vector2f(450, 550), sf::Vector2f(25, 40), 135, -40), // Big Tree
			Props(plantsTexture, sf::IntRect(210, 175, 50, 50), 2.0f, sf::Vector2f(470, 270), sf::Vector2f(90, 30), 12, -30)   // Bush
		};

		return propsList;
	}

	const sf::Sprite GetSprite() const { return sprite; }

	// To draw single prop
	void Draw(sf::RenderWindow& window) const
	{
		window.draw(sprite);
		window.draw(plate);
	}

	static void DrawProps(sf::RenderWindow& window, const std::vector<Props>& propsList)
	{
		for (const auto& props : propsList)
		{
			props.Draw(window);
		}
	}

	sf::FloatRect GetPlateBounds() const
	{
		return plate.getGlobalBounds();
	}
};
