#include "philosophers.h"

void	*execute_thread_function(void *data){
	t_common_resource	*common_resource;

	common_resource = (t_common_resource *)data;
	printf("idx %d\n", common_resource->current_idx);
	return ((void *)common_resource);
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

t_common_resource	*create_common_resource(char *philo_num)
{
	t_common_resource	*common_resource;
	int					*forks;
	int					size;
	int					i;

	common_resource = malloc(sizeof(t_common_resource));
	size = ft_atoi(philo_num);
	forks = malloc(sizeof(char) * (size + 1));
	i = -1;
	while (++i < size)
		forks[i] = AVAILABLE;
	forks[size] = 0;
	common_resource->forks = forks;
	common_resource->info_arr = create_thread_info_arr(philo_num);
	return (common_resource);
}

int	main(int argc, char **argv)
{
	pthread_t			*philosophers;//phillsopher - thread 1:1
	t_setting			setting;
	// t_thread_info		**info_arr;
	t_common_resource	*common_resource;
	int				size;
	int				thread_id;
	int				status;
	long long		count;

	count = 0;
	if (check_valid_input(argc ,argv) == 1)
		return (0);
	if (initiate_setting(&setting, argv) == 1)
		return (0);

	philosophers = create_phillosophers(argv[1]);
	// info_arr = create_thread_info_arr(argv[1]);

	common_resource = create_common_resource(argv[1]);
	pthread_mutex_t	idx_mutex;
	int	i;
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		// printf("%d\n", i);
		// printf("info idx : %d\n", info_arr[i]->idx);
		// pthread_mutex_lock(&idx_mutex);
		// common_resource->current_idx = i;
		// pthread_mutex_unlock(&idx_mutex);
		common_resource->current_idx = i;
		thread_id = pthread_create(&philosophers[i], NULL, execute_thread_function, (void *)common_resource);
		pthread_join(philosophers[i], (void **)&status);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(philosophers[i], (void **)&status);
		i++;
	}
	system("leaks a.out");
}
