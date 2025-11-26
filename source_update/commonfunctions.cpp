#include "commonfunctions.h"

void putProcess(double procedure, double time_used) {

    std::cout << std::fixed << std::setprecision(3) << "Processing: " << procedure * 100 << "%" \
            << "\t\tTime: " << timeFormatting(time_used).str() \
            << "\t\tEstimate remaining time: " << timeFormatting((1 - procedure) / procedure * time_used).str() << std::endl;
    
}

std::stringstream timeFormatting(double microSeconds) {

    std::stringstream ret;
    ret << (unsigned long long)(microSeconds*1000.0) << "ms" << " (";
    unsigned long long seconds = microSeconds ;
    if (seconds < 60) {
        ret << seconds << "s";
    }
    else if (seconds < 3600) {
        ret << seconds / 60ull << "min " << seconds % 60ull << "s";
    }
    else {
        ret << seconds / 3600ull << "h " << seconds % 3600ull / 60ull << "min " << seconds % 60ull << "s";
    }
    ret << ")";
    return ret;

}

unsigned long long currentTime() {

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration duration = now.time_since_epoch();
    unsigned long long microSecondsOfDuration = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    return microSecondsOfDuration;

}
