#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

struct Data
{
    std::string name;
    int value;

    Data(std::string in_name, int in_value)
    {
        name = in_name;
        value = in_value;
    }
};

int main()
{
    using namespace std;

    std::vector<Data> dataVector;
    ofstream outputFile("data.txt");


    while (true)
    {
        cout << "load save add quit print" << endl;

        char command;
        cin >> command;

        Data data("no name", -1);

        switch (command)
        {
        case 'l':
            {
                cout << "LOAD SELECTED" << endl;

                std::ifstream inputFile("data.txt");
                // Check if the file is successfully opened
                if (inputFile.is_open())
                {
                    std::string line;

                    // Read and print each line from the file
                    while (std::getline(inputFile, line))
                    {
                        std::istringstream inputStream(line);

                        std::string name;
                        int age;

                        std::getline(inputStream, name, ',');
                        inputStream >> age;

                        std::cout << "Name: " << name << std::endl;
                        std::cout << "Age: " << age << std::endl;
                    }
                }
            }
            break;
        case 's':
            cout << "SAVE SELECTED" << endl;

            for(auto& d : dataVector)
            {
                outputFile << d.name << ",";
                outputFile << d.value << endl;
            }

            break;
        case 'a':
            cout << "ADD SELECTED" << endl;

            cout << "enter a name: ";
            cin >> data.name;

            cout << "enter a value: ";
            cin >> data.value;

            dataVector.push_back(data);
            break;
        case 'p':
            cout << "PRINT SELECTED" << endl;

            for(auto& d : dataVector)
            {
                cout << "Name: " << d.name << endl;
                cout << "Value " << d.value << endl;
            }
            break;
        case 'q':
            return 0;
            break;
        default:
            cout << "command is not recognized" << endl;
            break;
        }
    }

}