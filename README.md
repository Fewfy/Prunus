# Prunus
This project is to follow Yan Chernikov's course step by step to build a gaming engine, the name is for the tree I planted this spring with my girlfriend



1. `git submodule init`

2. `git submodule update`

3. execute `Prunus\GenerateProjects.bat` file

Hint:
1. the include reference to the precompiled files must be put in the begining of the file
1. if there comes plenty of errors like `unresolved external symbol __imp__wassert`, please go to project -> properties -> C/C++ -> Code Generation -> Runtime Library, please make sure the runtime for each project are the same