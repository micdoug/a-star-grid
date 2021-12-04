#include "parsing.h"
#include <fstream>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <string_view>

std::optional<Grid> parse_grid_from_file(const std::string &file_path)
{
    std::ifstream input_file{file_path};
    if (!input_file)
    {
        std::cout << "Error while opening file: "
                  << strerror(errno)
                  << std::endl;
        return {};
    }

    std::vector<std::vector<bool>> grid_data;
    std::string line;
    while (std::getline(input_file, line))
    {
        std::vector<bool> line_data;
        size_t current_position = 0;
        while (current_position < line.size())
        {
            size_t sep_position = line.find(',', current_position);
            if (sep_position == -1)
            {
                std::cerr << "Invalid format at line " << grid_data.size() + 1 << std::endl;
                return {};
            }
            const auto value_str = line.substr(current_position, sep_position - current_position);
            current_position = sep_position + 1;

            int value;
            try
            {
                value = std::stoi(value_str);
            }
            catch (...)
            {
                std::cerr << "Invalid format at line " << grid_data.size() + 1 << std::endl;
                return {};
            }
            if (value == 1)
            {
                line_data.push_back(true);
            }
            else if (value == 0)
            {
                line_data.push_back(false);
            }
            else
            {
                std::cerr << "Invalid format at line " << grid_data.size() + 1 << std::endl;
                return {};
            }
        }

        grid_data.push_back(std::move(line_data));
    }
    return Grid{grid_data};
}