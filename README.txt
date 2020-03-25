Part 1: Virtual Memory Questions

1. A certain computer provides its users with a virtual-memory space of 232 bytes. 
   The computer has 218 bytes of physical memory. The virtual  memory is implemented
   by paging, and the page size is 4096 bytes. A user process generates the virtual address 
   11123456 (this is in hexadecimal (base 16)). Explain how the system establishes the 
   corresponding physical location. Distinguish between software and hardware operations. 
   Feel free to use a diagram (simple ASCII is fine) if you wish, but that’s not required. 

2. Assume we have a demand-paged memory. The page table is held in registers. It takes 8 
   milliseconds to service a page fault if an empty page is available or if the replaced 
   page is not modified, but 20 milliseconds if the replaced page was modified. Memory access 
   time is 100 nanoseconds. Assume that the page to be replaced is modified 70% of the time. 
   What is the maximum acceptable page-fault rate for an effective access time of no more than 
   200 nanoseconds? Show your work.


Part 2: The ls command
