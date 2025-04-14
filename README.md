# Real Time Operating System 

## RTOS Interview Questions

### Basic RTOS Concepts

    What is an RTOS?

        A Real-Time Operating System (RTOS) is an OS designed to meet real-time constraints, 
        ensuring predictable task execution.

    What are the types of RTOS?

        Hard RTOS (strict timing), Soft RTOS (occasional delays allowed), and Firm RTOS 
        (missed deadlines reduce system quality but don’t cause failure).

    What is the difference between RTOS and a general-purpose OS?

        RTOS guarantees deterministic behavior and real-time constraints, while general-purpose 
        OS prioritizes fairness and throughput.

    What is task scheduling in RTOS?

        Task scheduling determines the order in which tasks execute based on priority and 
        scheduling algorithms.

    What are the types of task scheduling in RTOS?

        Preemptive, Cooperative, Round-robin, and Hybrid scheduling.

### Tasks & Multitasking

    What is task preemption in RTOS?

        Preemption allows a high-priority task to interrupt a lower-priority task.

    What is a task state in RTOS?

        Tasks can be in Running, Ready, Blocked, Suspended, or Terminated states.

    What is a thread in RTOS?

        A thread is the smallest execution unit within a task, sharing memory but having its own 
        execution context.

    What is priority inversion?

        Priority inversion occurs when a high-priority task is blocked by a lower-priority task holding a shared resource.

    How can priority inversion be solved?

    By using priority inheritance or priority ceiling protocols.

Synchronization & Interprocess Communication (IPC)

    What are semaphores in RTOS?

    Semaphores are signaling mechanisms used for task synchronization and resource management.

    What is the difference between a binary semaphore and a counting semaphore?

    A binary semaphore allows only two states (0 or 1), while a counting semaphore allows multiple resource instances.

    What is a mutex in RTOS?

    A mutex (mutual exclusion) ensures that only one task accesses a shared resource at a time.

    What is the difference between a mutex and a semaphore?

    A mutex provides ownership and priority inheritance, while a semaphore is a signaling mechanism without ownership.

    What are message queues in RTOS?

    Message queues allow tasks to send and receive messages in a First-In-First-Out (FIFO) manner.

Memory Management & Performance

    What is dynamic memory allocation in RTOS?

    Dynamic memory allocation assigns memory at runtime using functions like malloc(), but it's often avoided due to fragmentation risks.

    What is a real-time clock (RTC)?

    An RTC is a hardware timer that keeps track of time and triggers periodic events in an RTOS.

    What is the impact of interrupt latency in RTOS?

    High interrupt latency delays task execution and affects system responsiveness.

    What is a watchdog timer in RTOS?

    A watchdog timer resets the system if it detects a software failure or infinite loop.

    What is context switching in RTOS?

    Context switching is the process of saving the state of a running task and restoring another task's state.