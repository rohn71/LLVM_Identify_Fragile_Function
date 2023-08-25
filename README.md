# LLVM_Identify_Fragile_Function
Code to Identify and Display the fragile functions in LLVM.
![LLVM logo](https://www.linuxadictos.com/wp-content/uploads/LLVM.png)

This was done as EL componet of Compiler Design Course, the problem statement is:

Consider the following data as input:
```
struct FragileCluster {
   llvm::DebugLoc start;
   llvm::DebugLoc end;
};
struct FragileCluster[] = { ... };
```
Create a custom LLVM attribute, named ```IsFragile```.

Iterate over each control flow graph in the program, comparing the basic block source locations against the above input. If the location of any basic block overlaps with any of the source ranges provided in the above input, mark the associated function (i.e. the function containing the basic block) with the above custom attribute.

Display all functions that are marked with the custom attribute IsFragile in a formatted table. Include the full signature of the function in the display, including the parameter names, types and the return type. Also display the size of the function (in number of lines of code) and the name of the source file that contains the function definition.



#### Files
- The header files are defined in ```MyLLVMPass.h``` which imports requred files from llvm/pass.
- ```MyLLVMPass.cpp``` implements the logic to identify and display fragile functions.
      the fuction markFragileFuctions() iterates over the basic blocks, detects the fragile function and marks it as IsFragile.
      and the function collectAndDisplayFragileFunctions() displays all marked functions in table.
- ```exp'x'.bc``` files are diffrent IR codes to test the program, by passing these in the main function.



