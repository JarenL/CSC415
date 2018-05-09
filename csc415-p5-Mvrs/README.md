# csc415-p5 

![AppVeyor](https://img.shields.io/appveyor/ci/gruntjs/grunt.svg)

## Part 1 - Threadracer

A extended version of the produce race condition. 
This assignment we add synchronization to eliminate of possible race conditions to produce
the correct number of threads.


Compile Instructions:
```
make threadracer
```
Run Instructions:
```
./threadracer
```

```c
void executeThread(void *threadId)
{
    int value = 0;
    int tid;
    tid = (int)threadId;

    pthread_mutex_lock(&m);

    value = gloablId;
    fprintf(stderr, "Hello I'm thread #%d\n", tid);
    nanosleep(&ts, NULL);

    value += 10;

    fprintf(stderr, "Thread local variable: %d and now Adding 10 -> Thread #%d\n", tid, value);

    nanosleep(&ts, NULL);

    gloablId = value;

    pthread_mutex_unlock(&m); //end of Critical Section

    pthread_exit((void *)threadId);
}
```

## Problems I faced (Part 1)
Accumulating a global variable count of 10, instead of 100.
Problem was solved by setting my value to my globalId.

## Part 2 - Producer and Consumer

Implemented Producers and Consumer threads with a bounded buffer queue of N elements

Compile Instructions:
```
make pandc
```
Run Instructions:
```
./pandc
```

## Consumer Function

```c
void *consumer(void *param)
{
    consumers *consumer = (consumers *)param;
    int capacity = consumer->consumerFillCount;
    int cmsID = consumer->consumerId;

    int count = 0;

    while (count++ < capacity) // P * X / C
    {
        sleep(consumer->totalConsumerTime);
        sem_wait(&full);
        pthread_mutex_lock(&m);

        // set the cBufferIndex = dequeue();

        // prints item and consume
        printf("\n%d is consumed by thread-> %d", buffer[cBufferIndex], cmsID + 1); // consumption

        consumerArray[consumerCounter] = buffer[cBufferIndex];
        consumerCounter++;

        // iterate through the consumer buffer until reached N size buffers

        if (cBufferIndex == (bufferAmt - 1))
        {
            cBufferIndex = 0; // reset to 0
        }
        else
        {
            cBufferIndex++;
        }

        // sleep(consumer->totalConsumerTime);

        pthread_mutex_unlock(&m);
        sem_post(&empty);
    }

    pthread_exit(0);
}
```

## Producer Function

```c
void *producer(void *param)
{
    producers *producer = (producers *)param;
    int capacity = producer->producerFillCount;
    int prodId = producer->producerId;

    int count = 0;

    while (count++ < capacity) // X
    {
        // sleep(producer->totalProducerTime);
        sem_wait(&empty);
        pthread_mutex_lock(&m);

        printf("\n%d was produced by thread-> %d", count_items, prodId + 1);

        //enqueue item in buffer
        // buffer[pBufferIndex] = count_items;
        producerArray[producerCounter] = count_items;

        //enqueue item in buffer
        buffer[pBufferIndex] = count_items;
        // count++;
        count_items++;
        producerCounter++;
        buffer_capacity++;

        // iterate through the proudcer buffer until reached N size buffers
        if (pBufferIndex == (bufferAmt - 1))
        {
            pBufferIndex = 0; // reset
        }
        else
        {
            pBufferIndex++;
        }

        sleep(producer->totalProducerTime);

        pthread_mutex_unlock(&m);
        sem_post(&full);
    }

    pthread_exit(0);
}
```

## Output
```bash
marlon@Marlons-PC:/mnt/c/Users/johns/Desktop/csc415-p5-Mvrs/part2$ ./pandc 7 5 3 15 1 1
N = 7 P = 5 C = 3 X = 15 Ptime = 1 Ctime = 1

Start time: Wed Apr 25 20:18:57 2018


1 was produced by thread-> 1
2 was produced by thread-> 1
3 was produced by thread-> 1
4 was produced by thread-> 4
5 was produced by thread-> 5
6 was produced by thread-> 2
1 is consumed by thread-> 3
2 is consumed by thread-> 2
7 was produced by thread-> 3
3 is consumed by thread-> 1
8 was produced by thread-> 1
9 was produced by thread-> 4
4 is consumed by thread-> 3
5 is consumed by thread-> 2
10 was produced by thread-> 5
6 is consumed by thread-> 1
11 was produced by thread-> 2
12 was produced by thread-> 3
7 is consumed by thread-> 3
8 is consumed by thread-> 2
13 was produced by thread-> 1
9 is consumed by thread-> 1
14 was produced by thread-> 4
15 was produced by thread-> 5
10 is consumed by thread-> 3
11 is consumed by thread-> 2
16 was produced by thread-> 2
12 is consumed by thread-> 1
17 was produced by thread-> 3
18 was produced by thread-> 1
13 is consumed by thread-> 3
14 is consumed by thread-> 2
19 was produced by thread-> 4
15 is consumed by thread-> 1
20 was produced by thread-> 5
21 was produced by thread-> 2
16 is consumed by thread-> 3
17 is consumed by thread-> 2
22 was produced by thread-> 3
18 is consumed by thread-> 1
23 was produced by thread-> 1
24 was produced by thread-> 4
19 is consumed by thread-> 3
20 is consumed by thread-> 2
25 was produced by thread-> 5
21 is consumed by thread-> 1
26 was produced by thread-> 2
27 was produced by thread-> 3
22 is consumed by thread-> 3
23 is consumed by thread-> 2
28 was produced by thread-> 1
24 is consumed by thread-> 1
29 was produced by thread-> 4
30 was produced by thread-> 5
25 is consumed by thread-> 3
26 is consumed by thread-> 2
31 was produced by thread-> 2
27 is consumed by thread-> 1
32 was produced by thread-> 3
33 was produced by thread-> 1
28 is consumed by thread-> 3
29 is consumed by thread-> 2
34 was produced by thread-> 4
30 is consumed by thread-> 1
35 was produced by thread-> 5
36 was produced by thread-> 2
31 is consumed by thread-> 3
32 is consumed by thread-> 2
37 was produced by thread-> 3
33 is consumed by thread-> 1
38 was produced by thread-> 1
39 was produced by thread-> 4
34 is consumed by thread-> 3
35 is consumed by thread-> 2
40 was produced by thread-> 5
36 is consumed by thread-> 1
41 was produced by thread-> 2
42 was produced by thread-> 3
37 is consumed by thread-> 3
38 is consumed by thread-> 2
43 was produced by thread-> 1
39 is consumed by thread-> 1
44 was produced by thread-> 4
45 was produced by thread-> 5
40 is consumed by thread-> 3
41 is consumed by thread-> 2
46 was produced by thread-> 2
42 is consumed by thread-> 1
47 was produced by thread-> 3
48 was produced by thread-> 1
43 is consumed by thread-> 3
44 is consumed by thread-> 2
49 was produced by thread-> 4
45 is consumed by thread-> 1
50 was produced by thread-> 5
51 was produced by thread-> 2
46 is consumed by thread-> 3
47 is consumed by thread-> 2
52 was produced by thread-> 3
48 is consumed by thread-> 1
53 was produced by thread-> 1
54 was produced by thread-> 4
49 is consumed by thread-> 3
50 is consumed by thread-> 2
55 was produced by thread-> 5
51 is consumed by thread-> 1
56 was produced by thread-> 2
57 was produced by thread-> 3
52 is consumed by thread-> 3
53 is consumed by thread-> 2
58 was produced by thread-> 1
54 is consumed by thread-> 1
59 was produced by thread-> 4
60 was produced by thread-> 5
55 is consumed by thread-> 3
56 is consumed by thread-> 2
61 was produced by thread-> 2
57 is consumed by thread-> 1
62 was produced by thread-> 3
63 was produced by thread-> 1
58 is consumed by thread-> 3
59 is consumed by thread-> 2
64 was produced by thread-> 4
Producer Thread Joined:  1
60 is consumed by thread-> 1
65 was produced by thread-> 5
66 was produced by thread-> 2
61 is consumed by thread-> 3
62 is consumed by thread-> 2
67 was produced by thread-> 3
63 is consumed by thread-> 1
68 was produced by thread-> 4
69 was produced by thread-> 5
64 is consumed by thread-> 3
65 is consumed by thread-> 2
70 was produced by thread-> 2
66 is consumed by thread-> 1
71 was produced by thread-> 5
72 was produced by thread-> 4
67 is consumed by thread-> 3
68 is consumed by thread-> 2
73 was produced by thread-> 3
74 was produced by thread-> 3
75 was produced by thread-> 2
69 is consumed by thread-> 3
Producer Thread Joined:  2
Producer Thread Joined:  3
Producer Thread Joined:  4
70 is consumed by thread-> 2
Producer Thread Joined:  5
71 is consumed by thread-> 1
72 is consumed by thread-> 3
73 is consumed by thread-> 2
74 is consumed by thread-> 1
75 is consumed by thread-> 1
Consumer Thread Joined:  1
Consumer Thread Joined:  2
Consumer Thread Joined:  3
End time: Wed Apr 25 20:20:14 2018

Producer Array  | Consumer Array
1               | 1
2               | 2
3               | 3
4               | 4
5               | 5
6               | 6
7               | 7
8               | 8
9               | 9
10              | 10
11              | 11
12              | 12
13              | 13
14              | 14
15              | 15
16              | 16
17              | 17
18              | 18
19              | 19
20              | 20
21              | 21
22              | 22
23              | 23
24              | 24
25              | 25
26              | 26
27              | 27
28              | 28
29              | 29
30              | 30
31              | 31
32              | 32
33              | 33
34              | 34
35              | 35
36              | 36
37              | 37
38              | 38
39              | 39
40              | 40
41              | 41
42              | 42
43              | 43
44              | 44
45              | 45
46              | 46
47              | 47
48              | 48
49              | 49
50              | 50
51              | 51
52              | 52
53              | 53
54              | 54
55              | 55
56              | 56
57              | 57
58              | 58
59              | 59
60              | 60
61              | 61
62              | 62
63              | 63
64              | 64
65              | 65
66              | 66
67              | 67
68              | 68
69              | 69
70              | 70
71              | 71
72              | 72
73              | 73
74              | 74
75              | 75

Consumer and Produce Arrays Match!
Duration of Execution: 77 secs
```

## Problems I faced (Part 2)
I had issues printing out the proper values of my consumer and producer array. 
At times I got a bunch of zeros then values towards the end of each index.
Luckily this issue was later resolved. 

### What I learned from this assignment
How to make use of adding sycrhonization with the use of p_threads and semaphores. 
System programming is far more difficult to grasp in c than I thought. 
The use of semaphores states are changed atomically, which just isn't a simple variable, it's a larger construct. 


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
