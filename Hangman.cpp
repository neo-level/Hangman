//
// Created by Frederik Desmet on 03/06/2023.
//

#include "Hangman.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <random>

#include "nlohmann/json.hpp"

Hangman::Hangman()
{
	_maxTries = 7;

	std::ifstream file("words.json");
	if (not file)
	{
		throw std::runtime_error("File not found");
	}

	nlohmann::json json{};
	file >> json;

	auto words = json["words"];
	size_t index = generateRandomNumber(words.size());
	setWord(words[index]["word"]);
	setHint(words[index]["hint"]);

	_guessed = std::string(getWord().size(), '_');
}
void Hangman::play()
{
	while (not _isGameOver)
	{
		guess();
		draw();
		if (_isGameWon)
		{
			std::cout << "You won!" << std::endl;
			std::cout << "do you want to play again? (y/n)" << std::endl;
			char answer{};
			std::cin >> answer;
			if (answer == 'y')
			{
				reset();
			}
			else
			{
				_isGameOver = true;
			}
			return;
		}
	}
}
std::string Hangman::getWord()
{
	return _word;
}
std::string Hangman::getHint()
{
	return _hint;
}
std::string Hangman::getGuessed()
{
	return _guessed;
}
std::string Hangman::getDrawing(size_t tries)
{
	return hangmanDrawing.at(tries);
}
size_t Hangman::getTries() const
{
	return _tries;
}
size_t Hangman::getMaxTries() const
{
	return _maxTries;
}
size_t Hangman::generateRandomNumber(size_t intmax)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, intmax);
	return dis(gen);
}

void Hangman::setWord(const std::string& word)
{
	_word = word;
}
void Hangman::setHint(const std::string& hint)
{
	_hint = hint;
}
void Hangman::setGuessed(const char guessed)
{
	if (getWord().find(guessed) != std::string::npos)
	{
		_isGuessed = true;
		return;
	}

	for (int letter{ 0 }; letter < getWord().size(); letter++)
	{
		if (letter == guessed)
		{
			_guessed.at(letter) = guessed;
			_isCorrect = true;
			if (getWord().find('_') == std::string::npos)
			{
				_isGameWon = true;
				_isGameOver = true;
			}
		}
	}

	if (not _isCorrect)
	{
		_isWrong = true;
	}
}
void Hangman::drawHangman()
{
	std::cout << getDrawing(getTries()) << std::endl;
}
void Hangman::drawWord()
{
	std::cout << "Word: " << getGuessed() << std::endl;
}
void Hangman::drawWrong()
{
	std::cout << "Wrong: " << _wrong << std::endl;
}
void Hangman::drawTries()
{
	std::cout << "Tries: " << getTries() << "/" << getMaxTries() << std::endl;
}
void Hangman::draw()
{
	drawHangman();
	drawWord();
	drawWrong();
	drawTries();
}
void Hangman::guess()
{
	char guess{};
	std::cout << "Guess a letter: ";
	std::cin >> guess;
	setGuessed(guess);

	if (_isGuessed)
	{
		std::cout << "You already guessed this letter" << std::endl;
		return;
	}
	if (_isCorrect)
	{
		std::cout << "Correct!" << std::endl;
		return;
	}
	if (_isWrong)
	{
		_wrong += guess;
		drawWrong();
		if (_tries == _maxTries)
		{
			_isGameOver = true;
			std::cout << "Game over!" << std::endl;
			return;
		}
		_tries++;
	}
}
void Hangman::reset()
{
	_isGameOver = false;
	_isGameWon = false;
	_isGuessed = false;
	_isCorrect = false;
	_isWrong = false;
	_tries = 0;
	_wrong = "";
	_guessed = std::string(getWord().size(), '_');
}
