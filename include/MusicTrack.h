#ifndef MUSICTRACK_H
#define MUSICTRACK_H

#include "Song.h"
#include <iostream>
#include <string>

/**
 * @class MusicTrack
 * @brief Manages a dynamic playlist of songs with full memory ownership.
 *
 * Demonstrates: dynamic arrays, deep copy, operator overloading,
 * static members, and friend functions.
 */
class MusicTrack {
private:
    Song* playlist;       // Dynamic array of songs
    int   playlist_size;  // Current number of songs

    // Static members — shared across ALL playlist instances
    static int    total_playlists;   // Tracks how many playlists have been created
    static Song   global_longest;    // Tracks the longest song seen across all playlists
    static bool   has_any_song;      // Guards against comparing an empty global_longest

public:
    // ── Constructors & Destructor ─────────────────────────────────────────────
    MusicTrack();
    MusicTrack(const MusicTrack& other);
    ~MusicTrack();

    // ── Core Operations ───────────────────────────────────────────────────────
    void addNewSongs();
    void addSong(const Song& s);

    // ── Static Queries ────────────────────────────────────────────────────────
    static int totalPlaylistsCreated();
    static Song longestSongInAllPlaylists();

    // ── Operator Overloads ────────────────────────────────────────────────────
    friend bool operator>=(const MusicTrack& lhs, const MusicTrack& rhs);
    Song operator[](int index) const;
    MusicTrack operator+(const MusicTrack& other) const;
    MusicTrack operator-(const MusicTrack& other) const;
    MusicTrack operator--(int);
    friend std::ostream& operator<<(std::ostream& os, const MusicTrack& mt);

    // ── Accessors ─────────────────────────────────────────────────────────────
    int size() const { return playlist_size; }
};

#endif // MUSICTRACK_H