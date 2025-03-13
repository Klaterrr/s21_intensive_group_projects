```markdown
# School 21 Summer Intensive: C Projects

This repository contains three small C projects developed during the School 21 summer intensive.  These projects focus on fundamental programming concepts, structured programming principles, and the use of the standard C library, along with `ncurses` for one project.  Each project simulates a classic scenario, building skills in algorithm design, data structures, and terminal-based user interfaces.

## Projects

This repository includes the following projects:

1.  **P01D06-1-ping-pong:** A terminal-based implementation of the classic Pong game.
2.  **P02D13-1-the-game-of-life:** Conway's Game of Life simulation in the terminal.
3.  **P03D20-1-polish-notation:** A program to graph mathematical functions entered in infix notation, utilizing the Shunting Yard algorithm for conversion to Reverse Polish Notation (RPN).

## Common Constraints and Guidelines

*   **Language:** All projects are written in C (C99 standard).
*   **Structure:**  Adherence to Edsger W. Dijkstra's structured programming principles is enforced.  This includes avoiding `goto` statements and keeping functions concise (generally under 40-50 lines).
*   **Code Style:**  The code is checked for style compliance using `clang-format` and for potential issues using `cppcheck`.  Instructions for running these tools locally are provided in the `materials` folder (though that folder is not included in this description).
*   **Memory Management:**  Careful attention is paid to memory management to prevent leaks.  Dynamic memory allocation is used in the Polish Notation project.
*   **Libraries:**  Projects primarily use the standard C library (`stdio.h`, `stdlib.h`, `string.h`, `math.h`).  The Game of Life project also utilizes the `ncurses` library for interactive terminal control.
*   **Build System:** A `Makefile` is provided for each project for compilation and building.
```
## Project Details

### 1. P01D06-1-ping-pong

**Description:**  This project implements a two-player Pong game playable within a terminal.  It supports both a step-by-step mode and an interactive (real-time) mode.

**Files:**

*   `src/pong.c`: The main source code for the step-by-step version of the game.
*   `src/pong_interactive.c`:  (Not present in the provided file listing, but mentioned in the original README) Source code for the interactive, real-time version.  This would likely use `ncurses` or a similar library.
*  `src/board.h`: (Simple header file, sets width and height, likely not essential)

**Gameplay:**

*   **Step-by-Step Mode:**  Players take turns moving their paddles.  The space bar advances the game state.
*   **Interactive Mode:**  Players control their paddles in real-time.
*   **Controls:**
    *   Player 1: `A` (up), `Z` (down)
    *   Player 2: `K` (up), `M` (down)
    *   Spacebar: Advances the game in step-by-step mode.
*   **Winning:** The first player to reach 21 points wins.
* **Graphics:** ASCII characters are used to represent the paddles, ball, and playing field.

**Compilation (Step-by-Step):**

```bash
cd P01D06-1-ping-pong/src
gcc pong.c -o pong
./pong
```

**Compilation (Interactive - *if pong_interactive.c existed*):**  You would likely need to link against `ncurses`.

```bash
cd P01D06-1-ping-pong/src
gcc pong_interactive.c -o pong_interactive -lncurses
./pong_interactive
```

### 2. P02D13-1-the-game-of-life

**Description:**  This project is a terminal-based visualization of Conway's Game of Life, a classic cellular automaton.  It supports both random initialization and loading initial states from configuration files.

**Files:**

*   `src/game_of_life.c`:  The main source code for the Game of Life simulation.
*   `src/*.conf`:  Example configuration files (`a.conf`, `b.conf`, `c.conf`, `d.conf`, `e.conf`) demonstrating different initial patterns.

**Features:**

*   **Interactive Control:** The user can pause, resume, adjust the simulation speed, and quit the game.
*   **Initialization:**
    *   **Random:** The field can be initialized with a random distribution of live and dead cells.
    *   **File-Based:**  Initial states can be loaded from text files, where `*` represents a live cell and ` ` (space) represents a dead cell.  The provided `.conf` files offer examples.
*   **Controls:**
    *   `p`: Pause/Resume
    *   `s`: Decrease Speed
    *   `f`: Increase Speed
    *   `q`: Quit
* **Graphics:**  Uses `ncurses` for a more interactive display.  Live cells are represented by `*`, and dead cells by spaces. The grid is 80x25.

