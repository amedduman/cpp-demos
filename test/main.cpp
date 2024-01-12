#include <iostream>
#include <vector>
#include <fstream>

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

    ofstream outputFile("data.txt", ios::app);
    outputFile << "my name" << " " << 123 << endl;


    while (true)
    {
        cout << "load save add quit print" << endl;

        char command;
        cin >> command;

        Data data("no name", -1);

        switch (command)
        {
        case 'l':
            cout << "LOAD SELECTED" << endl;

            break;
        case 's':
            cout << "SAVE SELECTED" << endl;

            for(auto& d : dataVector)
            {
                outputFile << "Name: " << d.name << endl;
                outputFile << "Value " << d.value << endl;
            }

            break;
#pragma region
        case 'a':
            cout << "ADD SELECTED" << endl;

            cout << "enter a name: ";
            cin >> data.name;

            cout << "enter a value: ";
            cin >> data.value;

            dataVector.push_back(data);
            break;
#pragma endregion
#pragma region
        case 'p':
            cout << "PRINT SELECTED" << endl;

            for(auto& d : dataVector)
            {
                cout << "Name: " << d.name << endl;
                cout << "Value " << d.value << endl;
            }
            break;
#pragma endregion
#pragma region
        case 'q':
            return 0;
            break;
#pragma endregion
#pragma region
        default:
            cout << "command is not recognized" << endl;
            break;
#pragma endregion
        }
    }

}