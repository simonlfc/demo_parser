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

enum commands
{
    signon = 1,
    packet,
    synctick,
    consolecmd,
    usercmd,
    datatables,
    stop,
    customdata,
    stringtables,
    lastcmd = stringtables
};

namespace demo_parser
{
    class srcdemo : public demoheader_s
    {
    public:
        std::int32_t tickrate;

        srcdemo(std::ifstream& in) : input(in)
        {
            input.seekg(0, std::ios::end);
            length = static_cast<std::uint32_t>(input.tellg());
            input.seekg(0, std::ios::beg);

            input.read(reinterpret_cast<char*>(&header), sizeof(demoheader_s));
            length -= sizeof(demoheader_s);
            tickrate = static_cast<std::int32_t>(playback_ticks / playback_time);
        }

        ~srcdemo()
        {
            input.close();
        }

        void analyse()
        {
            printf("analysing...\n");

            buffer.resize(length);
            input.read(buffer.data(), length);

            bool eof = false;
            while (!eof)
            {
                std::int32_t tick = 0;
                unsigned char cmd, playerslot;
                read_command_header(cmd, tick, playerslot);
                printf("command: %i, tick, %i, playerslot: %i\n", cmd, tick, playerslot);

                switch (cmd)
                {
                case commands::signon:
                case commands::packet:
                    break;
                case commands::synctick:
                    break;
                case commands::consolecmd:
                    break;
                case commands::usercmd:
                    break;
                case commands::datatables:
                    break;
                case commands::stop:
                    eof = true;
                    break;
                case commands::stringtables:
                    break;
                default:
                    break;
                }
            }
        }

    private:
        std::ifstream& input;
        std::string buffer;
        std::size_t pos = 0;
        std::uint32_t length;

        void read_command_header(unsigned char& cmd, std::int32_t& tick, unsigned char& playerslot)
        {
            cmd = buffer[pos++];

            if (cmd <= 0)
            {
                cmd = commands::stop;
                return;
            }

            tick = *reinterpret_cast<std::int32_t*>(&buffer[pos]);
            pos += sizeof(std::int32_t);

            playerslot = buffer[pos++];
        }
    };
};