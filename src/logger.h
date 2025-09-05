#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <chrono>

class logger {
    public:
        using high_resolution_clock = std::chrono::high_resolution_clock;
        using time_point = high_resolution_clock::time_point;

        logger(int total) : done(0), total(total) {}

        void start() {
            start_time = high_resolution_clock::now();
            progress = 0;
        }

        void tick() {
            auto progress_updated = int(100 * (done += 1) / total);

            if (progress != progress_updated) {
                progress = progress_updated;

                std::cout
                    << "\r[C++] pixels rendered = " << progress << "%"
                    << "\ttime = " << duration_time()
                    << std::flush;
            }
        }

        void end() {
            std::cout
                << "\n[C++] render completed in time " << duration_time()
                << std::endl;
        }

    private:
        int done;
        int total;
        int progress;
        time_point start_time;

        std::string duration_time() {
            const auto end_time = std::chrono::high_resolution_clock::now();
            const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

            auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration % std::chrono::hours(1)).count();
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration % std::chrono::minutes(1)).count();

            return std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
        };
};

#endif
