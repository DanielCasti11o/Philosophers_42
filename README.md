# Philosophers

![C](https://img.shields.io/badge/C-A8B9CC?style=flat-square&logo=c&logoColor=black)
![pthreads](https://img.shields.io/badge/POSIX-pthreads-555?style=flat-square)
![42](https://img.shields.io/badge/42-philo-000?style=flat-square)

Dining philosophers simulation in C with POSIX threads. Each philosopher is a thread, each fork a
`pthread_mutex_t`, and a separate monitor thread detects starvation and ends the simulation.

## Usage

```sh
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

```sh
./philo 5 800 200 200        # should run indefinitely
./philo 5 800 200 200 7      # stops once every philosopher has eaten 7 times
./philo 4 310 200 100        # a philosopher dies
./philo 1 800 200 200        # single fork → dies at 800 ms
```

All times are in milliseconds. Arguments must be positive integers below `INT_MAX`; at most 200 philosophers.

Output, one line per state change, timestamped relative to the simulation start:

```
<ms> <id> has taken a fork
<ms> <id> is eating
<ms> <id> is sleeping
<ms> <id> is thinking
<ms> <id> died
```

## Design

```
                 ┌───────────── t_datash (shared) ─────────────┐
                 │ forks[n]   : pthread_mutex_t                │
                 │ printfs    : serializes stdout              │
                 │ lock_data  : last_eat, meal counters        │
                 │ stop       : dead_flag (end of simulation)  │
                 └─────────────────────────────────────────────┘
  philo[0] ─┐        philo[1] ─┐        ...        monitor
  thread    │        thread    │                    thread
  left  = forks[i]                                  polls every philosopher
  right = forks[(i + 1) % n]                        every 100 µs
```

**Threads**
- `n` philosopher threads running `do_routine`: take forks → eat → release → sleep → think.
- 1 monitor thread (`monitor_keep`) that checks `now - last_eat > time_to_die` for every philosopher, prints `died` and raises `dead_flag`.
- `main` joins the monitor first, then all philosopher threads, then destroys the mutexes and frees everything.

**Fork assignment and deadlock avoidance**
- Philosopher `i` owns `forks[i]` on the left and `forks[(i + 1) % n]` on the right, which forms a circular resource graph.
- Even-indexed philosophers start delayed by `time_to_eat / 2`. That desynchronizes neighbors so the circular wait
  (everyone holding their left fork) doesn't occur at startup, and odd/even groups alternate eating.
- Thread creation is spaced by 100 µs to reduce start-up skew.

**Shared state**
- `printfs`: every log line is printed under this mutex so lines never interleave.
- `lock_data`: guards `last_eat` and the per-philosopher meal count; `last_eat` is updated as soon as both forks are held.
- `stop`: guards the end-of-simulation flag that the monitor sets and the philosophers poll between actions.
- When the optional meal limit is given, each philosopher increments a shared `eat_fin` counter on reaching it; when it equals `n` the simulation stops.

**Edge case**
- `n == 1`: only one fork exists. The philosopher takes it, waits `time_to_die` and the monitor reports the death.

**Timing**
- Timestamps come from `gettimeofday()` converted to milliseconds.
- Eating and sleeping use `usleep(t * 1000)`; the monitor loop runs at 100 µs resolution.

## Layout

```
include/philo.h      structs (t_datash, t_philo, t_pth), state enum, prototypes
src/main.c           argument flow, monitor creation, joins
src/checkargs.c      argument validation
src/inits.c          shared data, fork mutexes, philosopher structs
src/routine.c        philosopher routine, fork acquisition, monitor loop
src/update.c         meal accounting, death check, stop flag
src/utils_macros.c   synchronized logging, single-philosopher case, last-meal update
src/sleep.c          time/stop helpers
src/ft_utils.c       atoi/atol, time in ms
src/free.c           mutex destruction and cleanup
```

## Debugging

```sh
make FLAGS="-Wall -Wextra -Werror -g3 -I./include -fsanitize=thread"   # data races
valgrind --tool=helgrind ./philo 5 800 200 200 3                       # lock-order / race checks
```
