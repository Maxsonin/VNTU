#pragma once

#include <SFML/Graphics.hpp>

class Props
{
private:
	sf::Sprite sprite;
	sf::IntRect textureRect;

	// For Collision
	sf::RectangleShape plate;

public:

	Props(sf::Texture& texture, sf::IntRect rect, float scale, sf::Vector2f position, sf::Vector2f plateSize, int positionX, int positionY)
		: textureRect(rect)
	{
		// Giving some form to the Props objects
		sprite.setTexture(texture);
		sprite.setTextureRect(textureRect);
		sprite.setScale(scale, scale);
		sprite.setPosition(position);

		plate.setSize(plateSize);
		plate.setPosition(position.x + positionX, position.y + textureRect.height * scale + positionY);

		plate.setFillColor(sf::Color(255, 0, 0, 0)); // To see hitboxs
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
