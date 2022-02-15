#include <iostream>
#include <string>
#include <random>

/*
ABOUT:	
	This is the classic number guessing game.  Given a range, 1 - 10 (inclusive) for example, a random number is chosen in the range 
of the numbers.  The user needs to guess what number is chosen.  If incorrect, the user is told wether the random number is less or 
greater than the number guessed.  If correct, a "You win" message is shown and user is taken back to the main menu.  The number of 
guesses is tracked for a "score."

NOTES:
	- This was created for my YouTube channel for a easy game series.  It is NOT intended to be the best and best way to do 
	any of this.  It is for entertainment purposes only
	- This was written in MSVS 2022.  It may compile on other platforms with other compilers.  I have not tested but as simple
	as this is, it should work with any C++ compiler and platform with a console window. 
	- I took some time to make sure all input is validated for what the program is expecting.  Probably didn't think of everything.

LICENSE:
???
*/

// Empties out std::cin and clears any error flags
void ResetStdCin(void)
{
	// Clear and errors in std::cin
	std::cin.clear();
	// Clear out std::cin
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


// Prints out the Main Menu and returns the users choice
std::string MainMenu(void)
{
	// The user choice when input
	std::string input;

	// The user choice in a meaningful way
	std::string mode;

	// Print the main menu
	std::cout << "Guess The Number!" << std::endl;

	std::cout << "Choose your difficulty:" << std::endl;
	std::cout << "1 - Easy (1 - 10)" << std::endl;
	std::cout << "2 - Medium (1 - 50)" << std::endl;
	std::cout << "3 - Hard (1 - 100)" << std::endl;
	std::cout << "0 - Quit" << std::endl;

	std::cout << std::endl << "Choice (1, 2, 3, or 0): ";

	// Get input from user
	std::cin >> input;

	// Check for valid input
	if (std::cin.peek() != '\n')
	{
		mode = "Invalid";
	}
	else if (input.compare("1") == 0)
	{
		mode = "Easy";
	}
	else if (input.compare("2") == 0)
	{
		mode = "Medium";
	}
	else if (input.compare("3") == 0)
	{
		mode = "Hard";
	}
	else if (input.compare("0") == 0)
	{
		mode = "Quit";
	}
	else
	{
		mode = "Invalid";
	}

	// Clear out anything left in std::cin
	ResetStdCin();

	// Output what the user chose.
	std::cout << std::endl << "You chose " << mode << std::endl;

	// Return the user choice
	return mode;
}

// Generates a random number between minimum and maximum inclusive
unsigned int GenerateRandomNumber(const unsigned int minimum, const unsigned int maximum)
{
	unsigned int randomNumber = std::rand() % maximum + minimum;
	return randomNumber;
}

// Prompt user for input for the game and return it
unsigned int GetUserInputPromptForGame(const unsigned int guesses, const unsigned int minimumNumber, const unsigned int maximumNumber)
{
	// Number input for guess by user
	unsigned int userGuess = 0;

	// Print out the guess prompts
	std::cout << "Guesses so far: " << guesses << std::endl;
	std::cout << "Choose a number between " << minimumNumber << " and " << maximumNumber << ". Enter 0 (zero) to quit: ";
	
	// Get user input for guess
	std::cin >> userGuess;

	// Check if more than a number was entered
	if (std::cin.peek() != '\n')
	{
		// Return a bad input flag
		userGuess = 999999;
		
		// Clear out anything left in std::cin
		ResetStdCin();

		// Decoration thing
		std::cout << std::endl;
		return userGuess;
	}

	// Clear the std::cin stream
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Check for valid input (non integer number)
	if (std::cin.fail())
	{
		// Clear out anything left in std::cin
		ResetStdCin();
		// Return a bad input flag
		userGuess = 999999;
	}

	// Just a decoration thing
	std::cout << std::endl;

	return userGuess;
}

// Play the actual game
void PlayGame(const unsigned int numberToGuess, const unsigned int minimumNumber, const unsigned int maximumNumber)
{
	// Number of guesses user has used
	int numberOfGuesses = 0;
	// Is the game still going?
	bool isGamePlaying = true;
	// Guess input from user
	unsigned int guess = 0;

	// Game loop
	do
	{
		// Get the guess input from the user
		guess = GetUserInputPromptForGame(numberOfGuesses, minimumNumber, maximumNumber);

		// Handle bad input
		if (guess == 999999)
		{
			std::cout << "Please enter a valid number." << std::endl;
			continue;
		}
		// Handle if user wants to quit
		if (guess == 0)
		{
			return;
		}
		
		// Increase guess count
		numberOfGuesses++;
		
		// Check if user guessed correctly
		if (guess == numberToGuess)
		{
			std::cout << "YOU WIN!" << std::endl;
			std::cout << "You guessed the correct number, " << numberToGuess << ", in " << numberOfGuesses << " guesses!" << std::endl;
			std::cout << std::endl;
			
			// We are done playing
			isGamePlaying = false;
		}
		// Check if user's guess is less than the number to guess
		else if (guess < numberToGuess)
		{
			std::cout << guess << " is NOT the number!  The number is greater than that!  Try again!" << std::endl;
		}
		// Check if user's guess is greater than the number to guess
		else if (guess > numberToGuess)
		{
			std::cout << guess << " is NOT the number!  The number is less than that!  Try again!" << std::endl;
		}

	} while (isGamePlaying);
}

int main(void)
{
	// User inputted choice
	std::string choice;
	// Was user choice a valid choice
	bool isValidChoice = false;
	// Minimum number for random generation
	unsigned int minimumNumber = 0;
	// Maximum number for random generation
	unsigned int maximumNumber = 0;
	// Randomly generated number to guess
	unsigned int numberToGuess = 0;

	// Get the system time for random-ish seed 
	time_t seed = std::time(0);
	// Actually seed the randomize with system time
	std::srand(static_cast<unsigned int>(seed));

	// Infinite game loop until user quits
	do
	{
		// Get menu choice from user
		do
		{
			choice = MainMenu();
			
			// Is the user choice valid?
			if (choice.compare("Invalid") == 0)
			{
				std::cout << "Please enter a valid choice." << std::endl << std::endl;
			}
			else
			{
				isValidChoice = true;
			}
		} while (!isValidChoice);

		// Process the user's choice
		if (choice.compare("Quit") == 0)
		{
			// User wants to quit, tell them bye and quit the game
			std::cout << "Thanks for playing! Bye!" << std::endl;
			return 0;
		}
		else if (choice.compare("Easy") == 0)
		{
			// User chose easy which is a number between 1 and 10
			minimumNumber = 1;
			maximumNumber = 10;
		}
		else if (choice.compare("Medium") == 0)
		{
			// User chose medium which is a number between 1 and 50
			minimumNumber = 1;
			maximumNumber = 50;
		}
		else if (choice.compare("Hard") == 0)
		{
			// User chose hard which is a number between 1 and 100
			minimumNumber = 1;
			maximumNumber = 100;
		}

		// Generate the number to guess
		numberToGuess = GenerateRandomNumber(minimumNumber, maximumNumber);

		// Play the game
		PlayGame(numberToGuess, minimumNumber, maximumNumber);
	} while (true);

	return 0;
}