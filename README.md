busybeaver
==========

A crappy implementation of a busy beaver Turing machine.

## What is a busy beaver?

A busy beaver is a form of [Turing Machine](https://en.wikipedia.org/wiki/Turing_machine)
that follows a limited ruleset to obtain a maximum number of steps and eventually halt, as
indicated by '1's on the Turing machine's tape. A busy beaver begins in the center
of the tape.

A busy beaver has *N* states (as well as a *HALT* state), and a table associating
non-halt states with symbols read from the tape. A lookup is done with the current
state and current tape symbol, resulting in a sequence of operations until a 
*HALT* is encountered.

## Example

Given a 2-state, 2-symbol busy beaver, the table might look something like this:

| S/S | A | B |
| --- | --- | --- |
| 0 | 1RB | 1LA |
| 1 | 1LB | 1RH |

Where **A** and **B** are the states, **0** and **1** are the tape symbols,
and **L**, **R**, and **H** represent left shift, right shift, and halting.

Given the initial blank TM:

```
. . . 0 0 0 0 0 0 0 0 . . . 
              ^
         start cell

```

This beaver would produce the following tape state:

` 1RB -> 1LA -> 1LB -> 1LA -> 1RB -> 1RH `


```
. . . 0 0 1 1 1 1 0 0 . . .
              ^
          halt cell
```

For a total of 6 steps and 4 toggled cells.

## This Implementation

Because an optimal busy beaver with more than 5 states has
[yet to be decided](http://www.logique.jussieu.fr/~michel/ha.html#tm52),
this implementation only supports 4 or fewer states.

It takes a file as its singlular input, parsing it for the symbol/state table.
The parser is extremely rudimentary, and an example 2-2 table might look like this:

```
1r2 1l1
1l2 1r0
```

Where the first number is the symbol, and the second is the state index
(i.e. 0 => *HALT*, 1 => 'A', 2 => 'B', etc...). The middle character represents
the action (l => 'left', r => 'right'). As such, the table above presents the same
busy beaver as the example table.

### Building and Running:

`busybeaver` is meant to be C99 compatible, and should build on any system with
a C99-compliant compiler.

Just run:
```bash
$ git clone https://github.com/woodruffw/busybeaver
$ cd busybeaver
$ make
```

This will drop the `busybeaver` executable in the working directory.
Then, just run it:

```bash
$ ./busybeaver mystatefile.state
```

**IMPORTANT**: If your statefile describes a function that loops forever,
`busybeaver` will almost definitely run out of tape space and segfault. Stick to
busy beaver functions only (which must have *some* kind of halt statement.)

You can find some example statefiles in the *states* directory.

### Diagnostics

Because this is a crappy busy beaver, all kinds of bad things are bound to happen
unless you follow the *statefile* format exactly. If the program segfaults
or does something unexpected, check for the following:

* Whitespace in the statefile. Make sure there is **none**.
* Trailing commas or other symbols.
* Typos.
* Incorrect bounds (e.g. `1r8`).

## License

`busybeaver` is licensed under the MIT License.

For the exact terms, see the [LICENSE file](./LICENSE).
