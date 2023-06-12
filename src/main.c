/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:22 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:22 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_values_to_null(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->file = NULL;
	game->asset = NULL;
	game->minimap.ptr = NULL;
	game->player = NULL;
	game->gun_effect[0].ptr = NULL;
	game->gun.ptr = NULL;
	game->gun_sprite.ptr = NULL;
	game->frame.ptr = NULL;
}

char	*get_path(char **file, t_path path)
{
	int		i;
	char	*type;
	char	*res;

	type = "NO ";
	if (path == EA)
		type = "EA ";
	if (path == SO)
		type = "SO ";
	if (path == WE)
		type = "WE ";
	i = -1;
	while (file[i] && !str_in_str(file[i], type, ft_strlen(file[i])))
		i++;
	if (!file[i])
		return (NULL);
	type = ft_strtrim(file[i], " ");
	if (!type)
		return (NULL);
	res = ft_strtrim(type + 3, " ");
	safe_free(type);
	if (res && does_contain(res, ' '))
		safe_free(res);
	return (res);
}

int	destroy(t_game *game)
{
	terminate(game, NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		terminate(NULL, "invalid number of arguments\n");
	(void)argv;
	set_values_to_null(&game);
	init_game(&game, argv[1]);
	init_mlx(&game);
	init_asset(&game);
	game_loop(&game);
	return (0);
}
