
//To disable min max functions in termcolor.hpp. Otherwise it will pollute global namespace
#define NOMINMAX

//Necessary headers
#include <iostream>
#include "Random.h"
#include <string>
#include <string_view>
#include <algorithm>
#include <cctype>
#include <chrono>
#include "termcolor.hpp"
#include <limits>


//Gets input from user on difficulty of the game. Returns the number of chances as int
int getChancesInput()
{
	while (true)
	{
		std::string str{};


		std::cout 
			<< termcolor::on_blue << termcolor::bright_white 
			<< "Difficulty of the game (easy/medium/hard): " 
			<< termcolor::reset;


		std::cin >> str;

		std::transform
		(
			str.begin(),
			str.end(),
			str.begin(),
			[](unsigned char c) {return std::tolower(c);}
		);

		if (str == "easy")
			return 10;
		if (str == "medium")
			return 5;
		if (str == "hard")
			return 3;
	}
}


//Used to pause and wait for enter input. 
//Otherwise the console will be wiped before the player sees ending messages
void gamePause() {


	// Discard anything left over from previous input


	std::cin.clear();   // clear error flags (e.g. from a failed extraction)


	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	std::cout << "Press Enter to continue...";


	std::cin.get();     // now actually waits for the user
}


//Clears the console
void clearConsole() { std::cout << "\033[2J\033[H"; }


int main()
{
	while (true)
	{
		bool gameWon{ false };

		//generate answer value
		int answer{ Random::get(1, 100) };

		//number of chances for the player
		int chances{ getChancesInput() };

		clearConsole();

		static int highscore{chances};
		//Get value of chances from this input loop

		std::cout << termcolor::bright_green << "Let's start the game!\n\n\n" << termcolor::reset;

		//start timer
		auto start{ std::chrono::high_resolution_clock::now() };

		//Main game logic
		for (int attempts{ 1 }; attempts <= chances; ++attempts)
		{
			std::cout <<  "Enter your guess: ";
			int x{};
			std::cin >> x;

			if (x == answer)
			{
				//end timer
				auto end{ std::chrono::high_resolution_clock::now() };

				//calculate elapsed time in seconds
				auto elapsed{ std::chrono::duration_cast<std::chrono::seconds>(end - start) };

				if (attempts < highscore)
					highscore = attempts;
				//display congrats message with all info

				std::cout 
					<< termcolor::on_bright_green << termcolor::grey
					<< "Congratulations! You guessed the correct number in " << attempts << " attempts and took " << elapsed << " seconds.\n" 
					<< termcolor::reset;

				std::cout 
					<< termcolor::on_white << termcolor::grey 
					<< "The highscore is " << highscore << "\n\n" 
					<< termcolor::reset;

				gameWon = true;
				break;
			}
			else
			{
				std::cout << termcolor::red << "Incorrect! The number is " << (answer > x ? "more" : "less") << " than " << x << "\n\n" << termcolor::reset;
			}
		}

		gamePause();
		clearConsole();
		//ask player if they want to play again
		if (!gameWon) 
		{ 
			std::cout
				<< termcolor::on_bright_red << termcolor::white
				<< "You've run out of chances. Do you want to play again? (y/n): "
				<< termcolor::reset;
		}
		else
		{
			std::cout
				<< termcolor::on_yellow << termcolor::grey
				<< "Do you want to play again? (y/n): "
				<< termcolor::reset;
		}


		char c;
		std::cin >> c;

		clearConsole();

		//break the loop if they inputted n
		if (c == 'n')
			break;
	}
	
	return 0;
}