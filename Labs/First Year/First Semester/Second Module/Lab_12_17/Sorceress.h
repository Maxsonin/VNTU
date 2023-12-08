#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Props.h"
#include "Wizard.h"

class Sorceress
{
private:
	sf::Texture bodyTexture;
	sf::Sprite sprite;

	// General settings
	float movelen = 0.15f;
	float currentSize = 2.0f;

	// For work with animations
	float cFrame = 0;
	bool direction = true; // True - right

	// Collision rectangle
	sf::RectangleShape plate;
	bool isAboveProps = false;

	// For talking
	bool hasTalked = false;
	bool isTalking = false;

	// For HP Bar
	int HP = 100;
	sf::Music pain;
	bool damegeGet = false;

	// Proority Test
	// sf::RectangleShape test;

public:
	#pragma region Constructors

	Sorceress()
	{
		// Giving some form to the Sorceress object
		bodyTexture.loadFromFile("Resources/animation.png");
		sprite.setTexture(bodyTexture);
		sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		sprite.setPosition(100, 420); // Set spawn position
		sprite.setScale(currentSize, currentSize);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

		plate.setSize(sf::Vector2f(70, 35)); // Rectangle that will halp us handle Collision
		plate.setFillColor(sf::Color(255, 0, 0, 0)); // To see hitboxs(Rectangle)

		pain.openFromFile("Resources/pain.mp3"); // add sound that will play whan hit

		// Priority Test
		// test.setSize(sf::Vector2f(1000.f, 1000.f));
		// test.setFillColor(sf::Color(255, 0, 0, 90));
	}

	#pragma endregion 

	#pragma region Geters&Setters

	bool HasTalkedToWizard() const { return hasTalked; }

	bool Alive() const { return (HP > 0 ? 1 : 0); }

	bool DamegeGet() const { return damegeGet; }

	void ChangeDamegeGet(bool newValue) { damegeGet = newValue; }

	bool IsTalking() const { return isTalking; }

	void ChangeIsTalking(bool newValue) { isTalking = newValue; }

	void ChangeIfHasTalked(bool newValue) { hasTalked = newValue; }

	int GetCurrentHP() { return HP; }

	sf::FloatRect GetPlateBounds() const { return plate.getGlobalBounds(); }

	#pragma endregion

	#pragma region Update&DrawFunctions

	void UpdateWithCollision(const std::vector<Props>& propsList)
	{
		for (auto& props : propsList)
		{
			sf::FloatRect sorceressBounds = plate.getGlobalBounds(); // Position of hitbox(sorceress)
			sf::FloatRect propsPlateBounds = props.GetPlateBounds(); // Position of hitbox(current props)

			// Finding from which direction we have colliіion
			// Перевірте чи існує зіткнення по X
			bool collisionX = sorceressBounds.left < propsPlateBounds.left + propsPlateBounds.width &&
				sorceressBounds.left + sorceressBounds.width > propsPlateBounds.left;

			// Перевірте чи існує зіткнення по Y
			bool collisionY = sorceressBounds.top < propsPlateBounds.top + propsPlateBounds.height &&
				sorceressBounds.top + sorceressBounds.height > propsPlateBounds.top;

			if (collisionX && collisionY)
			{
				// Перевірка сторони по Y
				if (sorceressBounds.top < propsPlateBounds.top && (sorceressBounds.left + sorceressBounds.width >= propsPlateBounds.left || sorceressBounds.left <= propsPlateBounds.left + propsPlateBounds.width))
				{
					// Зіткнення зверху
					if (direction)
						sprite.setPosition(sorceressBounds.left + 15, propsPlateBounds.top - sorceressBounds.height + 2.5);
					else
						sprite.setPosition(sorceressBounds.left + sorceressBounds.width - 15, propsPlateBounds.top - sorceressBounds.height + 2.5);
				}
				else if (sorceressBounds.top > propsPlateBounds.top + propsPlateBounds.height - 2 && (sorceressBounds.left + sorceressBounds.width >= propsPlateBounds.left || sorceressBounds.left <= propsPlateBounds.left + propsPlateBounds.width))
				{
					// Зіткнення знизу
					if (direction)
						sprite.setPosition(sorceressBounds.left + 15, propsPlateBounds.top + propsPlateBounds.height + 2.5);
					else
						sprite.setPosition(sorceressBounds.left + sorceressBounds.width - 15, propsPlateBounds.top + propsPlateBounds.height + 2.5);
				}
				// Перевірка сторони по X
				else if (sorceressBounds.left < propsPlateBounds.left)
					// Зіткнення зліва
					sprite.setPosition(propsPlateBounds.left - sorceressBounds.width + 15, sorceressBounds.top + 2.5);
				else if (sorceressBounds.left > propsPlateBounds.left)
					// Зіткнення справа
					sprite.setPosition(propsPlateBounds.left + propsPlateBounds.width + sorceressBounds.width - 15, sorceressBounds.top + 2.5);
			}
		}
	}

