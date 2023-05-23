<div align='center'> <h1>Philosophers</h1> </div>

<div align='center'> <h2>I never thought philosophy would be so deadly</h2> </div> 

The "Dining Philosophers problem" is a classic computer science synchronization problem that illustrates issues with resource allocation and concurrency.

## introduction
The Dining Philosophers problem presents a challenging scenario that explores concurrency and resource allocation. In this project, we tackle this problem using threads, where each philosopher is represented by a separate thread.

## Objective of the Project

* Solve the Dining Philosophers problem using thread-based concurrency and mutexes.
* Design an efficient solution that allows philosophers to dine concurrently while preventing conflicts.
* Ensure proper resource allocation by using mutexes to control access to shared forks.
* Implement synchronization mechanisms to prevent deadlock and race conditions.
* Gain practical experience in utilizing mutexes for managing critical sections of code.
* Deepen understanding of thread-based systems, resource allocation, and synchronization techniques.
* Enhance problem-solving skills in the context of concurrent programming.
* Provide a solid foundation for further exploration of concurrency, mutexes, and related challenges in software development.



## Skills
* Multi Threading
* Mutexs
* processing time optimization

## Rules
* Your(s) program(s) should take the following arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
* number_of_philosophers: The number of philosophers and also the number of forks.
* time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
* time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
* time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
* number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
* Each philosopher has a number ranging from 1 to number_of_philosophers.
* Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philoso- pher number N + 1.
** About the logs of your program:
* Any state change of a philosopher must be formatted as follows:
* ◦ timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
  ◦ timestamp_in_ms X is sleeping
  ◦ timestamp_in_ms X is thinking
  ◦ timestamp_in_ms X died
* A displayed state message should not be mixed up with another message.
* A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
* Again, philosophers should avoid dying!
* Your program must not have any data races.
### The specific rules for the mandatory part are:
* Each philosopher should be a thread.
* There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
* To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.
