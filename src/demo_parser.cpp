#include "demo_parser.hpp"
using namespace demo_parser;

int main(int argc, char* argv[])
{
    for (auto i = 1; i < argc; i++)
    {
        const std::filesystem::path file(argv[i]);
        if (file.extension() != ".dem")
        {
            printf("Invalid file %s\n", argv[i]);
            continue;
        }

        std::ifstream input(file);
        if (input.is_open())
        {
            auto* demo = new srcdemo(input);
            printf("servername: %s\n", demo->server);
            demo->analyse();


            delete demo;
        }
    }

    return 0;
}