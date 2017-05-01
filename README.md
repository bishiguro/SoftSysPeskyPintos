## `virtmem`: Virtual Memory in C
##### Implementation and analysis of page replacement policies
## Authors

[Apurva Raman](https://github.com/apurvaraman/), [Bonnie Ishiguro](https://github.com/bishiguro/), [Andrew Pan](https://github.com/apan64), [Amy Wu](https://amybohbeanii.github.io/)

## About `virtmem`

This student project was created as part of Olin College of Engineering’s Software Systems course. For more details on this project, check out our [final report on our project website](https://bishiguro.github.io/SoftSysPeskyPintos/).

For this project, we implemented several page fault handlers and analyzed their performance. We used the structure provided in the [Operating Systems Principles course](http://www3.nd.edu/~cpoellab/teaching/cse30341/project4.html) at Notre Dame.

Our goal in doing this project was to understand virtual memory (VM), an important part of an OS, so we decided to analyze the different components of VM and techniques for implementation strategies. A comprehensive understanding of VM means knowing how virtual addresses are mapped to physical addresses. The abstraction that virtual memory provides is that each process has its own chunk of memory, isolated from all other processes and allows for a larger virtual memory space to be used than just the amount of physical memory available. The main component that allows this concept to work is the page table, which stores the mapping, and the techniques are the various page replacement algorithms.

## Setup and Usage

Clone this repository and change into its directory: `cd SoftSysPeskyPintos`

To compile the project from source using the makefile:

```
make circ_buffer.o
make virtmem
```

To run the program: ```./virtmem npages nframes rand|fifo|second-chance scan|sort|focus```

Argument 1: `npages` is the number of pages in virtual memory.

Argument 2: `nframes` is the number of frames in physical memory.

Argument 3: The implemented replacement polices are `rand`([random replacement](https://en.wikipedia.org/wiki/Page_replacement_algorithm#Random)), `fifo`( [First-In-First-Out](https://en.wikipedia.org/wiki/Page_replacement_algorithm#First-in.2C_first-out) using a circular buffer), and `second-chance` ([Clock](https://en.wikipedia.org/wiki/Page_replacement_algorithm#Clock) which behaves like [second chance FIFO](https://en.wikipedia.org/wiki/Page_replacement_algorithm#Second-chance) using a circular buffer).

Argument 4: Program to run (see [program.c](https://github.com/bishiguro/SoftSysPeskyPintos/blob/master/program.c) for more about each program).

Examples to run the project:

```
./virtmem 15 10 rand sort
./virtmem 15 10 fifo focus
```
## Additional Libraries
All of `virtmem`’s dependencies are standard C libraries.

## License
This software is provided under the [MIT License](https://github.com/bishiguro/SoftSysPeskyPintos/blob/master/LICENSE.md).
