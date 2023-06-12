/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:33 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:33 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	valid_format(char *s)
{
	int	i;
	int	nb;
	int	coma;

	i = -1;
	nb = 0;
	coma = 0;
	while (s[++i])
	{
		if (s[i] == ',' && !nb)
			return (0);
		(!nb && ft_isdigit(s[i]) && nb++);
		(s[i] == ',' && ++coma && nb--);
	}
	return (coma == 2);
}

int	is_invalid_name(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (1);
	while (s[++i])
	{
		if (s[i] == '.')
			break ;
	}
	return (ft_strcmp(s + i, ".cub"));
}

int	empty_line(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] != '\t' && s[i] != '\n' && s[i] != '\f' && \
		s[i] != '\b' && s[i] != ' ' && s[i] != '\r')
			return (0);
	return (1);
}

int	valid_map_line(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != '1' && s[i] != '0' && s[i] != 'N' && s[i] != 'S' && \
		s[i] != 'E' && s[i] != 'W' && s[i] != ' ')
			return (0);
	}
	return (1);
}
