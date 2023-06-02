#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>

struct demoheader_s
{
    char header[8];
    std::int32_t demo_protocol;
    std::int32_t net_protocol;
    char server[260];
    char client[260];
    char map[260];
    char gamedir[260];
    std::float_t playback_time;
    std::int32_t playback_ticks;
    std::int32_t playback_frames;
    std::int32_t signon_length;
};

namespace demo_parser
{
    class srcdemo : public demoheader_s
    {
    public:
        std::ifstream input;
        std::int32_t tickrate;

        srcdemo(std::ifstream& input)
        {
            input.read((char*)&header, sizeof(demoheader_s));
            tickrate = static_cast<std::int32_t>(playback_ticks / playback_time);
        }

        void analyse()
        {
            // protobuf ill see you another day
            printf("analysing...\n");
        }
    };
};