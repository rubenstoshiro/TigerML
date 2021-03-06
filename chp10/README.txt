Group Members:
Paul Cruz
Rubens Farias 
Mike Ma

ECE553 Liveness Analysis Submission


Compilation: Compile the project by writing the following commands in the SML window
1) CM.make "sources.cm";
2) Main.compile "TEST_NAME_HERE.tig"

This will give you a shortened version of the output. In order to print out a more verbose version, use the following commands (please note that the int 3 at the end is needed (this is a print option that determines how much output is printed. You can also use values of 1 or 2):
1) CM.make "sources.cm";
2) Main.compileverb "TEST_NAME_HERE.tig" 3

lastly, we've included several files that can be used for compiling all useful tests. You can use these commands to compile all tests that should output interference graphs (excludes the ones with syntax errors, etc) or compile all 50 tests and export them to a text file

1) sml < good_tests.sml > output.txt
or
2) sml < tests.sml > output.txt

Note that good_tests.sml and tests.sml rely on our directories to work properly, therefore using them may require changing them a bit.



During this phase, we wrote most of the code in three significant files: flowgraph.sml, makegraph.sml, and liveness.sml. It should be noted that instead of using Appel's provided graph.sml module, we instead used Professor Hilton's funcgraph.sml. The first two modules we wrote (makegraph.sml and flowgraph.sml) are responsible for generating the control flow graph. This was done using basic blocks rather than creating a node for each instruction. The idea behind this implementation was that fact that canon.sml formats the insturctions nicely. Generally speaking, the assembly instructions should repeat the pattern label instruction, several operations, and then jump instruction (the only places where this is not the case are where an operation is listed, and the next assembly portion is a label, in which case we insert an artificial jump to the next label, which is equivalent). Since the instructions that occur between a label and a jump instruction must occur one after the other, these are all 1 predecessor/1 successor nodes that can be combined. Therefore we combine them into one node, and calculate the defs/uses for that node. Once defs/uses are calculated for each of the nodes, the result is passed to liveness.sml to generate the interference graph.

When calculating intereference, the liveness module first computes live-in and live-out sets for each node in the control flow graph using equations from the book (the iteration method). Once live-in and live-out sets have been computed for each node, we can perform liveness at the instruction level within each block by using live-out for that block and working backwards. For each instruction, interference edges are added to the interference graph. This is done for each node in the control flow graph, thus giving us the produced interference graph. 

We also wrote the show function in the liveness module, we prints out the interference graph. This is done by simply looking at each node in the interference graph (which represents a temp or special register), and then printing out the corresponding adjacent nodes. We did not create move edges for coalescing in this phase of the project.

