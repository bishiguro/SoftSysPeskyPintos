## `virtmem`: Virtual Memory in C
##### Implementation and analysis of page replacement policies

### To download and for usage and setup instructions, check out our [github repository](https://github.com/bishiguro/SoftSysPeskyPintos).

## Authors

[Apurva Raman](https://github.com/apurvaraman/), [Bonnie Ishiguro](https://github.com/bishiguro/), [Andrew Pan](https://github.com/apan64), [Amy Wu](https://amybohbeanii.github.io/)


## Abstract

To understand virtual memory better, we built `virtmem`, a fully functional demand paged virtual memory in C following the guidance of [Notre Dame University’s VM project](http://www3.nd.edu/~cpoellab/teaching/cse30341/project4.html).  This project implementation allows us to understand the code mechanics of how the operating system handles memory addressing, page faults, and page replacement.


Our team explored implementations of virtual memory by working with processes and algorithms involved in looking up virtual addresses in the page table and handling page faults.  There are many commonly used algorithms for page replacement and documentation on how virtual memory works, and our team’s goal was to gain a better understanding of virtual memory by implementing parts of the system ourselves.  

## Background

Virtual memory refers to the memory addressing the OS uses for its processes, which is mapped to physical addresses through the usage of a page table.  On a request from a process to read or write to a position in memory, the memory management unit (MMU) attempts to look for the mapping from a virtual to physical address in the translation lookaside buffer (TLB).  If the address in not found in the buffer, the MMU then looks up the virtual address in the page table.  The mapping to the physical address is then added to the TLB, and the MMU attempts to find the virtual address in the TLB again.  When the virtual address is found in the TLB, the corresponding physical address is then passed to main memory so the address space can be read from or written to.

![Figure 1: Diagram of different components in Virtual Memory](https://github.com/bishiguro/SoftSysPeskyPintos/blob/gh-pages/images/empty_frame.jpg)

We focused our project on the implementation of a specific part of virtual memory, page replacement algorithms. This includes understanding how page faults occur and how to handle page faults by creating page replacement algorithms. A page fault occurs when the a process accesses an address in the page table that there isn’t a mapping from virtual to physical memory for, resulting in the page replace algorithm being called. There are many page replacement policies, such as random, first-in first-out (FIFO), least recently used (LRU), and second-chance.
The purpose of our project is to gain a general overview of Virtual Memory. We read ThinkOS Chapter 3: Virtual Memory to understand the different components that make up Virtual Memory (Refer to Figure 1). We read a previous project’s documentation on Virtual Memory in regard to Computer Architecture in order to understand that in the broader context, the concept of Virtual Memory is similar to caching. Understanding virtual memory is an important part of an Operating System and an implementation allows us to demonstrate mastery of the virtual memory concept. Specifically, our team was able to gain a comprehensive understanding of page faults, page table, frame table, disk, and page replacement algorithms random, fifo, and second-chance.  For further information from sources we used for information, we created an [annotated bibliography]() with a summary of each source.

## Implementation

Our goal for this project was to create a working virtual memory system to handle the mapping from virtual memory to physical memory. Due to the complexity of developing an entire virtual memory system with pages, frames, a page table, and the ability to write to disk, we chose to search for existing virtual memory projects and build upon those instead of creating a system entirely from scratch. We began with exploring virtual memory implementations on Arduino Uno’s and PintOS, a pseudo-OS developed for implementing different OS features as projects for a Stanford course.  After performing some preliminary implementation of both options, we chose to further explore the PintOS project with the intent of completing a virtual memory project in the OS.

After spending multiple weeks with trying to implement some of the features of PintOS necessary to begin working on virtual memory, we came to the conclusion that the multitude of issues we were running into from the OS was hindering our progress, and we pivoted our project to work on a different virtual memory project: Notre Dame’s Project V: Virtual Memory, which has a much simpler setup and a more readable code base.  This implementation uses only a page table and does not use a TLB. The main goal of our new virtual memory project was to implement a page fault handler that would manage interactions with the page table and page replacement.

Our page fault handler is called whenever there is an attempted access to a page that is not mapped to a frame, or when there is an attempted write to a page when all of the pages in the table have an existing mapping.  We implemented multiple page replacement algorithms to address these issues, starting with a random page replacement as an MVP and eventually moving into FIFO page replacement with a circular buffer.  We chose to use a circular buffer to implement FIFO because we knew the maximum size of the buffer had to be equal to the size of the page table, so having a fixed-size circular data structure was more efficient than creating a linked list. We also followed the architecture of implementing a frame table to understand how virtual memory is mapped to physical memory.


Results
Provide evidence demonstrating that what you built works. Though the details will be different for each project, screenshots and video are likely helpful. Include graphs or other data if appropriate.

In addition to creating your final report website, you will also perform two other tasks to prepare your work for release: clean up your code and write a README. Hopefully these should be trivial since you've been doing them all along.



## Results


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


## Learning Objectives
This project was intended to be a learning exercise for the team to get hands on experience with implementing an important component of VM, the page fault handler. We accomplished our learning goals, which were:
Learn about all the components of VM
In depth understanding of TLB
In depth understanding of Page Table
In depth understanding of different page replacement algorithms
Mapping of Virtual Address to Physical Address
Physical Memory versus Disk
Design decisions on how to implement a frame table
Data structure decisions on how to implement fifo.

While there are various other page replacement algorithms to implement, this project still proves to be a valuable learning experience for the team to gain in-depth knowledge in VM and experience implementing some page replacement algorithms.
