/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:57:30 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/06 22:02:49 by yuikim           ###   ########.fr       */
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
# include <signal.h>

typedef struct s_philo{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	long long		time_to_start;
	int				idx;
	int				eat_count;
	int				last_eat;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*die;
	sem_t			*eat;
	pthread_t		thread_id;
	struct timeval	start_to_eat;
}	t_philo;

int			initiate_setting(t_philo *setting, char **argv);
int			show_error(char *message);
int			check_valid_input(int argc, char **argv);
long long	timestamp(void);
int			execute_philo(t_philo *philo);
void		*monitor_dead(void *data);
void		print(t_philo *philo, char *message);
void		ft_usleep(int mili_second);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
void		repeat(t_philo *philo);
int			have_forks(t_philo *philo);
int			create_philos(t_philo *philo);
void		*monitor_dead(void *data);
void		eat(t_philo *philo);
void		init_semaphores(t_philo *philo);
#endif