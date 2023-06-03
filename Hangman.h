//
// Created by Frederik Desmet on 03/06/2023.
//

#pragma once

#include <string>

class Hangman
{
public:
	Hangman();
	void play();
private:
	size_t _tries{};
	size_t _maxTries{};

	[[nodiscard]] size_t getTries() const;
	[[nodiscard]] size_t getMaxTries() const;
	size_t generateRandomNumber(size_t intmax);

	std::string _word{};
	std::string _hint{};
	std::string _guessed{};
	std::string _wrong{};

	std::string getWord();
	std::string getHint();
	std::string getGuessed();
	std::string getDrawing(size_t tries);

	void setWord(const std::string& word);
	void setHint(const std::string& hint);
	void setGuessed(char guessed);
	void drawHangman();
	void drawWord();
	void drawWrong();
	void drawTries();
	void draw();
	void guess();
	void reset();

	bool _isGuessed{};
	bool _isWrong{};
	bool _isCorrect{};
	bool _isGameOver{};
	bool _isGameWon{};

	std::vector<std::string> hangmanDrawing = {
		"+---+\n"
		"|   |\n"
		"    |\n"
		"    |\n"
		"    |\n"
		"    |\n"
		"=======",

		"+---+\n"
		"|   |\n"
		"O   |\n"
		"    |\n"
		"    |\n"
		"    |\n"
		"=======",

		"+---+\n"
		"|   |\n"
		"O   |\n"
		"|   |\n"
		"    |\n"
		"    |\n"
		"=======",

		" +---+\n"
		" |   |\n"
		" O   |\n"
		"/|   |\n"
		"     |\n"
		"     |\n"
		" ========",

		" +---+\n"
		" |   |\n"
		" O   |\n"
		"/|\\  |\n"
		"     |\n"
		"     |\n"
		" ========",

		" +---+\n"
		" |   |\n"
		" O   |\n"
		"/|\\  |\n"
		"/    |\n"
		"     |\n"
		" ========",

		" +---+\n"
		" |   |\n"
		" O   |\n"
		"/|\\  |\n"
		"/ \\  |\n"
		"     |\n"
		" ========",
	};
};
