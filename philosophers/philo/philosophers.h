#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "libft/libft.h"

#define AVAILABLE 0
#define USED 1

typedef struct s_fork{
	int	state;
	pthread_mutex_t mutex;
}	t_fork;

typedef struct s_philo{
	int					idx;
	int					eat_count;
	int					last_eat;
	long long			start_eat;
	pthread_mutex_t		fork_mutex;
	pthread_t			thread_id;
	struct s_setting	*common_info;
}	t_philo;

typedef struct s_setting{
	int				turn;
	int				total_eat;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	int				stop_idx;
	int				dead;
	int				philo_eat;
	long long		time_to_start;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	total_eat_mutex;
}	t_setting;

// typedef struct s_philo{
// 	int				idx;
// 	int				last_eat;
// 	pthread_mutex_t	fork_mutex;
// 	pthread_t		thread_id;
// 	t_setting		*common_info;
// }	t_philo;

// typedef enum e_status{

// }	t_status;

// typedef struct s_phillo{
// 	pthread_mutex_t	*count_mutex;
// 	long long		*count;
// } t_phillo;

//철학자 한명당 정보 담기
// typedef enum e_status{
// 	EATING,
// 	SLEEP,
// 	WAKEUP,
// }	t_status;

typedef struct s_thread_info{
	int	idx;
}	t_thread_info;

typedef struct s_common_resource{
	int	size;
	int	*forks;
	int	current_idx;
	t_thread_info **info_arr;
}	t_common_resource;

int			show_error(char *message);
int			check_valid_input(int argc, char **argv);
int			initiate_setting(t_setting *setting, char **argv);
long long	timestamp(void);
void		*execute_philo(void *data);
int			initiate_philos(t_setting *setting);
#endif