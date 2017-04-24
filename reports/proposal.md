# SoftSysPeskyPintos Project 2: Virtual Memory in C

## By Bonnie Ishiguro, Andrew Pan, Apurva Raman, Amy Wu

## Project Goal

The goal of this project is to gain a comprehensive understanding of the theory and implementation of virtual memory.  We are planning to implement a version of virtual memory in C, using either Arduino or the Stanford Pintos OS.


Lower bound: A working, if inefficient, implementation of virtual memory. Includes page table and virtual memory mapping. May have things such as threading from existing implementations or may just handle replacing loads/read/write in assembly with a different set of instructions. 

Stretch goal: A working implementation of VM that includes more advanced implementation strategies other replacement policies, sharing)

## Current Progress

We have read Ch3 of TOS on virtual memory and address translation. We have also looked at implementations of virtual memory on an Arduino and on Pintos (see our Annotated Bibliography section). We have outlined a set of tasks to complete for the project in our [project backlog](https://trello.com/b/jNHxdxiL/softsyspeskypintos).



## Annotated Bibliography

### ThinkOS Chapter 3: Virtual Memory

[http://greenteapress.com/thinkos/html/thinkos004.html](http://greenteapress.com/thinkos/html/thinkos004.html)

We each read this chapter before starting this project, and we will use it as a reference to the basics of virtual memory theory.

### Virtual memory project for creating a system to manage memory on a USB

"Project 5: Virtual Memory." COS 318 : Operating System. Princeton University, 2004. Web. 26 Mar. 2017.

[https://www.cs.princeton.edu/courses/archive/fall04/cos318/projects/5.html](https://www.cs.princeton.edu/courses/archive/fall04/cos318/projects/5.html)

This is a virtual memory project description in Princeton’s Operating Systems class that we will reference as an example of how to structure our virtual memory implementation.

### Stanford Pintos project:

"Project 3: Virtual Memory." Pintos Projects. Stanford University, n.d. Web. 26 Mar. 2017. 

[https://web.stanford.edu/class/cs140/projects/pintos/pintos_4.html#SEC53](https://web.stanford.edu/class/cs140/projects/pintos/pintos_4.html#SEC53)

This is a virtual memory project description in Stanford’s Operating Systems class that we might use as a starting point for our implementation.

### Pintos Reference Guide:

Pfaff, Ben.  “Pintos.”  Stanford University, n.d.  Web.  26. Mar. 2017.

[https://web.stanford.edu/class/cs140/projects/pintos/pintos.pdf](https://web.stanford.edu/class/cs140/projects/pintos/pintos.pdf)

This includes Pintos documentation, the four projects in Stanford’s Operating Systems class, and a guide to setting up Pintos on our machines.

### Arduino virtual memory library: 

[https://rhelmus.github.io/virtmem/index.html](https://rhelmus.github.io/virtmem/index.html)

Existing implementation of a virtual memory system that runs on Arduino to increase the available amount of RAM through an additional memory source

## Project Backlog

[Link to our Trello Board](https://trello.com/b/jNHxdxiL/softsyspeskypintos)

## Potential Roadblocks

We could face potential roadblocks from the setup of the environment we choose to work in.  One of the pathways we are considering taking this project in involves a messy setup process that may take more time than we expect.  We also may have roadblocks in the scope of our project because we are not certain whether our project ideas would be appropriate for the duration of three sprints, and working with an OS without significant documentation could make it difficult to extend our project beyond existing project assignments.  
