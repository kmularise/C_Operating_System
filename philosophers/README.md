```
./philo num_philo time_to_die time_to_eat time_to_sleep num_times_philo_must_eat
```
* number_of_philosophers
If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.

• To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them

```c
struct timeval {
			time_t       tv_sec;   /* seconds since Jan. 1, 1970 */
			suseconds_t  tv_usec;  /* and microseconds */
	};
```