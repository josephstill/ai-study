# Artificial Intelligence Study
This is a simple study on artificial intelligence using a winner tree. The purpose of this study is to get familiarity with a simple game AI algorithm as well as memory usage, data structures, and general C programming tactics. There will also be some emphasis on geneeral software engineering practices. 

## Code Segments
The project will be broken into a few logical segments that will be described here as they begin development. This is to encapsulate functionality and ease in development. This will also help isolate and fix bugs easily.  
 
### Map
The map will be square and contain the tokens X, Y, and whitespace. While Xs and Os are standard, Xs and Ys will be used because math, and why not (very adult reasoning). Map functions will encapsulate allocating a map, deleting a map, traversing a map, setting map state, creating map strings, and comparing two maps. 

### Test
Unit tests will be used to make sure that code is tested throughout development. The test module will provide the functionality to accomplish this. The hope is that successful passing of unit tests are required for the building of the modules that follow up the dependency tree.    

## Code Standards
Code will be written in C and built with GCC through a makefile. Following are some highlights of coding standards.
* There should be no compiler warnings.
* Function names, variable names, and typedefs are camel case.
* Function names and variable names are lower case while typedefs are upper case.
* Enums and preprocessor variable names are all caps with underscore between words.
* All variables will be declared at the top of the function. 
* Brackets open on a new line.
* There will be spaces between ifs, fors, whiles, and the following open parenthesis.
* There will be no space between function names and parameter lists.
* Spaces will be used instead of tabs with the exception of Makefiles