#pragma once
#include <iostream>
#include <chrono>

class FrameTimer
{
public:
    FrameTimer()
    {
        last = std::chrono::high_resolution_clock::now();
    }

    float DeltaTime()
    {
        if(firstCall)
        {
            firstCall = false;
            return 0;
        }
        const auto old = last;
        last = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<float> duration = last - old;
        return duration.count();
    }
private:
    std::chrono::time_point<std::chrono::steady_clock> last;
    bool firstCall = true;;
};