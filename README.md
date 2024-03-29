# gameoflife-mini-c
A Game of Life implementation written in C with extra language constraints

**Goals:**

* Experimenting how much C syntax could be thrown overboard while still having a Turing complete language :).
* Exploring the power of C pointers :D

**Constraints:**

* No 'if', 'else', 'elseif', 'switch' etc.
* No 'while', 'for', 'foreach' etc.
* No '&&', '||', '!'
* No 'goto'
* No '?'-Operator
* No guards (not available in C anyway)
* No external API

**Note:**

This Game-Of-Life implementation so far is totally incomplete, of course!
However the way loops and checks are performed in the test functions
should give a hint on how Turing completeness still holds with these
constraints.

**How to Run:**

	$ make
	$ ./gol
	$ echo $?

This outputs 0 if all tests have passed, 1 otherwise.
