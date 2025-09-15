# 🧩 Sudoku Solver in C++ with SFML

This project is a **Sudoku solver and generator** implemented in **C++** with an integrated graphical user interface using **SFML**.  
It allows the user to generate random Sudoku puzzles, verify their uniqueness, and watch the solving process in real time.

---

## Features

- **Puzzle Solving**  
  - Solve puzzles using a recursive **backtracking algorithm** with row, column, and subgrid validation.  
  - Detect contradictions and backtrack until a valid assignment is found.  
  - Optionally slow down solving to observe the algorithm’s progress step by step, making it a valuable visual   representation of backtracking algorithm
 
- **Puzzle Generation**  
  - Create an empty board.  
  - Generate a fully solved valid Sudoku board and selectively remove entries to form a puzzle.  
  - Enforce uniqueness of puzzles by rejecting grids with multiple solutions.  

- **Visualization**  
  - **SFML window** displays the 9×9 grid, current digits, and solver updates.  
  - Separate thread executes the solver while the UI continuously redraws the board.  
  - Mutex synchronization ensures safe concurrent access to the board state.  
  - Optional background textures and custom fonts for improved readability.  

- **Modes of Operation**  
  - Fast solving without delays.  
  - Animated solving with configurable delay per step.  
  - Puzzle generation with user-defined difficulty ranges (by number of removed cells).  

---

## 📸 Example Screenshots

<img width="1494" height="1025" alt="Zrzut ekranu 2025-09-15 224321" src="https://github.com/user-attachments/assets/bdde8b46-3aff-4498-9b47-832872eaa9cd" />

<img width="1499" height="1033" alt="Zrzut ekranu 2025-09-15 224124" src="https://github.com/user-attachments/assets/c4003614-55b7-4628-900d-f9e17f9a4bd2" />
