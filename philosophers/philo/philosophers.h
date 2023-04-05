#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

#define AVAILABLE 0;
#define USED 1;
// typedef enum e_status{

// }	t_status;

// typedef struct s_phillo{
// 	pthread_mutex_t	*count_mutex;
// 	long long		*count;
// } t_phillo;

//철학자 한명당 정보 담기
typedef enum e_status{
	EATING,
	SLEEP,
	WAKEUP
}	t_status;

typedef struct s_thread_info{
	int	idx;
}	t_thread_info;

typedef struct s_common_resource{
	int	size;
	int	*forks;
	int	current_idx;
	t_thread_info **info_arr;
}	t_common_resource;

#endif