# 🎵 Music Playlist Management System

A console-based C++ application for creating and managing dynamic music playlists — demonstrating core OOP concepts including dynamic memory management, deep copy semantics, operator overloading, and static class members.

---

## Features

| # | Feature | Concept demonstrated |
|---|---------|---------------------|
| 1 | Create a playlist | Default constructor, heap allocation |
| 2 | Add songs | Dynamic array resizing |
| 3 | Remove a playlist | Destructor, `delete[]` |
| 4 | Copy a playlist | Deep copy constructor |
| 5 | Total playlists created | Static member variable |
| 6 | Longest song across all playlists | Static method + global tracking |
| 7 | Compare playlists | `operator>=` (friend function) |
| 8 | Play song by index | `operator[]` with bounds checking |
| 9 | Common songs between playlists | `operator+` |
| 10 | Unique songs in a playlist | `operator-` |
| 11 | Remove last song | `operator--` (postfix) |
| 12 | Print all songs | `operator<<` (friend function) |

---

## Getting Started

### Prerequisites

- A C++ compiler supporting C++17 (`g++`, `clang++`)
- `make` (optional but recommended)

### Build & Run

```bash
# Clone the repository
git clone https://github.com/your-username/music-playlist-system.git
cd music-playlist-system

# Build using Makefile
make

# Run
./music_playlist

# Or build manually
g++ -std=c++17 -Wall -Iinclude src/MusicTrack.cpp src/main.cpp -o music_playlist
```

---

## Project Structure

```
music-playlist-system/
├── include/
│   ├── Song.h          # Song struct definition
│   └── MusicTrack.h    # MusicTrack class declaration
├── src/
│   ├── MusicTrack.cpp  # Class implementation
│   └── main.cpp        # Menu-driven entry point
├── README.md
├── Makefile
└── .gitignore
```

---

## Design Decisions

- **Separation of concerns** — struct and class defined in separate headers; implementation in `.cpp`.
- **Deep copy** — the copy constructor allocates fresh memory rather than sharing pointers, preventing double-free bugs.
- **Static tracking** — `total_playlists` and `global_longest` are static members, shared across all instances without global variables.
- **Input validation** — all user input is validated in a loop; invalid values are rejected gracefully.
- **No STL containers** — uses raw `Song*` arrays to satisfy the assignment's memory-management learning goals.

---

## Concepts Covered

- `new` / `delete[]` dynamic memory
- Copy constructor (deep copy semantics)
- Destructor and RAII principles
- Operator overloading (`[]`, `+`, `-`, `--`, `>=`, `<<`)
- Friend functions
- Static data members and static methods
- Exception handling (`std::out_of_range`, `std::runtime_error`)

---

## Roadmap

- [ ] Add `operator=` (assignment operator) for complete Rule of Three
- [ ] Add file I/O to persist playlists between sessions
- [ ] Unit tests with a simple test harness
- [ ] Sort playlist by duration or title

---

## CV Description

> **Music Playlist Management System** · C++ · *December, 2025*
>
> Console application managing dynamic playlists using raw pointer arrays. Implemented deep copy semantics, seven operator overloads, static members for cross-instance tracking, and input-validated menus. Demonstrates strong understanding of memory management, OOP design, and C++ fundamentals.
