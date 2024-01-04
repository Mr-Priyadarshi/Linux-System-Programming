/*
fd1 and fd2 are file descriptors for the same file "abc" because dup duplicates the file descriptor fd1. 
Both fd1 and fd2 refer to the same open file description.

Each read system call advances the file offset for the file descriptor from where it reads. 
The file offset keeps track of the current position within the file.

Here's what happens with the file offsets after each read operation:

read(fd1, buf, 100); (R1) reads 100 bytes from the file associated with fd1 starting from the current file offset. 
After this operation, the file offset for fd1 is advanced by 100 bytes.

read(fd2, buf, 10); (R2) reads 10 bytes from the file associated with fd2 starting from the current file offset of fd2. 
After this operation, the file offset for fd2 is advanced by 10 bytes. 
Importantly, since fd2 was duplicated from fd1, the file offset for fd1 is also advanced by 10 bytes to maintain consistency between the two descriptors.

read(fd1, buf, 10); (R3) reads 10 bytes from the file associated with fd1 starting from the current file offset of fd1. 
After this operation, the file offset for fd1 is advanced by an additional 10 bytes. 
This means that the file offset for fd1 is now 120 bytes ahead of its initial position.

read(fd2, buf, 100); (R4) reads 100 bytes from the file associated with fd2 starting from the current file offset of fd2. 
After this operation, the file offset for fd2 is advanced by 100 bytes. 
Importantly, since fd2 was duplicated from the updated fd1 (with a file offset advanced by 10 bytes in R3), the file offset for fd1 is also advanced by 100 bytes to maintain consistency between the two descriptors. 
Therefore, the file offset for fd1 is now 220 bytes ahead of its initial position.

In summary, after the read operations, the file offset for both fd1 and fd2 has advanced. 
For fd1, the offset is 220 bytes ahead of its initial position, and for fd2, the offset is 100 bytes ahead of its initial position.
*/