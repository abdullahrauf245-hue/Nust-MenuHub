🍴 NUST MenuHub: C++ File-Based Management System
NUST MenuHub is a centralized dining management application built to handle the menus and pricing for the 9 primary cafes across the NUST campus. This project focuses on robust File I/O, data persistence, and building a clean, user-centric Command Line Interface (CLI).

📂 Repository Breakdown
🧠 Core Logic
focp3.cpp: The main driver of the application. It handles the user interface, cafe selection logic, and integration of the data modules.

Logic.cpp: Contains the backend functions, including the file-parsing algorithms and stream management.

📜 Database Layer (.txt)
The system uses flat-file databases to ensure data persists even after the program closes. The following files act as the "Source of Truth" for the app:

Hostel & Academic Cafes: C1.txt, C2 Menu.txt, C3 Menu.txt, C4 menu.txt, S3H Cafe.txt

Specialty Lounges: Coffee Lounge Menu.txt, Inno.txt, Retro Menu.txt, Nice Menu.txt

🏗️ Technical Architecture
The system bridges the gap between static text files and dynamic user interaction using the <fstream> library:

Selection: The user chooses a cafe from the main menu.

Streaming: The program establishes an ifstream connection to the corresponding .txt file.

Parsing: The logic reads structured data (Item Name | Price) into memory.

Formatting: The CLI outputs a clean, tabular view of the menu for the student.

🚀 Installation & Setup
To run the project locally via CMD, follow these steps:

Clone the Repository:

DOS
git clone https://github.com/abdullahrauf245-hue/Nust-MenuHub.git
cd Nust-MenuHub
Verify Files: Ensure all .txt files are in the same directory as the .cpp files.

Compile:

DOS
g++ focp3.cpp -o MenuHub
Launch:

DOS
MenuHub.exe
🎓 Academic Context
Course: Fundamentals of Computer Programming (FOCP)

University: National University of Sciences & Technology (NUST)

Key Skills: C++, File Handling, String Manipulation, and CLI Design.

Maintained by: Muhammad Abdullah

Status: Completed (December 2025)
