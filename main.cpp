#include <iostream>
#include <vector>

#include <getopt.h>

using namespace std;
vector<string>* handled_options = new vector<string>();

void Help()
{
    cout << "Option --help was used" << endl;
}

void Version()
{
    cout << "Current version of application is 1.0" << endl;
}

void Input(char *arg)
{
    cout << "Your input: " << arg << endl;
}

void Size(char *arg)
{
    if(arg == nullptr)
    {
        cout << "You have used size option without value" << endl;
    }
    else
    {
        cout << "You have used size option with value: " << arg << endl;
    }
}


bool isAlreadyHandled(const std::string& option_name)
{
    for(auto &argument : *handled_options)
    {
        if (option_name == argument)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    int current_option;

    const char* short_options = "hvi:s::";

    struct option long_options[] = {
            {"help",    no_argument, nullptr, 'h'},
            {"version", no_argument, nullptr, 'v'},
            {"input",  required_argument, nullptr, 'i'},
            {"size", optional_argument, nullptr, 's'},
            {nullptr, 0, nullptr, 0}
    };

    int option_index = 0;

    while((current_option = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
    {
        string option_name;

        for(struct option &element : long_options)
        {
            if(element.val == current_option)
            {
                option_name = element.name;
                break;
            }
        }

        if(!(option_name.empty()) && isAlreadyHandled(option_name))
        {
            continue;
        }
        handled_options->push_back(option_name);

        switch(current_option)
        {
            case 'h':
                Help();
                break;

            case 'v':
                Version();
                break;

            case 'i':
                Input(optarg);
                break;

            case 's':
                Size(optarg);
                break;

            case '?':
                break;

            default:
                abort();
        }
    }

    return 0;
}
