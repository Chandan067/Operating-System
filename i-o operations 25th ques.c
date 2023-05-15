#include <stdio.h>

int main()
{
    int n = 100; // number of blocks in file
    int block_size = 512; // size of each block in bytes
    int fcb = 1; // number of blocks for file control block (FCB)
    int ib = 1; // number of blocks for index block (only for indexed allocation)

    // contiguous allocation
    int cont_start = 0; // starting block of contiguous allocation
    int cont_end = n - 1; // ending block of contiguous allocation
    int cont_io = 0; // number of disk I/O operations for contiguous allocation

    // linked allocation
    int linked_start = 0; // starting block of linked allocation
    int linked_end = n - 1; // ending block of linked allocation
    int linked_io = 0; // number of disk I/O operations for linked allocation

    // indexed allocation
    int indexed_io = 0; // number of disk I/O operations for indexed allocation

    // adding block at beginning
    cont_end++; // increment ending block for contiguous allocation
    linked_start++; // increment starting block for linked allocation
    indexed_io++; // read index block for indexed allocation

    // adding block in middle
    int mid = n / 2; // middle block
    if (cont_end < mid) { // new block is before middle block
        cont_end++; // increment ending block for contiguous allocation
        cont_io++; // write new block to disk for contiguous allocation
    }
    else { // new block is after middle block
        linked_start++; // increment starting block for linked allocation
        linked_io++; // read next block for linked allocation
    }
    indexed_io++; // read index block for indexed allocation

    // adding block at end
    cont_end++; // increment ending block for contiguous allocation
    linked_end++; // increment ending block for linked allocation
    indexed_io++; // read index block for indexed allocation

    // calculate total disk I/O operations
    cont_io += (cont_end - cont_start + 1); // read/write all blocks for contiguous allocation
    linked_io += (linked_end - linked_start + 1); // read/write all blocks for linked allocation
    indexed_io += ib; // write new index block for indexed allocation

    printf("Contiguous allocation: %d disk I/O operations\n", cont_io);
    printf("Linked allocation: %d disk I/O operations\n", linked_io);
    printf("Indexed allocation: %d disk I/O operations\n", indexed_io);

    return 0;
}
