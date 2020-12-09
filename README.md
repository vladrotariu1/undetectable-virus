# undetectable-virus

This is a reverse TCP program. I created it to be undetectable by the most of the viruses.

Tetris folder contains the client program written in C, the Python game source code and the compiled python game. When you open the game (tetris/build/tetris/tetris.exe), in the background 
a C client starts. The client code(tetris/build/source/client.c) is compiled locally, because the game comes with the TDM-GCC compiler(tetris/TDM-GCC-64). So when the game starts, it 
executes the create_binary.bat, which is located in the same folder as tetris.exe. Create_binary.bat will use the TDM compiler and compile the client.c, than will start the client executable.
The reason why the program comes with the compiler is to compile it locally, because the client executable has a chance to be recognized by the browser.


The server side is a program that waits for an incoming connection and than executes powershell commands on the victim PC. The server side must be executed on a Linux system.
