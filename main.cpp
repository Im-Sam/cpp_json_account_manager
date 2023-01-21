#include <iostream>
#include <ostream>
#include <fstream>
#include <C:\Users\Sam\Documents\C\required\json.hpp>

using json = nlohmann::json;
using namespace std;

namespace Color
{
    enum Code
    {
        FG_RED = 31,
        FG_GREEN = 32,
        FG_BLUE = 34,
        FG_YELLOW = 33,
        FG_MAGENTA = 35,
        FG_DEFAULT = 39
    };
    class Modifier
    {
        Code code;

    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream &
        operator<<(std::ostream &os, const Modifier &mod)
        {
            return os << "\033[" << mod.code << "m";
        }
    };
}

void add_to_json(json &j)
{
    string input1, input2, input3;
    cout << setw(25) << "Enter the Account Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input1);
    cout << setw(25) << "Enter the Email: ";
    getline(cin, input2);
    cout << setw(25) << "Enter the Password: ";
    getline(cin, input3);

    json new_entry = {{"Account", input1}, {"Email", input2}, {"Password", input3}};
    j.push_back(new_entry);
}

void write_to_file(json &j)
{
    ofstream json_file("strings.json");
    json_file << j;
    json_file.close();
    cout << "\nStrings added successfully" << endl;
}

void show_json_arrays(json &j)
{
    cout << "\n"
         << j.dump(4) << endl
         << "\n";
}

void delete_json_array(json &j)
{
    int index;
    cout << "Enter the index of the array to delete: ";
    cin >> index;
    j.erase(j.begin() + index);
    cout << "Array deleted successfully" << endl;
    ofstream json_file("strings.json");
    json_file << j;
    json_file.close();
}

int main()
{
    Color::Modifier def(Color::FG_DEFAULT), red(Color::FG_RED), green(Color::FG_GREEN), blue(Color::FG_BLUE), magenta(Color::FG_MAGENTA), yellow(Color::FG_YELLOW);

    json json_arrays;
    ifstream json_file("strings.json");
    if (json_file.good())
    {
        json_file >> json_arrays;
    }
    json_file.close();

    while (true)
    {
        cout << blue << string(29, '\xC4') << " MENU " << string(29, '\xC4') << def << endl;
        cout << green << "1. Add strings" << endl;
        cout << green << "2. Show strings" << endl;
        cout << green << "3. Delete strings" << endl;
        cout << red << "4. Exit" << endl;
        cout << blue << string(64, '\xC4') << yellow << endl;
        int choice;
        cin >> choice;
        cout << def;

        switch (choice)
        {
        case 1:
            cout << "\033c";
            cout << blue << string(25, '\xC4') << " Save Account " << string(25, '\xC4') << magenta << endl;
            add_to_json(json_arrays);
            write_to_file(json_arrays);
            break;
        case 2:
            cout << "\033c";
            cout << blue << string(24, '\xC4') << " Saved Accounts " << string(24, '\xC4') << magenta << endl;
            show_json_arrays(json_arrays);
            break;
        case 3:
            cout << "\033c";
            delete_json_array(json_arrays);
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }

    return 0;
}
