# Preliminary Report
Apurva Raman, Amy Wu, Bonnie Ishiguro, Andrew Pan

Our team’s learning goal for this project is to gain a comprehensive understanding of the theory and implementation of virtual memory.  We are planning to implement a version of virtual memory in C using the Stanford Pintos OS.  Our lower bound is a working, if inefficient, implementation of virtual memory that involves a page table and virtual memory mapping.  We are planning to work off of earlier projects in the Stanford course and would therefore include an implementation of threading and user programs.  Our stretch goal is to have a working implementation of virtual memory that includes more advanced implementation strategies, such as replacement policies and sharing of data between processes.


To see the tasks that we completed during this sprint, along with evidence of completion, see the cards and card comments in the “Done” list on our [Trello board](https://trello.com/b/jNHxdxiL/softsyspeskypintos) or see the list below:

| Completed Tasks  | Evidence |
| ------------- | ------------- |
| Research VM Theory and bring in notes on topics in VM  | [Link](https://docs.google.com/document/d/1o5RZs28DHMHPYEKhko-TQksUKRmZS9w19s89c3lyUyw/edit)  |
| Get together to set up development environment. Get Pintos and Arduino working  | [Link](https://trello.com/c/I4mBAkmO/7-determine-which-hardware-libraries-or-existing-projects-to-use-have-a-meeting-and-make-pro-con-bullet-points-1-to-1-5-hr) |
| Choose either Pintos or Arduino. Have a meeting to make a pros/cons on both paths. We chose Pintos  | [Link](https://github.com/bishiguro/SoftSysPeskyPintos/blob/master/configure_pintos.sh) |
| Get together to draw a block diagram of VM to understand how VM works. Understand TLB, Page Tables, Address Translation  | [Link](https://drive.google.com/drive/folders/0B6n1zsVOIMe6VXNFM280UnhmVDg) |
| Ask Ben during class time to confirm/review our block diagram to see if we need to make additional changes in our current understanding of VM  | We talked to Ben and we concluded that we want to expand our replacement procedure when we get there in implementation  |
| Re-evaluate project MVP and stretch goals  | Our team’s learning goal for this project is to gain a comprehensive understanding of the theory and implementation of virtual memory. |
| Work through Projects 1 and 2 in Pintos in order to start VM implementation  | [Link](https://docs.google.com/document/d/1pPJVoXkzB9vAcKZOBHPdK81diZmTF2zh0bMJQ_gvWGM/edit)  |
| Setup script to get Pintos running  | [Link](https://github.com/bishiguro/SoftSysPeskyPintos/blob/master/configure_pintos.sh) |


After successfully installing Pintos, we attempted to walk through the threads exercise in Project 1 of the Stanford OS course.  The following outlines the steps we took to use GDB to attempt to step through the alarm-multiple test program provided with Pintos.  Our understanding is that alarm-multiple uses thread.c and is running on the Pintos kernel, kernel.o.


Inputs with gdb:
~/pintos$ pintos --gdb --qemu -- run alarm-multiple

    Use of literal control characters in variable names is deprecated at /home/bishiguro/pintos/utils/pintos line 911.
    Prototype mismatch: sub main::SIGVTALRM () vs none at /home/bishiguro/pintos/utils/pintos line 935.
    Constant subroutine SIGVTALRM redefined at /home/bishiguro/pintos/utils/pintos line 927.
    qemu-system-x86_64 -hda /tmp/TXlHkLOEBb.dsk -m 4 -net none -serial stdio -s -S

    WARNING: Image format was not specified for '/tmp/TXlHkLOEBb.dsk' and probing guessed raw.
             Automatically detecting the format is dangerous for raw images, write operations on block 0 will be restricted.
             Specify the 'raw' format explicitly to remove the restrictions.
    warning: TCG doesn't support requested feature: CPUID.01H:ECX.vmx [bit 5]

    We learned that to run pintos-gdb, we need to be in the directory where kernel.o lives.

    bishiguro@bishiguro-Latitude-E6430:~/pintos/threads/build$ pintos-gdb kernel.o
    *** /pintos/misc/gdb-macros does not exist ***
    *** Pintos GDB macros will not be available ***
    GDB introduction and instructions ...
    Reading symbols from kernel.o...done.
    (gdb) target remote localhost:1234
    Remote debugging using localhost:1234
    0x0000fff0 in ?? ()
    (gdb) break thread.c: 228
    Breakpoint 1 at 0xc0020df5: file ../../threads/thread.c, line 228.
    (gdb) step
    Cannot find bounds of current function

We were able to set breakpoints in thread.c, but we have not figured out why gdb cannot find the bounds of a function.


Present a product backlog for the next sprint that represents a concrete plan that will keep the entire team productively engaged and get you to your stated goals (this can be a link to your Trello board). If you had trouble putting together evidence for your cards in the previous sprints, adjust your new cards accordingly.

https://trello.com/b/jNHxdxiL/softsyspeskypintos

Research VM specific implementation strategies: 1 page of notes each

Debug threading in Pintos exercise 1 or understand solution

Deliverable: notes on what is occurring in exercise 1 and what issues we ran into, demo of working code

Understand Pintos User Programs exercise 2

Deliverable: notes on what is happening in exercise 2, and any issues we run into if we attempt to implement it, demo of working code


Implement:
* Pintos Virtual memory project
* Pages
* Stack growth
* Page tables / Address mapping
* User memory during system calls
* Error handling for page faults

The potential roadblocks we may face include having difficulty implementing or understanding the threading or user program projects in the Stanford OS course. Having working versions of these components is necessary before implementing virtual memory. These projects are considered difficult, and we will have to take substantial amount of time outside of class to get working versions of projects 1 and 2.  Another potential roadblock stems from the fact that we are working with an environment that we did not build from scratch, which could make debugging more difficult.

## Annotated Bibliography

### ThinkOS Chapter 3: Virtual Memory

[http://greenteapress.com/thinkos/html/thinkos004.html](http://greenteapress.com/thinkos/html/thinkos004.html)
[http://greenteapress.com/thinkos/html/thinkos010.html](http://greenteapress.com/thinkos/html/thinkos010.html)

We each read TOS chapter 4 before starting this project, and we will use it as a reference to the basics of virtual memory theory. It gave us a general overview of the topic, but we needed to consult other resources to learn about the specific parts of virtual memory we would need to implement (ex. TLB, replacement policies, page table). We also read TOS chapter 9 to understand basics of threading in order to build earlier projects in the Stanford Pintos project.

### Stanford Pintos Project:

"Project 3: Virtual Memory." Pintos Projects. Stanford University, n.d. Web. 26 Mar. 2017.

[https://web.stanford.edu/class/cs140/projects/pintos/pintos_4.html#SEC53](https://web.stanford.edu/class/cs140/projects/pintos/pintos_4.html#SEC53)

This is a virtual memory project description in Stanford’s Operating Systems class that is the starting point for our implementation.  We plan to use this project because it is based on the Stanford Pintos OS, which means that we would not have to build basic operating system functionality from scratch.  This also gives us a structure from which to design our virtual memory system.

### Pintos Installation and Project Guide

Pfaff, Ben.  “Pintos.”  Stanford University, n.d.  Web.  26. Mar. 2017.

[https://web.stanford.edu/class/cs140/projects/pintos/pintos.pdf](https://web.stanford.edu/class/cs140/projects/pintos/pintos.pdf)

This includes Pintos documentation, the four projects in Stanford’s Operating Systems class, and a guide to setting up Pintos on our machines.  In addition to the virtual memory project description referenced above, this includes the first two course projects on threading and user programs, which we will need to either implement or understand solution implementations in order to build a base for our VM.  We used this guide to verify that our Pintos installations were successful by running the alarm-multiple program.

### Installing Pintos with QEMU

[https://pintosiiith.wordpress.com/2012/09/13/install-pintos-with-qemu/](https://pintosiiith.wordpress.com/2012/09/13/install-pintos-with-qemu/)

This is a guide to how to install Pintos using QEMU as the hypervisor rather than Bochs, which speeds up the emulation substantially. We used it to fix some issues we had with paths to Pintos source files being incorrect. It did not explain how or why to use QEMU, but we used the other documentation to determine which hypervisor to use.
