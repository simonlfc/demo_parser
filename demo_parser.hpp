#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>

class demo_parser
{
private:
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

public:
    class demo
    {
    public:
        std::string duration;
        std::int32_t tickrate;
        demoheader_s header{};

        demo(std::ifstream& input)
        {
            input.read((char*)&header, sizeof(demoheader_s));

            duration = std::format("{:%T}", std::chrono::duration<float>(header.playback_time));
            tickrate = static_cast<std::int32_t>(header.playback_ticks / header.playback_time);
        }
    };
};