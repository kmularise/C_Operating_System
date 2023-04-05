#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

// typedef enum e_status{

// }	t_status;

// typedef struct s_phillo{
// 	pthread_mutex_t	*count_mutex;
// 	long long		*count;
// } t_phillo;

//철학자 한명당 정보 담기
typedef struct s_thread_info{
	int	idx;
}	t_thread_info;

#endif