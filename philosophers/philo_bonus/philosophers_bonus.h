/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:57:30 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/05 19:23:43 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>

# define AVAILABLE 0
# define USED 1

typedef struct s_fork{
	pthread_mutex_t	mutex;
}	t_fork;

// typedef struct s_philo{
// 	int					idx;
// 	int					eat_count;
// 	int					last_eat;
// 	long long			start_eat;
// 	int					stop;
// 	int					done;
// 	pthread_mutex_t		fork_mutex;
// 	pthread_mutex_t		done_mutex;
// 	pthread_t			thread_id;
// 	struct s_setting	*common_info;
// }	t_philo;

typedef struct s_philo{
	//setting
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	int				dead;
	long long		time_to_start;
	//philo
	int				idx;
	int				eat_count;
	int				last_eat;
	long long		start_eat;
	int				stop;
	int				done;
	//semaphore
	sem_t			*forks;
	sem_t			*print;
	sem_t			*die;
	//thread
	pthread_t		thread_id;

}	t_philo;

typedef struct s_setting{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	int				dead;
	long long		time_to_start;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	dead_mutex;
}	t_setting;

typedef struct s_thread_info{
	int	idx;
}	t_thread_info;

typedef struct s_common_resource{
	int				size;
	int				*forks;
	int				current_idx;
	t_thread_info	**info_arr;
}	t_common_resource;

int			show_error(char *message);
int			check_valid_input(int argc, char **argv);
int			initiate_setting(t_philo *setting, char **argv);
long long	timestamp(void);
void		*execute_philo(void *data);
int			initiate_philos(t_setting *setting);
int			is_dead(t_setting *info);
void		set_dead(t_setting *info);
void		monitor_dead(t_setting *info, t_philo *philo);
int			get_turn(t_setting *info);
void		print(t_philo *philo, char *message);
void		set_dead(t_setting *info);
void		set_done(t_philo *philo);
void		ft_usleep(int mili_second);
void		execute_starvation(t_setting *info, t_philo *philo);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
#endif