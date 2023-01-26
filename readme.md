Matthew Olaka
V00888684
Assignment 1 partb

This assignment was to implement some basic functionality of a linux shell such as:

* Execute commands with arguments in a child process
* Execute a commands from a .SEEshrc file

# Helpful links that helped me write the code:

https://brennan.io/2015/01/16/write-a-shell-in-c/?fbclid=IwAR1sstZm2AY_L8qfPtHGpZQ4aOO1xTuXltfC9TcEnDL4G5IcW4Lego3ND2Y
https://stackoverflow.com/questions/17929414/how-to-use-setenv-to-export-a-variable-in-c
https://www.tutorialspoint.com/c_standard_library/c_function_exit.htm
https://stackoverflow.com/questions/18041100/using-c-string-address-of-stack-memory-associated-with-local-variable-returned


# Summary of memory leaks and errors from valgrind:

==5365== 
==5365== HEAP SUMMARY:
==5365==     in use at exit: 4,216 bytes in 2 blocks
==5365==   total heap usage: 9 allocs, 7 frees, 15,248 bytes allocated
==5365== 
==5365== LEAK SUMMARY:
==5365==    definitely lost: 0 bytes in 0 blocks
==5365==    indirectly lost: 0 bytes in 0 blocks
==5365==      possibly lost: 0 bytes in 0 blocks
==5365==    still reachable: 4,216 bytes in 2 blocks
==5365==         suppressed: 0 bytes in 0 blocks
==5365== Rerun with --leak-check=full to see details of leaked memory
==5365== 
==5365== For counts of detected and suppressed errors, rerun with: -v
==5365== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)