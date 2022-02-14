#include <iostream>
#include <string>
#include <random>

// Prints out the Main Menu and returns the 
// users choice.
std::string MainMenu(void)
{
	// Holds the user choice when inputed
	unsigned char input = 0; 

	// Holds the user choice in a meaningful way
	std::string mode = "";

	// Print the main menu
	std::cout << "Guess The Number!" << std::endl;

	std::cout << "Choose your difficulty:" << std::endl;
	std::cout << "1 - Easy (1 - 10)" << std::endl;
	std::cout << "2 - Medium (1 - 50)" << std::endl;
	std::cout << "3 - Hard (1 - 100)" << std::endl;

	std::cout << std::endl << "Choice (1, 2, 3, or 'Q' to Quit): ";

	// Get input from user
	std::cin >> input;

	// Parse the input
	switch (input)
	{
	case '1': mode = "Easy"; break;
	case '2': mode = "Medium"; break;
	case '3': mode = "Hard"; break;
	case 'q':
	case 'Q': mode = "Quit"; break;
	default: mode = "Unknown"; break;
	}

	// Output what the user chose.
	std::cout << std::endl << "You chose " << mode << std::endl;

	// Return the user choice
	return mode;
}

unsigned int GenerateRandomNumber(const unsigned int minimum, const unsigned int maximum)
{
	unsigned int randomNumber = std::rand() % maximum + minimum;
	return randomNumber;
}

int main(void)
{
	std::string choice = "";
	bool validChoice = false;

	do
	{
		choice = MainMenu();
		if (choice.compare("Unknown") == 0)
		{
			std::cout << "Please enter a valid choice." << std::endl << std::endl;
			choice = "";
		}
		else
		{
			validChoice = true;
		}
	} while (!validChoice);

	if (choice.compare("Quit") == 0)
	{
		std::cout << "Thanks for playing! Bye!" << std::endl;
		return 0;
	}


	// Random tests
	time_t seed = std::time(0);
	unsigned int number = 0;
	std::srand(static_cast<unsigned int>(seed));
	unsigned int numMin = 0;
	unsigned int numMax = 0;

	if (choice.compare("Easy") == 0)
	{
		numMin = 1;
		numMax = 10;
	}
	else if (choice.compare("Medium") == 0)
	{
		numMin = 1;
		numMax = 50;
	}
	else if (choice.compare("Hard") == 0)
	{
		numMin = 1;
		numMax = 100;
	}

	for (int loop = 0; loop < 5; loop++)
	{
		number = GenerateRandomNumber(numMin, numMax);
		std::cout << "Random number = " << number << std::endl;
	}
	return 0;
}