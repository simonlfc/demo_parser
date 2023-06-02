#include "demo_parser.hpp"

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
            const auto* demo = new demo_parser::demo(input);
            printf("%s on %s for %s at %i tickrate", demo->header.map, demo->header.server, demo->duration.c_str(), demo->tickrate);
        }
    }

    return 0;
}