	void UpdateDrawPriority(sf::RenderWindow& window, const std::vector<Props>& propsList, Wizard& wizard)
	{
		// We will go through every Props and if we below it - draw priority will increase to Sorceress
		for (auto& props : propsList)
			if (props.GetPlateBounds().top > plate.getGlobalBounds().top && (!props.GetPlateSprite().getSize().x == 0)) props.Draw(window);

		if (!CheckCollisionWithWizard(wizard) && wizard.GetCurrentReplicaCount() <= 8) wizard.Draw(window);
	}

	void UpdatePlatePosition()
	{
		sf::Vector2f position = sprite.getPosition();
		if (currentSize > 4.0f) // To correctly change Collision rectangle
			plate.setPosition(position.x, position.y + 60);
		else
			plate.setPosition(position.x, position.y + 15);

		if (direction) // Saves the view direction of the player
			plate.setOrigin(plate.getLocalBounds().width / 2 - 20, plate.getLocalBounds().height / 2);
		else
			plate.setOrigin(plate.getLocalBounds().width / 2 + 20, plate.getLocalBounds().height / 2);
	}

	void DrawSorceress(sf::RenderWindow& window, const std::vector<Props>& propsList, Wizard& wizard)
	{
		// Handle Changes
		Animation();
		Movement();
		UpdatePlatePosition();
		UpdateWithCollision(propsList);
		UpdateIsTalking(wizard);

		// and than draw tham
		//Priority Test
		//window.draw(test);
		window.draw(sprite);
		window.draw(plate);
	}

	void UpdateIsTalking(Wizard& wizard) {	if (wizard.GetCurrentReplicaCount() == 9) ChangeIsTalking(false); }

	#pragma endregion

	#pragma region Animations

	void Animation()
	{
		cFrame += 0.0045f; // Responsible for animation speed
		if (cFrame > 9) cFrame -= 9; // Here we have num of diff pic in SpriteList

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			direction = false;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			direction = true;

		if (direction)
			sprite.setTextureRect(sf::IntRect(64 * static_cast<int>(cFrame), 0, 64, 64));
		else
			sprite.setTextureRect(sf::IntRect(64 * static_cast<int>(cFrame) + 64, 0, -64, 64));
	}

	#pragma endregion

	#pragma region MainFunctions

	void Movement()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && plate.getGlobalBounds().left + plate.getGlobalBounds().width + movelen < 960)
		{
			sprite.move(movelen, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && plate.getGlobalBounds().left - movelen > 0)
		{
			sprite.move(-movelen, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sprite.getGlobalBounds().top + movelen > 0)
		{
			sprite.move(0, -movelen);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sprite.getGlobalBounds().top + sprite.getGlobalBounds().height + movelen < 960)
		{
			sprite.move(0, movelen);
		}

		if (hasTalked && !isTalking)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
			{
				sf::Vector2f scale = sprite.getScale();
				if (currentSize + 0.1f <= 9.0f)
				{
					sprite.setScale(scale.x * 1.01f, scale.y * 1.01f);
					plate.setScale(scale.x * 0.355f, scale.y * 0.355f);
					currentSize += 0.1f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
			{
				sf::Vector2f scale = sprite.getScale();
				if (currentSize - 0.1f >= -6.0f)
				{
					sprite.setScale(scale.x * 0.99f, scale.y * 0.99f);
					plate.setScale(scale.x * 0.475f, scale.y * 0.475f);
					currentSize -= 0.1f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
			{
				currentSize = 2.0f;
				sprite.setScale(currentSize, currentSize);
				plate.setScale(1.0f, 1.0f);
			}
		}
		SizeDamege(); // and right after we will handle damege
	}

	void GetDamage(int damage) { HP -= damage; damegeGet = true; pain.play(); }

	void SizeDamege()
	{
		static sf::Clock damegeClock;
		static const sf::Time damegeLimitTime = sf::seconds(3.5f); // it will set time for space between geting two damege

		if (damegeClock.getElapsedTime() >= damegeLimitTime)
		{
			if ((currentSize + 1.0f >= 9.0f || currentSize - 1.0f <= -6.0f) && HP > 0)
			{
				GetDamage(10);
				damegeGet = true;
			}

			damegeClock.restart();
		}
	}

	#pragma endregion

	#pragma region MetodsForColision

	bool CheckCollision(const Props& props) const
	{
		sf::FloatRect sorceressBounds = plate.getGlobalBounds();
		sf::FloatRect propsPlateBounds = props.GetPlateBounds();
		return sorceressBounds.intersects(propsPlateBounds);
	}

	bool CheckCollisionWithWizard(Wizard& wizard) const
	{
		sf::FloatRect sorceressBounds = plate.getGlobalBounds();
		sf::FloatRect propsPlateBounds = wizard.GetPlate().getGlobalBounds();
		return sorceressBounds.intersects(propsPlateBounds);
	}

	#pragma endregion
};