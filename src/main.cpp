#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>

#include "coordinator.hpp"

int main(const int argc, const char * const argv[])
{
    try
    {
        using namespace snake2;

        Config config;

        if (argc > 1)
        {
            config.media_path = std::filesystem::current_path() / std::filesystem::path{ argv[1] };
        }
        else
        {
            config.media_path = std::filesystem::current_path() / "media";
        }

        config.media_path = std::filesystem::canonical(config.media_path);

        if (!std::filesystem::exists(config.media_path))
        {
            throw std::runtime_error(
                "Error:  The media path does not exist! Put the media path on the command line or "
                "put the 'media' folder here.");
        }

        std::cout << "Using media folder: " << config.media_path.string() << std::endl;

        Coordinator coordinator;
        coordinator.run(config);
    }
    catch (const std::exception & ex)
    {
        std::cout << "Exception Error: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Exception Error: (non-standard exception)" << std::endl;
    }

    return EXIT_SUCCESS;
}