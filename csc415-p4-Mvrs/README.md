# csc415-p4

## Compile Instructions:

```bash
saschaMars at Marlons-PC in csc415-p4-Mvrs on master [!?]
$ make threadracer
```

## Run Instructions:

```bash
saschaMars at Marlons-PC in csc415-p4-Mvrs on master [!?]
$ ./threadracer
```

## Use of pthread_create()

```c
    // creating the thread

    for (t = 0; t < NUM_THREADS; t++)
    {
        threadExecute = pthread_create(&threads[t], &attr, executeThread, (void *)t);
        if (threadExecute)
        {
            fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", threadExecute);
            exit(-1);
        }
    }
```

## Use of pthread_join()

```c
    // now to wait for the thread to finalize

    for (t = 0; t < NUM_THREADS; t++)
    {
        threadExecute = pthread_join(threads[t], &status);

        if (threadExecute)
        {
            fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", threadExecute);
            exit(-1);
        }

        fprintf(stderr, "Each thread completed with final status: %d\n", (int)gloablId);
    }
```

### What I learned from this assignment
The use of parrallel processing of its base theory. 
For S\starters we execute each task in a FIFO implementation. 
As each process is shared in a single-memory (I believe) . 
Also, I chose to not use a pointer for tid value because I belive it wouldn't effect the process. 
So, I changed it (not in push code) to this and still get the same output as I cast it to an int. 
```c
    int value = 0;
    int tid;
    tid = (int *)threadId;
```

### Final Thoughts
This was good use on preventing deadlock and learning the use of allowing each task to perform sequentially 
