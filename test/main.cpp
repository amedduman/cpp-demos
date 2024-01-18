#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <random>

// ANSI escape codes for text styles
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

bool IsVectorContainWord(const std::vector<std::string>& vec, const std::string& word)
{
    for(auto& w : vec)
    {
        if(w == word)
            return true;
    }
    return false;
}
bool IsWordContainsLetter(const std::string& word, const char letter)
{
    for (const char& c : word)
    {
        if(c == letter)
            return true;
    }
    return false;
}


int main()
{
    using namespace std;

    std::cout << BOLD << "Bold Text" << RESET << std::endl;

    vector<string> words;
    ifstream wordsFile("../sgb-words.txt");

    for(string line; getline(wordsFile, line);)
    {
        if(line.empty()) continue;
        words.push_back(line);
    }

    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<int> distribution(0, static_cast<int>(words.size()) - 1);

    int randomIndex = distribution(engine);
    const string answer = words[randomIndex];
    cout << "DEBUG: " << answer << endl;
    cout << "Guess the word" << endl;
    while (true)
    {
        string input;
        cin >> input;
        for (char& c : input)
        {
            c = std::tolower(c);
        }
        if(input.size() != 5)
        {
            cout << "your anser should be 5 letters long" << endl;
            continue;
        }
        if(IsVectorContainWord(words, input) == false)
        {
            cout << "your anser is not a valid word" << endl;
            continue;
        }
        for (int i = 0; i < input.size(); ++i)
        {
            if(input[i] == answer[i])
            {
                char c = toupper(input[i]);
                cout << GREEN << c << RESET;
            }
            else if(IsWordContainsLetter(answer, input[i]))
            {
                char c = toupper(input[i]);
                cout << YELLOW << c << RESET;
            }
            else
            {
                char c = toupper(input[i]);
                cout << RED << c << RESET;
            }
        }
        cout << endl;
        if(input == answer)
        {
            cout << "YOU WIN" << endl;
            break;
        }
    }
}