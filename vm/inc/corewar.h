/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:07:31 by adhondt           #+#    #+#             */
/*   Updated: 2018/08/01 14:23:11 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "op.h"

# define BUFF_SIZE 4
# define MAX_PROC 200000
# define MEM_MOD(x) ((x) % MEM_SIZE)

typedef struct		s_process
{
	struct s_process	*next;
	int					r[REG_NUMBER];
	int					id;
	int					id_player;
	int					carry;
	int					exec_cycle;
	int					op_code;
	int					will_die;
	unsigned int		last_live;
	unsigned int		id_process;
	unsigned int		pc;
}					t_process;

typedef struct		s_lst_process
{
	t_process	*process;
	int			len;
}					t_lst_process;

typedef struct		s_champ
{
	struct s_champ	*next;
	int				player_id;
	int				fd;
	int				process_count;
	int				header_champsize;
	char			*name;
	char			*comment;
}					t_champ;

typedef struct		s_board
{
	t_lst_process	*lst_process;
	t_champ			*first_champ;
	unsigned int	champions_count;
	unsigned int	cycle;
	unsigned int	id_process;
	int				last_live;
	unsigned int	last_check_purge;
	unsigned int	check_nbr;
	unsigned int	total_cycle_live;
	unsigned char	*ram;
	unsigned int	dump;
	int				cycle_to_die;
	int				p;
	int				s;
	int				m;
	char			*opt_list;
	char			*verbose;
}					t_board;

typedef struct		s_op
{
	char			*name;
	int				argc;
	int				argv[3];
	int				op_code;
	int				cycles;
	char			*lname;
	int				octal;
	int				carry;
}					t_op;

static const t_op	g_op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}
};

t_lst_process		*init_list_process(void);
t_process			*add_process(t_board *bd, int r1, unsigned int pc);
void				update_process_count(t_board *bd, int id, int op);
void				set_ramvalue(t_board *bd,
						unsigned int pc, unsigned int value);
void				loop_process(t_board *board);
int					check_instruction(t_board *bd, t_process *proc);
int					init_process(t_board *board);
int					get_params(t_board *bd, t_process *proc,
						unsigned int *pc, int data[2]);
void				purge_process(t_board *bd);

void				play(t_board *board);
void				add(t_board *board, t_process *process);
void				aff(t_board *board, t_process *process);
void				and(t_board *board, t_process *process);
void				frk(t_board *board, t_process *process);
void				ld(t_board *board, t_process *process);
void				ldi(t_board *board, t_process *process);
void				lfork(t_board *board, t_process *process);
void				live(t_board *board, t_process *process);
void				lld(t_board *board, t_process *process);
void				lldi(t_board *board, t_process *process);
void				or(t_board *board, t_process *process);
void				st(t_board *board, t_process *process);
void				sti(t_board *board, t_process *process);
void				sub(t_board *board, t_process *process);
void				xor(t_board *board, t_process *process);
void				zjmp(t_board *board, t_process *process);

unsigned int		ocp_first(unsigned char c);
unsigned int		ocp_scd(unsigned char c);
unsigned int		ocp_third(unsigned char c);
short				get_dir2(t_board *bd, unsigned int pos);
int					get_dir4(t_board *bd, unsigned int pos);
int					get_indir(t_board *bd, unsigned int pos);
int					get_long_indir(t_board *bd, unsigned int pos);
int					get_reg(t_process *proc, unsigned int index);

int					init_board_data(t_board **bd, char **argv);
t_board				*collect_inputs(char **argv, int argc, t_board *bd);
void				add_champ_to_lst(t_board *bd, t_champ *champ);
int					open_champ(t_board *bd, char **argv, int i, int op);
int					get_first_number(t_board *bd, int i);
void				init_f(void (*f[17])(t_board *b, int player));
int					ft_error(int id, int errn);
int					insert_instructions(t_board *board);
void				print_memory(t_board *bd, int id);
void				print_champ_lst(t_board *bd);
void				print_verbose_data(t_board *bd);
int					ft_usage(void);
void				ft_putnbrstrnbr(int nb, char *str, int n);
void				ft_putstrnbrstr(char *s, int nb, char *str);
void				ft_put3str(char const *s, char *s2, char *s3);
void				ft_bzero(void *s, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_puttable(char *tab);
void				*ft_memset(void *s, int c, size_t n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				*ft_memalloc(size_t size);
void				ft_putnbr(int n);
int					ft_atoi_base(const char *str, int base);
int					ft_isnumber(char *str);
int					ft_isdigit(int c);
int					pos_str_tab(char *haystack, char **needle);
int					ft_atoi(const char *str);
int					pos_in_str(char c, char *str);
int					ft_strcmp(const char *tab, const char *tab2);
int					ft_strlen(const char *src);
unsigned char		*ft_memalloc_c(size_t size, char c);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strcpy(char *dest, const char *str);
char				*ft_strdup(const char *s);
char				*ft_strstr(const char *haystack, const char *needle);
char				*get_name_champ(t_board *bd, int id);
void				memclear(t_board *bd);
char				*ft_strjoin(char *s1, char *s2);
void				sount_start_game(void);
char				*escape_champ(char *s);

#endif
