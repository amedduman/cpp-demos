#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <numeric>

////////////////////////////////////////////////////////////////////////////
//     !! HOMEWORK !!
// use the C++ <algorithms> as extensively as you can for these problems!

// you may not modify this
struct Pube
{
	int num;
	std::string str;
	bool operator<( const Pube& rhs ) const
	{
		return num < rhs.num;
	}
	operator int() const
	{
		return num;
	}
};

// write your remove_erase_if template function here!

// write your custom insertion operator here!

int main()
{
	// materiel (do not modify!)
	const std::vector<Pube> numbers = {
		{ 0,"zero" },
		{ 9,"nine" },
		{ 7,"seven" },
		{ 2,"two" },
		{ 8,"eight" },
		{ 3,"three" },
		{ 4,"four" },
		{ 1,"one" },
		{ 6,"six" },
		{ 5,"five" }
	};
	const std::vector<Pube> memes = {
		{ 3,"dat boi" },
		{ 1,"yaaaas" },
		{ 3,"soviet russia" },
		{ 1,"damn daniel" },
		{ 1,"hipster ariel" },
		{ 3,"harambe" },
		{ 2,"doge" },
		{ 3,"cash me outside" },
		{ 2,"henlo" },
		{ 3,"kappa" }
	};
	const std::string nambies = "eight one six eight three three eight five four two nine six nine";
	const std::string numpies = { 6, 6, 5, 0, 6, 1, 8, 6 };

	// Problem 1:
	// create a vector that contains 4 copies of each of the elements of memes
	// sort it first by number descending (score from 3 to 1) and then name ascending
	// output sorted meme list w/ score and name using custom insertion operator
	std::cout << "<< Sort Memes >>" << std::endl;
	{
		// code goes here
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 2:
	// output nambies as string of digits without spaces
	// (can be done in single statement!)
	std::cout << "<< Number Words to Digits >>" << std::endl;
	{
		// code goes here
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 3:
	// output numpies as a string of words separated by spaces
	// don't use std::find_if or other searches
	std::cout << "<< Digits to Number Words >>" << std::endl;
	{
		// code goes here
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 4:
	// find the product of all numbers in nambies
	// and output of course
	std::cout << "<< Product >>" << std::endl;
	{
		// code goes here
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 5:
	// find sums of corresponding nums in numbers and memes
	// output as comma separated list
	std::cout << "<< Parallel Sum >>" << std::endl;
	{
		// code goes here
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 6:
	// write a template function (not here, above int main())
	// that will remove elements from vector based on unary predicate
	// the following code should not be modified
	std::cout << "<< Top Memes >>" << std::endl;
	{
		// copy to get non-const vector
		auto maymays = memes;
		// remove all memes with score below 3
		remove_erase_if( maymays,[]( const Pube& p ) { return p.num < 3; } );
		// output results
		std::copy( maymays.begin(),maymays.end(),std::ostream_iterator<Pube>( std::cout,"\n" ) );
	}
	std::cout << "============================================" << std::endl << std::endl;

	std::cin.get();
	return 0;
}