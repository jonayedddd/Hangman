# Console Hangman: Movies & Shows Edition

A dynamic, console-based implementation of the classic Hangman game written in C++. This project demonstrates standard file I/O operations, vector manipulation, and input validation.

## 🎮 Features
* **Dynamic Word Loading:** Reads the word bank from an external `words.txt` file, allowing for easy updates to the game vocabulary without recompiling.
* **Randomized Gameplay:** Utilizes `srand(time(0))` to ensure a different word is selected every round.
* **Input Validation:** Handles character casing (auto-converts to lowercase) and validates user guesses.
* **Visual Interface:** Displays a progressive ASCII art "Hangman" figure as lives decrease.
* **Replay System:** Prevents repeat words within a single session and allows the user to restart the game seamlessly.

## 🛠️ Technical Implementation
* **Language:** C++
* **Libraries:** `<vector>`, `<fstream>`, `<string>`, `<ctime>`
* **Data Structure:** Uses `std::vector` to store the word bank for efficient dynamic resizing (removing played words).

## 🚀 How to Run
1.  Clone the repository.
2.  Ensure `words.txt` is in the same directory as the source file.
3.  Compile using any standard C++ compiler (e.g., g++):
    ```bash
    g++ Main.cpp -o hangman
    ./hangman
    ```

## 📝 Sample Word List
The game currently features popular media titles, including:
* *Game of Thrones*
* *Interstellar*
* *Stranger Things*
* *The Godfather*
