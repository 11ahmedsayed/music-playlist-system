#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include "MusicTrack.h"

using namespace std;

// ── Helpers ───────────────────────────────────────────────────────────────────

static void printSeparator() {
    cout << "\n════════════════════════════════════\n";
}

static void printMenu() {
    printSeparator();
    cout << "  🎵 Music Playlist Manager\n";
    printSeparator();
    cout << "  1.  Create a new playlist\n"
              << "  2.  Add songs to a playlist\n"
              << "  3.  Remove a playlist\n"
              << "  4.  Copy a playlist\n"
              << "  5.  Total playlists created\n"
              << "  6.  Longest song across all playlists\n"
              << "  7.  Compare two playlists (>=)\n"
              << "  8.  Play song by index\n"
              << "  9.  Display common songs (+)\n"
              << "  10. Display unique songs (-)\n"
              << "  11. Remove last song (--)\n"
              << "  12. Print all songs (<<)\n"
              << "  13. Exit\n";
    printSeparator();
    cout << "  Choice: ";
}

/** Safely reads an integer from stdin */
static int readInt(const string& prompt = "") {
    int v;
    if (!prompt.empty()) cout << prompt;
    while (!(cin >> v)) {
        cout << "  Invalid input. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return v;
}

/** Prompts for a valid playlist index (1-based display, 0-based returned) */
static int pickPlaylist(int count) {
    if (count == 0) { cout << "  No playlists available.\n"; return -1; }
    cout << "  Select playlist (1–" << count << "): ";
    int idx = readInt() - 1;
    if (idx < 0 || idx >= count) { cout << "  Invalid selection.\n"; return -1; }
    return idx;
}

// ── main ──────────────────────────────────────────────────────────────────────

int main() {
    vector<MusicTrack*> playlists; // owns heap-allocated playlists
    int choice;

    do {
        printMenu();
        choice = readInt();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {

        // 1. Create playlist
        case 1: {
            playlists.push_back(new MusicTrack());
            cout << "  ✔ Playlist #" << playlists.size() << " created.\n";
            break;
        }

        // 2. Add songs
        case 2: {
            int idx = pickPlaylist(static_cast<int>(playlists.size()));
            if (idx != -1) playlists[idx]->addNewSongs();
            break;
        }

        // 3. Remove playlist
        case 3: {
            int idx = pickPlaylist(static_cast<int>(playlists.size()));
            if (idx != -1) {
                delete playlists[idx];
                playlists.erase(playlists.begin() + idx);
                cout << "  ✔ Playlist removed.\n";
            }
            break;
        }

        // 4. Copy playlist
        case 4: {
            int idx = pickPlaylist(static_cast<int>(playlists.size()));
            if (idx != -1) {
                playlists.push_back(new MusicTrack(*playlists[idx])); // copy ctor
                cout << "  ✔ Playlist copied as #" << playlists.size() << ".\n";
            }
            break;
        }

        // 5. Total playlists created
        case 5:
            cout << "  Total playlists ever created: "
                      << MusicTrack::totalPlaylistsCreated() << "\n";
            break;

        // 6. Longest song
        case 6:
            try {
                Song s = MusicTrack::longestSongInAllPlaylists();
                cout << "  Longest song: \"" << s.title
                          << "\" (" << s.duration << " min)\n";
            } catch (const exception& e) {
                cout << "  " << e.what() << "\n";
            }
            break;

        // 7. Compare two playlists
        case 7: {
            if (playlists.size() < 2) {
                cout << "  Need at least 2 playlists to compare.\n"; break;
            }
            cout << "  First  "; int a = pickPlaylist(static_cast<int>(playlists.size()));
            cout << "  Second "; int b = pickPlaylist(static_cast<int>(playlists.size()));
            if (a == -1 || b == -1) break;
            if (*playlists[a] >= *playlists[b])
                cout << "  Playlist #" << (a+1) << " has >= songs than #" << (b+1) << ".\n";
            else
                cout << "  Playlist #" << (a+1) << " has fewer songs than #" << (b+1) << ".\n";
            break;
        }

        // 8. Play song by index
        case 8: {
            int idx = pickPlaylist(static_cast<int>(playlists.size()));
            if (idx == -1) break;
            int songIdx = readInt("  Song index (1-based): ") - 1;
            try {
                Song s = (*playlists[idx])[songIdx];
                cout << "  ▶ Playing: \"" << s.title
                          << "\" (" << s.duration << " min)\n";
            } catch (const out_of_range& e) {
                cout << "  Error: " << e.what() << "\n";
            }
            break;
        }

        // 9. Common songs (operator+)
        case 9: {
            if (playlists.size() < 2) {
                cout << "  Need at least 2 playlists.\n"; break;
            }
            cout << "  First  "; int a = pickPlaylist(static_cast<int>(playlists.size()));
            cout << "  Second "; int b = pickPlaylist(static_cast<int>(playlists.size()));
            if (a == -1 || b == -1) break;
            MusicTrack common = *playlists[a] + *playlists[b];
            cout << "  Common songs:\n" << common;
            break;
        }

        // 10. Unique songs (operator-)
        case 10: {
            if (playlists.size() < 2) {
                cout << "  Need at least 2 playlists.\n"; break;
            }
            cout << "  Source "; int a = pickPlaylist(static_cast<int>(playlists.size()));
            cout << "  Minus  "; int b = pickPlaylist(static_cast<int>(playlists.size()));
            if (a == -1 || b == -1) break;
            MusicTrack unique = *playlists[a] - *playlists[b];
            cout << "  Unique songs from playlist #" << (a+1) << ":\n" << unique;
            break;
        }

        // 11. Remove last song (operator--)
        case 11: {
            int idx = pickPlaylist(static_cast<int>(playlists.size()));
            if (idx != -1) (*playlists[idx])--;
            break;
        }

        // 12. Print all songs (operator<<)
        case 12: {
            int idx = pickPlaylist(static_cast<int>(playlists.size()));
            if (idx != -1) std::cout << *playlists[idx];
            break;
        }

        case 13:
            cout << "  Goodbye! Cleaning up...\n";
            break;

        default:
            cout << "  Invalid option. Choose 1–13.\n";
        }

    } while (choice != 13);

    // Cleanup — free all remaining playlists
    for (MusicTrack* p : playlists) delete p;
    playlists.clear();

    return 0;
}