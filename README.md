busybeaver
==========

A crappy implementation of a busy beaver Turing machine.

## What is a busy beaver?

A busy beaver is a form of [Turing Machine](https://en.wikipedia.org/wiki/Turing_machine)
that follows a limited ruleset to obtain a maximum number of steps and eventually halt
, as indicated by '1's on the Turing machine's tape.

A busy beaver has *N* states (as well as a *HALT* state), and a table associating
non-halt states with symbols read from the tape. A lookup is done with the current
state and current tape symbol, resulting in a sequence of operations until a 
*HALT* is encountered.

## Example

Given a 2-state, 2-symbol busy beaver, the table might look something like this:

|S/S|A|B|
|------------
|0	|1RB|1LA|
|1	|1LB|1RH|

Where **A** and **B** are the states, **0** and **1** are the tape symbols,
and **L**, **R**, and **H** represent left shift, right shift, and halting.
