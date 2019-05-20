#include <iostream>
#include <string>

int main()
{
    using std::cout;
    using std::cin;
    using std::string;

    cout << "Select option:" << "\n";
    cout << "1 - to capture image from camer" << "\n";
    cout << "2 - to read image from file" << "\n";
    char mode{'1'};
    cin >> mode;

    if(mode == '1')
    {

    }
    else if(mode == '2')
    {
        cout << "Provide path to image file." << "\n";
        cin.ignore(32767, '\n');
        string path{" "};
        std::getline(cin, path);

    }

    return 0;
}