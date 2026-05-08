#include "MusicTrack.h"
#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

// ── Static member definitions ─────────────────────────────────────────────────
int  MusicTrack::total_playlists = 0;
Song MusicTrack::global_longest  = Song("", 0.0);
bool MusicTrack::has_any_song    = false;

// ── Helper: update global longest song ───────────────────────────────────────
static void updateGlobalLongest(Song& global, bool& has_any, const Song& candidate) {
    if (!has_any || candidate.duration > global.duration) {
        global  = candidate;
        has_any = true;
    }
}

// ── Constructors & Destructor ─────────────────────────────────────────────────

MusicTrack::MusicTrack() : playlist(nullptr), playlist_size(0) {
    ++total_playlists;
}

MusicTrack::MusicTrack(const MusicTrack& other)
    : playlist_size(other.playlist_size) {

    if (other.playlist_size > 0) {
        playlist = new Song[other.playlist_size];
        for (int i = 0; i < other.playlist_size; ++i)
            playlist[i] = other.playlist[i];
    } else {
        playlist = nullptr;
    }
    ++total_playlists;
}

MusicTrack::~MusicTrack() {
    delete[] playlist;
    playlist      = nullptr;
    playlist_size = 0;
    cout << "[~] Playlist removed and memory freed.\n";
}

// ── Core Operations ───────────────────────────────────────────────────────────

void MusicTrack::addSong(const Song& s) {
    // Allocate a new array one element larger, copy, then replace
    Song* enlarged = new Song[playlist_size + 1];
    for (int i = 0; i < playlist_size; ++i)
        enlarged[i] = playlist[i];
    enlarged[playlist_size] = s;

    delete[] playlist;
    playlist = enlarged;
    ++playlist_size;

    updateGlobalLongest(global_longest, has_any_song, s);
}

void MusicTrack::addNewSongs() {
    int count;
    cout << "How many songs do you want to add? ";
    while (!(cin >> count) || count < 1) {
        cout << "Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    for (int i = 0; i < count; ++i) {
        string title;
        double duration;

        cout << "Song " << (i + 1) << " title: ";
        getline(cin, title);

        cout << "Song " << (i + 1) << " duration (minutes): ";
        while (!(cin >> duration) || duration <= 0) {
            cout << "Enter a valid positive duration: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        addSong(Song(title, duration));
        cout << "  Added: \"" << title << "\" (" << duration << " min)\n";
    }
}

// ── Static Queries ────────────────────────────────────────────────────────────

int MusicTrack::totalPlaylistsCreated() {
    return total_playlists;
}

Song MusicTrack::longestSongInAllPlaylists() {
    if (!has_any_song)
        throw runtime_error("No songs have been added to any playlist yet.");
    return global_longest;
}

// ── Operator Overloads ────────────────────────────────────────────────────────

bool operator>=(const MusicTrack& lhs, const MusicTrack& rhs) {
    return lhs.playlist_size >= rhs.playlist_size;
}

Song MusicTrack::operator[](int idx) const {
    if (idx < 0 || idx >= playlist_size)
        throw out_of_range("Index " + to_string(idx) +
                                " is out of range (size: " +
                                to_string(playlist_size) + ").");
    return playlist[idx];
}

MusicTrack MusicTrack::operator+(const MusicTrack& other) const {
    MusicTrack common;
    for (int i = 0; i < playlist_size; ++i)
        for (int j = 0; j < other.playlist_size; ++j)
            if (playlist[i].title == other.playlist[j].title)
                common.addSong(playlist[i]);
    return common;
}

MusicTrack MusicTrack::operator-(const MusicTrack& other) const {
    MusicTrack unique;
    for (int i = 0; i < playlist_size; ++i) {
        bool found = false;
        for (int j = 0; j < other.playlist_size; ++j)
            if (playlist[i].title == other.playlist[j].title) { found = true; break; }
        if (!found) unique.addSong(playlist[i]);
    }
    return unique;
}

MusicTrack MusicTrack::operator--(int) {
    MusicTrack snapshot(*this); // save state before modification
    if (playlist_size == 0) {
        cout << "Playlist is already empty.\n";
        return snapshot;
    }
    // Shrink by one: allocate smaller array, copy all but last
    Song* shrunk = (playlist_size > 1) ? new Song[playlist_size - 1] : nullptr;
    for (int i = 0; i < playlist_size - 1; ++i)
        shrunk[i] = playlist[i];

    cout << "Removed last song: \"" << playlist[playlist_size - 1].title << "\"\n";
    delete[] playlist;
    playlist = shrunk;
    --playlist_size;
    return snapshot;
}

ostream& operator<<(ostream& os, const MusicTrack& mt) {
    if (mt.playlist_size == 0) {
        os << "  (empty playlist)\n";
        return os;
    }
    os << "  ┌─ Playlist (" << mt.playlist_size << " songs) ──────────────\n";
    for (int i = 0; i < mt.playlist_size; ++i)
        os << "  │  " << (i + 1) << ". "
           << mt.playlist[i].title
           << "  (" << mt.playlist[i].duration << " min)\n";
    os << "  └────────────────────────────────────\n";
    return os;
}