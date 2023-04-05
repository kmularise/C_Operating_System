#include "philosophers.h"

void	*execute_thread_function(void *data){
	t_thread_info	*thread_info;

	thread_info = (t_thread_info *)data;
	printf("thread okay? %d\n",thread_info->idx);
	return ((void *)thread_info);
}


pthread_t	*create_phillosophers(char *philo_num)
{
	pthread_t	*philosophers;
	int			size;

	size = ft_atoi(philo_num);//예외 처리
	//bigger than int, not number I have to handle errors
	philosophers = malloc(sizeof(pthread_t) * (size + 1));
	philosophers[size] = NULL;
	// return NULL;
	return (philosophers);
}

t_thread_info	*create_thread_info_node(int idx)
{
	t_thread_info	*node;

	node = malloc(sizeof(t_thread_info));
	node->idx = idx;
	return node;
}

t_thread_info	**create_thread_info_arr(char *philo_num)
{
	t_thread_info	**info_arr;
	int				size;
	int				i;

	size = ft_atoi(philo_num);
	info_arr = malloc(sizeof(t_thread_info *) * (size + 1));
	i = -1;
	while (++i < size)
		info_arr[i] = create_thread_info_node(i);
	info_arr[size] = NULL;
	return (info_arr);
}



int	main(int argc, char **argv)
{
	pthread_t		*philosophers;//phillsopher - thread 1:1
	t_thread_info	**info_arr;
	int				size;
	int				thread_id;
	int				status;
	// if (argc != 5 && argc != 6)
	// 	return (0);
	philosophers = create_phillosophers(argv[1]);
	info_arr = create_thread_info_arr(argv[1]);
	int i;
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		// printf("%d\n", i);
		// printf("info idx : %d\n", info_arr[i]->idx);
		thread_id = pthread_create(&philosophers[i], NULL, execute_thread_function, (void *)info_arr[i]);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(philosophers[i], (void **)&status);
		i++;
	}
	// system("leaks a.out");
}
