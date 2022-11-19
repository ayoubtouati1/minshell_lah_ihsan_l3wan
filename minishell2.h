#if !defined(MINISHELL2_H)
#define MINISHELL2_H

# include <pthread.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <curses.h>
# include <signal.h>
# include "dirent.h"
# include <limits.h>
# include "libft/libft.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFF_SIZE 4000

//////////// parsing struct /////////////

enum e_type
{
	CMD,
	ARG,
	INPUT_FILE,
	OUTPUT_FILE,
	HEREDOC,
	HEREDOC_OP,
	APPEND,
	INPUT_OP,
	OUTPUT_OP,
	APPEND_OP,
	PIPE,
	D_QUOTES,
	S_QUOTES,
	NO_QUOTES
};

typedef struct s_file
{
	int		fd;
	int		type;
} t_file;

typedef struct s_minishell
{
	char				*data;
	int					type;
	t_file				file;
	int					quotes;
	struct s_minishell	*next;
}	t_minishell;



typedef struct s_token
{
	char			*parse_line;
	char			**pip_split;
	int				quotes;
	char			a;
	char			b;
	int				i;
	int				j;
	int				n;
	int				s_quot;
	int				d_quot;
	int				if_true;
}	t_token;


///////// execution struct ////////////////////////

typedef struct		s_list
{
	void			*content;
	long			content_size;
	struct s_list	*next;
}					t_list;

typedef struct s_sig
{
	int	sigint;
	int sigquit;
	pid_t pid;
	int exit_status;
}t_sig;

typedef struct s_list_env
{
    char *value;
    struct s_list_env *next;

}t_list_env;

typedef struct s_shell
{
	t_list_env		*export_env;
    t_list_env		*env;
	t_minishell		**start;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				here_in;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				no_exec;
	int				n;
}t_shell;
//////////// or Execution //////////////
void		replace_env(t_list_env **list, char *name, char *value);
char		*find_env(t_shell **list, char *name);
void		add_env(t_list_env **lst, t_list_env *new);
t_list_env 	*new_env_malloc(char *name, char *value);
void		ft_list_sort_env(t_list_env **lst);
void    	del_at_env(t_list_env **lst, char *str);
int			ft_cd(char **args, t_list_env *env);
int    		ft_echo(char **argv);
int			run_env(t_list_env *env);
void    	run_exit(char **av, t_shell *t_mini);
int  		run_export(char **args, t_list_env *env, t_list_env *export_env);
int			ft_pwd(void);
int			run_unset(char **a, t_shell *mini);
void 		free_tab(char **tabs);
void		sig_handler(int sig);
void		sig_handler_quit(int code);
void		print_prompt(int clear);
int			run_builtins(char **argv, t_shell *mini);
void 		free_tab(char **tabs);
void 		init_sig(void);
t_minishell *next_sep(t_minishell *token, int skip);
t_minishell *prev_sep(t_minishell *token, int skip);
t_minishell *next(t_minishell *token, int skip);
void		print_sorted_env(t_list_env *env);
int			is_valid_env(char *env);
void		exec_cmd(t_shell *mini, t_minishell *token);
int			run_bin(char **av, t_list_env *env, t_shell *mini);
char		*env_to_str(t_list_env *lst);
void		redir(t_shell *mini, t_minishell *token, int type);
void		input(t_shell *mini, t_minishell *token);
void 		minipipe(t_shell *mini, t_minishell *token);
void		input(t_shell *mini, t_minishell *token);
int			is_in_env(t_list_env *env, char *args);
int			env_add(const char *value, t_list_env *env);
void 		execution(t_shell *ptr);
void		reset_std(t_shell *mini);
void		close_fds(t_shell *mini);
void		reset_fds(t_shell *mini);
void		ft_close(int fd);
char		*ms_getprompt();
void		heredoc_func(t_shell *head, t_minishell *token, t_shell *ptr);
void  		redir_and_exec(t_shell *mini, t_minishell *token);
void		signals(void);

////////////for the parsing//////////////

char		*handling_quotes(char	*str, char a, char b);
char		*ft_strcpy(char *dst, const char *str);
//int			ft_strchr(const char *s, int c);
int			ft_strnstr(const char *haystack, const char *needle);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);
int			ft_memcmp(const void *s1, const void *s2);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_isdigit(int c);
char		*copy_no_dollar(char *str,char *tmp, t_token *ptr);
int			quot_cont(char *str, int n, char sep);
int			check_dollar(char *str, int i);
int			cont_dollar(char *str, int i);
char		*copy_no_expand(char *str, char *tmp, t_token *ptr, t_shell *mini);
char		*digit_expand(char *str, char *tmp, t_token *ptr, char **env);
char		*dollar_expand(char *str, char *tmp, t_token *ptr, char ** env);
char		*expand(char *str, int i, char **env);
char		**alloc_des(char **env);
void		ft_free(char **dst);
char		*count_space_and_alloc(char *str, char *dest, int i);
int			add_after_opirations(char **str, char	**dest, int *i, int *j);
int			add_inside_quot(char **str, char **dest, int *i, int *j);
void		add_befor_opirations(char **str, char **dest, int *i, int *j);
char		*handling_spaces(char *str);
t_minishell	*fill_stack(t_minishell *stack_a, char **str, char **env, t_shell *mini);
char		*remove_quotes(char *str);
int			check_quot(char *str);
int			cont_quot(char *str);
char		*comper_to_env(char *dest, char **env);
char		*check_expand(char *str, char **env, int type, t_shell *mini);
char		**replace_in_quotes(char **str, char a, char b);
void		define_cmd(t_minishell **tokens);
t_minishell	**sep_split(char **str, char sep, char **env, t_shell *mini);
char		*get_next_line(int fd);
char		*ft_strrjoin(char const *s1, char const *s2);

extern t_sig g_sig;
#endif  
