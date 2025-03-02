# TDDD86 Advanced Data Structures and Algorithms Labs

This repository contains laboratory assignments for the TDDD86 Advanced Data Structures and Algorithms course. The labs focus on implementing fundamental algorithms and data structures in C++ while solving complex computational problems.

## Labs Overview

### Lab 1: Conway's Game of Life
- **Description**: Cellular automaton simulation implementing John Conway's rules
- **Key Features**:
  - Toroidal grid implementation
  - Graphical simulation using Stanford C++ Library
  - Support for various initial patterns
- **Learning Objectives**: Grid manipulation, neighbor counting algorithms

### Lab 2: Word Puzzles
1. **Evil Hangman**
   - Adaptive hangman game with dynamic dictionary management
   - Implements cheating strategy using word families
2. **Word Chain**
   - Finds valid transformations between words using BFS
   - Implements graph representation of word relationships

### Lab 3: Traveling Salesman Problem (TSP)
- **Implementation**: Nearest neighbor heuristic algorithm
- **Features**:
  - 2D point representation and distance calculations
  - Visual tour representation
  - Performance analysis on large datasets

### Lab 4: Robot Survival Game
- **Core Mechanics**:
  - Robot AI movement algorithms
  - Collision detection and response
  - Energy management system
- **Data Structures**: Custom grid-based entity management

### Lab 5: Boggle Word Game
- **Features**:
  - Trie-based dictionary implementation
  - Recursive board traversal
  - Score calculation system
- **Algorithms**: Depth-first search with backtracking

### Lab 6: Fish Simulation
- **Implementation**:
  - Priority queue-based event simulation
  - Custom vector implementation
  - Statistical analysis of fishing strategies

### Lab 7: Pattern Recognition
- **Algorithm**: Efficient collinear point detection
- **Optimizations**:
  - Slope-based sorting
  - Duplicate point handling
  - Brute force fallback

### Lab 8: Pathfinding Algorithms
- **Implemented Methods**:
  - Dijkstra's algorithm
  - A* search
  - Kruskal's algorithm for maze generation
- **Features**: Terrain cost modeling and visualization

### Extra Lab 1: Huffman Coding
- **Implementation**:
  - Frequency analysis and priority queue
  - Binary tree construction
  - Bitstream compression/decompression
- **Applications**: File compression for various data types

## Prerequisites
- Qt 5+ development tools
- C++17 compatible compiler
- Stanford C++ Library (included)

## Building and Running
Each lab uses Qt project files (.pro) for building. Example for Lab 1:

```bash
# Navigate to lab directory
cd lab1

# Generate Makefile and build
qmake Life.pro
make

# Run executable (Windows)
release\life.exe

# Or for Linux/Mac
./release/life
```

Note: Ensure qmake is in your PATH or use full path to Qt's qmake executable.


## Contributors
- Me
- [Ludwig Ingestedt](https://github.com/LudwigIngestedtGit)

**Note**: Solutions are for educational purposes only.
