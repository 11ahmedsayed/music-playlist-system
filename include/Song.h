#ifndef SONG_H
#define SONG_H

#include <string>

/**
 * @struct Song
 * @brief Represents a single music track with a title and duration.
 */

struct Song {
    std::string title;
    double duration; // in minutes

    // Default constructor — ensures safe initialization
    Song() : title(""), duration(0.0) {}

    Song(const std::string& t, double d) : title(t), duration(d) {}
};

#endif // SONG_H