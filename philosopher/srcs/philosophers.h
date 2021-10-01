/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 13:48:56 by lduhamel          #+#    #+#             */
/*   Updated: 2021/10/01 14:42:50 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*
** -------------------------- External Headers ---------------------------------
*/

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

/*
** ------------------------- Structure Definitions -----------------------------
*/

typedef struct s_philo
{
	pthread_mutex_t	*forks;
	pthread_t		*philo;
	pthread_mutex_t	id_mutex;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	eat_mutex;
	struct timeval	tv;
	unsigned int	**last_meals;
	unsigned int	last_meal;
	int				n_philo;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				n_times;
	int				id_counter;
	int				died;
	int				ate_n_times;
}				t_philo;

typedef struct s_indiv
{
	int				id;
	int				r_fork;
	int				l_fork;
	unsigned int	msg_usec;
}				t_indiv;

/*
** -----------------------------------------------------------------------------
** ------------------------------- Sources -------------------------------------
** -----------------------------------------------------------------------------
*/

/*
** ---------------------------------- main.c -----------------------------------
*/

int				main(int ac, char **av);
int				ph_one_philo(t_philo *ph, t_indiv *p);
int				ph_multiple_philo(t_philo *ph, t_indiv *p);
void			*function(void *arg);
void			ph_odd_waiting(int id, int eat_time);

/*
** ---------------------------------- init.c -----------------------------------
*/

int				ph_malloc(t_philo *ph);
void			ph_get_argv(int ac, char **av, t_philo *ph);
void			ph_init_mutex(t_philo *ph);
void			ph_get_initial_last_meals(t_philo *ph);

/*
** ---------------------------------- libft.c -----------------------------------
*/

int				ft_isdigit(int c);
int				ft_atoi(const char *str);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int nb, int fd);
void			ft_putstr_fd(char *s, int fd);

/*
** ---------------------------------- threads.c ---------------------------------
*/

int				ph_create_philosophers(t_philo *ph);
int				ph_join_philosophers(t_philo *ph);
int				ph_get_philo_id(int *id_counter, pthread_mutex_t *mutex);

/*
** ---------------------------------- parsing.c --------------------------------
*/

int				ph_parsing(int ac, char **av, t_philo *ph);
int				ph_check_if_digits(int ac, char **av);

/*
** ---------------------------------- messages.c --------------------------------
*/

int				ph_write_message(t_philo *ph, t_indiv *p, char *str);
void			ph_dead_message(t_philo *ph, int id);

/*
** ---------------------------------- actions.c --------------------------------
*/

int				ph_take_fork(t_philo *ph, t_indiv *p);
int				ph_sleeping(t_philo *ph, t_indiv *p);
int				ph_thinking(t_philo *ph, t_indiv *p);

/*
** ---------------------------------- death.c --------------------------------
*/

void			ph_check_death(t_philo *ph);
int				ph_check_if_died(t_philo *ph, pthread_mutex_t *die_mutex);
int				ph_check_if_ate_n_times(t_philo *ph);

/*
** ---------------------------------- utils.c --------------------------------
*/

int				ft_strlen(const char *s);
unsigned int	ph_get_time_today(struct timeval *tv);
void			ph_usleep(unsigned int start_usec, unsigned int time);
int				ph_unlock(t_philo *ph, int fork_r, int fork_l);

/*
** ---------------------------------- clean.c --------------------------------
*/

void			ph_free_dtab(unsigned int **tab, int n);
int				ph_free_mallocs(pthread_t *philo, pthread_mutex_t *forks,
					unsigned int **last_meals, int n);
void			ph_destroy_mutex(t_philo *ph);
int				ph_handle_error(t_philo *ph, char *str);
int				ph_write_error(char *str);

#endif
