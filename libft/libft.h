/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:12:40 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 19:05:37 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <wchar.h>
# include <stddef.h>
# include <limits.h>
# include <math.h>

# define BUFF_SIZE 1024

# define MAX(a, b) ((a) > (b)) ? (a) : (b)
# define MIN(a, b) ((a) > (b)) ? (b) : (a)

typedef struct		s_file
{
	int				fd;
	char			*buf;
	size_t			buf_size;
	size_t			i;
}					t_file;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_dlist
{
	void			*content;
	size_t			content_size;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

long long			ft_atoi(const char *str);
long long			ft_atoi_base(const char *str, int base);
long double			ft_atod(const char *str);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_isspace(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size, char c);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

t_dlist				*ft_dlstnew(void const *content, size_t content_size);
void				ft_dlstdelone(t_dlist **alst, void (*del)(void*, size_t));
void				ft_dlstdel(t_dlist **alst, void (*del)(void *, size_t));
unsigned int		ft_dlstlen(t_dlist **head);
void				ft_dlstadd(t_dlist **alst, t_dlist *new);
void				ft_dlstpush(t_dlist **alst, t_dlist *new);

int					ft_sqrt_high(int nb);
void				ft_swap_int(int *a, int *b);
void				ft_swap_uint(unsigned int *a, unsigned int *b);
void				ft_puttab(char const **tab);
t_list				*ft_nodenew(void *content, size_t content_size);
unsigned int		ft_lstlen(t_list **head);
void				ft_lstpush(t_list **alst, t_list *new);
void				ft_putnode_int(t_list *node);
void				ft_putnode_str(t_list *node);
void				ft_putlist_int(t_list *head);
void				ft_putlist_str(t_list *head);
void				*ft_smemalloc(size_t size, char *ft_name);
int					ft_arrlen(char **arr);
void				ft_free_tab(char **tab);
int					get_next_line(const int fd, char **line);
void				ft_error(char *msg);
void				ft_warn(char *msg);
int					ft_indexof_chr(char *str, int c);
char				*ft_strcut(char *str, size_t from, size_t to);
void				ft_strrplc(char *str, char find, char put);
int					ft_limit(int min, int max, int num);
double				ft_limitf(double min, double max, double num);

void				ft_write_wctoa(wchar_t wc, char *str);
char				*ft_ustos(wchar_t *us);
void				ft_putwchar(wint_t wc);
void				ft_putwchar_fd(wint_t wc, int fd);
void				ft_putwstr(const wchar_t *wstr);
void				ft_putwstr_fd(const wchar_t *wstr, int fd);
void				ft_putwendl(const wchar_t *wstr);
void				ft_putwendl_fd(const wchar_t *wstr, int fd);

char				*ft_itoa(long long num);
char				*ft_itoa_base(long long num, int base);
char				*ft_uitoa(unsigned long long num);
char				*ft_uitoa_base(unsigned long long num, int base);

size_t				ft_get_filesize(char *file_name);
char				*ft_readfile(char *file_name);

double				ft_torad(double degrees);
void				ft_solve_sqr
						(double a, double b, double c, double (*res)[3]);

#endif
