#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*
** -------------------------- External Headers ---------------------------------
*/

# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

/*
** ------------------------- Structure Definitions -----------------------------
*/

typedef struct s_philo
{
	pthread_mutex_t *forks;
	pthread_t		*philo;
	pthread_mutex_t	id_mutex;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	die_mutex;
	struct timeval	tv;
	unsigned int	*timestamp;
	//unsigned int	msg_usec;
	unsigned int	start_usec;
	int				n_philo;
	//int				n_forks;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				n_times;
	int				id_counter;
	int				fork_id;
	int				died;
}				t_philo;

typedef struct s_indiv
{
	int	id;
	int	r_fork;
	int	l_fork;
	int fork_id;
	unsigned int msg_usec;
}				t_indiv;


/*
** ------------------------- Enum Definitions ----------------------------------
*/

// typedef enum e_error
// {

// }				t_elem_error;

/*
** -----------------------------------------------------------------------------
** ------------------------------- Sources -------------------------------------
** -----------------------------------------------------------------------------
*/

/*
** ---------------------------------- main.c -----------------------------------
*/
int		main(int ac, char **av);
void    ph_init(int ac, char **av, t_philo *ph);
void ph_get_initial_timestamp(t_philo *ph);
void* function(void* arg);
void ph_odd_waiting(int id, int eat_time);

/*
** ---------------------------------- libft.c -----------------------------------
*/

int	ft_isdigit(int c);
int	ft_atoi(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putstr_fd(char *s, int fd);
int	ft_strlen(const char *s);

/*
** ---------------------------------- fork.c -----------------------------------
*/

//void    ph_take_fork(t_philo *ph, t_indiv *p, pthread_mutex_t *mutex, int fork_id );
int    ph_take_fork(t_philo *ph, t_indiv *p);

/*
** ---------------------------------- threads.c -----------------------------------
*/

int	ph_create_philosophers(t_philo *ph);
int ph_join_philosophers(t_philo *ph);
int	ph_get_philo_id(int *id_counter, pthread_mutex_t *mutex);

/*
** ---------------------------------- parsing.c --------------------------------
*/


/*
** ---------------------------------- messages.c --------------------------------
*/

//int	ph_write_message(int p_id, unsigned int start_usec, char *str, pthread_mutex_t *mutex);
//int	ph_write_message(int p_id, unsigned int msg_usec, int start_usec, char *str, pthread_mutex_t *mutex);
int	ph_write_message(t_philo *ph, t_indiv *p, char *str);
void	ph_dead_message(t_philo *ph, int id);
//void	ph_dead_message(t_philo *ph, unsinged int msg_usec, int id);


/*
** ---------------------------------- actions.c --------------------------------
*/

//void	ph_usleep(unsigned int time);
void	ph_usleep(unsigned int start_usec, unsigned int time);
int	ph_sleeping(t_philo *ph, t_indiv *p);
int	ph_thinking(t_philo *ph, t_indiv *p);


/*
** ---------------------------------- death.c --------------------------------
*/

void ph_check_death(t_philo *ph);
int		ph_check_if_died(t_philo *ph, pthread_mutex_t *die_mutex);



/*
** ---------------------------------- utils.c --------------------------------
*/

unsigned int ph_get_time_today(struct timeval *tv);


#endif


