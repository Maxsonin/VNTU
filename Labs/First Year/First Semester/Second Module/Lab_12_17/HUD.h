#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Sorceress.h"

class HUD
{
private:
	// Element to work with Task Menu
	sf::Font fontForHead;
	sf::Font fontForText;
	sf::Text HeadText;
	sf::Text mainText;

	sf::Music scrollSound;
	bool isSoundPlayed = false;

	sf::Texture scrollTexture;
	sf::Sprite scrollSprite;

	// To work with Helth
	sf::Texture HPTextur;
	sf::Sprite HPSprite;
	sf::RectangleShape healthRect;
	int CurHP;

	sf::RectangleShape painEffect;

	sf::RectangleShape EndScreen;
	sf::Text EndText;
	sf::Music die;
	bool deadDoundPlayed = false;

public:
	#pragma region Constructors

	HUD()
	{
		// Scroll
		scrollSound.openFromFile("Resources/scrolls.mp3");
		scrollTexture.loadFromFile("Resources/scrollf.png");
		scrollSprite.setTexture(scrollTexture);
		scrollSprite.setTextureRect(sf::IntRect(0, 0, 618, 825));
		scrollSprite.setPosition(170.0f, 50.0f);

		// Text for Scroll
		fontForHead.loadFromFile("Resources/fonth.ttf");
		HeadText.setFont(fontForHead);
		HeadText.setFillColor(sf::Color::Black);
		HeadText.setString(L"Завдання:");
		HeadText.setPosition(270.0f, 250.0f);
		
		fontForText.loadFromFile("Resources/fontm.ttf");
		mainText.setFont(fontForText);
		mainText.setFillColor(sf::Color::Black);
		mainText.setCharacterSize(30);

		// Health Bar
		HPTextur.loadFromFile("Resources/HPBar.png");
		HPSprite.setTexture(HPTextur);
		HPSprite.setScale(1.5f, 1.5f);
		HPSprite.setPosition(500, 10);
		healthRect.setSize(sf::Vector2f(150, 60)); // - 30
		healthRect.setPosition(570, 49);
		healthRect.setFillColor(sf::Color(53, 240, 36)); // Lime

		// Damage Effect
		painEffect.setFillColor(sf::Color(255, 0, 0, 80));
		painEffect.setSize(sf::Vector2f(1000, 1000));

		// Die
		EndScreen.setFillColor(sf::Color(0, 0, 0));
		EndScreen.setSize(sf::Vector2f(1000, 1000));
		EndText.setFillColor(sf::Color::White);
		EndText.setString("YOU DIED");
		EndText.setFont(fontForHead);
		EndText.setPosition(390, 400);
		die.openFromFile("Resources/die.mp3");
	}

	#pragma endregion

	#pragma region TasksScroll

	void UpdateTusks(Sorceress& sorceress)
	{
		mainText.setString(L"1. Поговорити з\n   чарівником");
		mainText.setPosition(295.0f, 290.0f);
	}

	void DrawTasks(sf::RenderWindow& window, Sorceress& sorceress)
	{
		if (!sorceress.IsTalking() && sorceress.Alive())
		{
			if (sorceress.HasTalkedToWizard())
			{
				mainText.setStyle(sf::Text::Style::StrikeThrough);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
			{
				// Work with sounds
				if (!isSoundPlayed) scrollSound.play();
				isSoundPlayed = true; 
				// Task Show
				UpdateTusks(sorceress);
				window.draw(scrollSprite);
				window.draw(HeadText);
				window.draw(mainText);
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
			{
				isSoundPlayed = false;
			}
		}
	}

	#pragma endregion

	#pragma region ForWorkWithHP

	void HandleHUD(sf::RenderWindow& window, Sorceress& sorceress)
	{
		DrawTasks(window, sorceress);
		DrawHPBar(window, sorceress);
		DamageEffect(window, sorceress);
		DieScreen(window, sorceress);
	}

	void UbdateHPBar(Sorceress& sorceress)
	{
		CurHP = 350.0f - (100 - sorceress.GetCurrentHP()) * 3;
		healthRect.setSize(sf::Vector2f(CurHP, 60));
		if (CurHP > 160 && CurHP < 280)
		{
			healthRect.setFillColor(sf::Color::Yellow);
		}
		else if(CurHP <= 160)
		{
			healthRect.setFillColor(sf::Color::Red);
		}
	}

	void DrawHPBar(sf::RenderWindow& window, Sorceress& sorceress)
	{
		UbdateHPBar(sorceress);

		window.draw(healthRect);
		window.draw(HPSprite);
	}

	void DamageEffect(sf::RenderWindow& window, Sorceress& sorceress)
	{
		static sf::Clock damageEffectClock;

		if (sorceress.DamegeGet())
		{
			static const sf::Time damageDurationTime = sf::seconds(0.4f);

			if (damageEffectClock.getElapsedTime() <= damageDurationTime)
			{
				window.draw(painEffect);
			}
			else
			{
				sorceress.ChangeDamegeGet(false);
				damageEffectClock.restart();
			}	
		}
		else
		{
			damageEffectClock.restart();
		}
	}

	void DieScreen(sf::RenderWindow& window, Sorceress& sorceress)
	{
		if (sorceress.GetCurrentHP() <= 0)
		{
			window.draw(EndScreen);
			window.draw(EndText);
			if (!deadDoundPlayed)
			{
				die.play();
				deadDoundPlayed = true;
			}
		}
	}

	#pragma endregion
};