**Compilation:**

```bash
cd P02D13-1-the-game-of-life/src
gcc game_of_life.c -o game_of_life -lncurses
./game_of_life
```

**Running with a configuration file:**

```bash
./game_of_life  # Then select 'f' and input the file path, e.g., "a.conf"
# OR, using input redirection (if the program fully supports it):
./game_of_life < a.conf
```

### 3. P03D20-1-polish-notation

**Description:** This project takes a mathematical expression in infix notation as input (e.g., `sin(x) * (x + 2)`) and generates a graph of the function in the terminal.  It uses the Shunting Yard algorithm to convert the infix expression to Reverse Polish Notation (RPN) for evaluation.

**Files:**

*   `src/graph.c`:  The main source code, including parsing, RPN conversion, evaluation, and graph plotting.
*   `src/lib.h`, `src/lib.c`: (Not provided, but implied by `graph.c`)  Likely contains helper functions for tokenization and general utility functions.
*   `src/stack.h`, `src/stack.c`:  Implementation of a stack data structure, crucial for both the Shunting Yard algorithm and RPN evaluation.
*   `src/Makefile`:  Builds the project.
*   `src/test.c`: (Empty, intended for unit tests).

**Features:**

*   **Infix to RPN Conversion:**  Implements Dijkstra's Shunting Yard algorithm.
*   **RPN Evaluation:**  Evaluates the RPN expression using a stack.
*   **Supported Operations and Functions:**
    *   Arithmetic: `+`, `-` (unary and binary), `*`, `/`
    *   Parentheses: `()`
    *   Trigonometric: `sin(x)`, `cos(x)`, `tan(x)`, `ctg(x)`
    *   Other: `sqrt(x)`, `ln(x)`
    *   Variable: `x`
*   **Graph Plotting:**  Generates an ASCII-based graph of the function.
    *   Domain: \[0, 4π]
    *   Range: \[-1, 1]
    *   Resolution: 80x25 characters
    *   Origin: Centered at (0, 12) (middle of the left border)
    *   Graph Symbol: `*`
    *   Background Symbol: `.`
* **Makefile commands**:
  * `all`: builds the project.
  * `cp_cf`: copies the clang format file
  * `all_checks`: runs clang-format and cppcheck.
  * `all_fix`: formats the code with clang-format.
  * `clean`: cleans up object files.
  * `rebuild`: cleans and rebuilds the project.

**Compilation:**

```bash
cd P03D20-1-polish-notation/src
make
./graph
```

**Input:**  The program prompts the user to enter a mathematical expression in infix notation.

**Example Usage:**

```
./graph
sin(x) * (x + 2)  # Enter this at the prompt
# ... (graph output) ...
```

## Summary

These projects provide a good foundation in C programming, covering diverse topics from basic game development to algorithmic problem-solving and data structure implementation. They demonstrate a commitment to clean, well-structured code, and the use of common development tools.
```

Key improvements and explanations in this README:

*   **Clear Project Overview:**  Provides a concise introduction to the entire repository and its purpose.
*   **Organized Structure:** Uses headings and bullet points for readability.
*   **Detailed Project Sections:**  Each project has its own section explaining its functionality, files, compilation, and usage.
*   **Comprehensive Feature Lists:**  Highlights the key features of each project.
*   **Compilation Instructions:**  Provides clear, step-by-step instructions on how to compile and run each project.  Includes necessary linking flags (e.g., `-lncurses`).
*   **Input/Output Examples:** Shows how to interact with the programs.
*   **Algorithm Explanations:** Briefly mentions the use of the Shunting Yard algorithm and RPN.
*   **Constraints and Guidelines:**  Summarizes the common rules and coding standards followed across all projects.
*   **Assumptions and Clarifications:**  Addresses potential missing files (like `pong_interactive.c`, `lib.h`, `lib.c`) and explains their likely purpose.
*   **Professional Tone:**  Uses a formal and informative writing style.
*   **Makefile explanation:** Includes description of all commands available in the Makefile.

This improved README.md provides a much more complete and user-friendly guide to the projects, making it easier for others to understand, build, and run the code. It's suitable for sharing on platforms like GitHub, GitLab, or Bitbucket.
