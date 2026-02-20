/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:55:36 by andriamr          #+#    #+#             */
/*   Updated: 2025/04/08 13:42:11 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int		ft_isalpha(int c);//si lettre
int		ft_isdigit(int c);//si chiffre
int		ft_isalnum(int c);//si alphanumerique chiffre ou lettre
size_t	ft_strlen(const char *str);// longueu str
int		ft_isascii(int c);// est dans ascii
int		ft_isprint(int c);// si printable
int		ft_toupper(int c);// rend majuscule
int		ft_tolower(int c);// rend miniscule
void	*ft_memset(void *s, int c, size_t n);//n character de *s en c
void	ft_bzero(void *s, size_t n);//n premier caractere de s en 0 ou '\0'
void	*ft_memcpy(void *dest, const void *src, size_t n);// cpy memoire 2 cast
void	*ft_memmove(void *dest, const void *src, size_t n);// si src sur dest
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);//premier c
char	*ft_strrchr(const char *s, int c);// dernier c
int		ft_strncmp(const char *s1, const char *s2, size_t n);// cmp n s2 dans s1
void	*ft_memchr(const void *s, int c, size_t n);// chr c dans s
int		ft_memcmp(const void *s1, const void *s2, size_t n);// cmp avec cast
char	*ft_strnstr(const char *big, const char *little, size_t len);// ncmp
int		ft_atoi(const char *nptr);// char to int
void	*ft_calloc(size_t nmemb, size_t size);// size =size of
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
/*char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));*/

#endif