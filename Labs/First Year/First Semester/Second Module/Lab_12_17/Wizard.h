#pragma once

#include <SFML/Graphics.hpp>

class Wizard
{
private:
	sf::Texture bodyTexture;
	sf::Sprite sprite;

	// Collision rectang
	sf::RectangleShape plate;

	// For animation
	float cFrame = 0;

	// Talk
	sf::Sprite spriteTextCloud;
	sf::Texture textureCloudSprite;
	sf::Font gameFont;
	sf::Text gameText;
	int replicaCount = 1;

	// For Vanish
	bool hasVanished = false;
	float cFrameV = 0;
public:
	#pragma region Constructors

	Wizard()
	{
		// Giving some form to the Wizard object
		bodyTexture.loadFromFile("Resources/animationWizard.png");
		sprite.setTexture(bodyTexture);
		sprite.setTextureRect(sf::IntRect(34 * static_cast<int>(cFrame) + 34, 162, -34, 34));
		sprite.setPosition(370, 325); // Set spawn position
		sprite.setScale(1.5f, 1.5f);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2); // Origin to center of Wizard

		// Making hitboxes
		plate.setSize(sf::Vector2f(60, 70));
		plate.setOrigin(plate.getLocalBounds().width / 2, plate.getLocalBounds().height / 2);
		plate.setPosition(sf::Vector2f(375, 380));
		plate.setFillColor(sf::Color(255, 0, 0, 0)); // To see hitboxs

		// Settings for Speech Cloud
		textureCloudSprite.loadFromFile("Resources/talkmanu.png");
		spriteTextCloud.setTexture(textureCloudSprite);
		gameText.setScale(sf::Vector2f(0.6f, 0.6f));

		// Font for Speech Cloud
		gameFont.loadFromFile("Resources/gamemain.ttf");
		gameText.setFont(gameFont);
		gameText.setFillColor(sf::Color::Black);
	}

	#pragma endregion

	#pragma region Geters&Setters

	sf::RectangleShape GetPlate() { return plate; }

	int GetCurrentReplicaCount() const { return replicaCount; }

	bool IsVenished() const { return hasVanished; }

	void SetCloudSpeech(sf::Vector2f CloudPosition = { 310, 240 }, sf::Vector2f CloudScale = { 0.4f, 0.4f }, sf::Vector2f textPosition = { 330, 250 })
	{
		spriteTextCloud.setPosition(CloudPosition);
		spriteTextCloud.setScale(CloudScale);
		gameText.setPosition(textPosition);
	}

	#pragma endregion

	#pragma region Animations

	void Animation()
	{
		cFrame += 0.003f; // Responsible for animation speed
		if (cFrame > 4) cFrame -= 4;
		sprite.setTextureRect(sf::IntRect(32 * static_cast<int>(cFrame) + 32, 34, -34, 32));
	}


	void Vanish(sf::RenderWindow& window)
	{
		if (cFrameV <= 5)
		{
			cFrameV += 0.005f; // Responsible for animation speed
			sprite.setTextureRect(sf::IntRect(32 * static_cast<int>(cFrameV) + 32, 162, -32, 32));

			if (cFrameV == 5) { hasVanished = true; } // It will mean that it's end of animation
			else
			{
				// Else we will just draw animation
				window.draw(sprite);
				window.draw(plate);
			}
		}
	}

	#pragma endregion

	#pragma region MainFunctionsOfWizard

	void Talk(sf::RenderWindow& window)
	{
		if (replicaCount < 9)
		{
			static sf::Clock talkTimer;  // Static timer to save state between calls
			static const sf::Time talkTimeLimit = sf::seconds(3.5f);  // Length of each replicas

			if (talkTimer.getElapsedTime() < talkTimeLimit)
			{
				if (replicaCount == 1)
				{
					SetCloudSpeech();
					gameText.setString(L"І знову привіт!");
				}
				else if (replicaCount == 2)
				{
					SetCloudSpeech(sf::Vector2f(280, 210), sf::Vector2f(0.6f, 0.6f), sf::Vector2f(300, 225));
					gameText.setString(L"Думаю ти здогадуєшся\nчому я тебе зараз навчу");
				}
				else if (replicaCount == 3)
				{
					SetCloudSpeech(sf::Vector2f(270, 240), sf::Vector2f(0.62f, 0.4f), sf::Vector2f(300, 250));
					gameText.setString(L"Тому перейдемо до суті");
				}
				else if (replicaCount == 4)
				{
					SetCloudSpeech(sf::Vector2f(260, 240), sf::Vector2f(0.685f, 0.4f), sf::Vector2f(280, 250));
					gameText.setString(L"Щоб збільшитись натисни '+'");
				}
				else if (replicaCount == 5)
				{
					SetCloudSpeech(sf::Vector2f(285, 240), sf::Vector2f(0.53f, 0.4f), sf::Vector2f(315, 250));
					gameText.setString(L"Щоб зменшитись - '-'");
				}
				else if (replicaCount == 6)
				{
					SetCloudSpeech(sf::Vector2f(260, 240), sf::Vector2f(0.685f, 0.4f), sf::Vector2f(285, 250));
					gameText.setString(L"Щоб відновити розмір - '0'");
				}
				else if (replicaCount == 7)
				{
					SetCloudSpeech(sf::Vector2f(270, 240), sf::Vector2f(0.67f, 0.4f), sf::Vector2f(295, 250));
					gameText.setString(L"Easy peasy Lemon squeezy!");
				}
				else if (replicaCount == 8)
				{
					SetCloudSpeech(sf::Vector2f(310, 240), sf::Vector2f(0.45f, 0.4f), sf::Vector2f(330, 250));
					gameText.setString(L"Ще зустрінемось!");
				}
				window.draw(spriteTextCloud);
				window.draw(gameText);
			}
			else
			{
				replicaCount++; // Change replica
				talkTimer.restart();
			}
		}
	}

	#pragma endregion

	#pragma region DrawWizard

	void Draw(sf::RenderWindow& window)
	{
		Animation();

		window.draw(sprite);
		window.draw(plate);
	}

	#pragma endregion
};
