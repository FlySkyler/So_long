/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:13:04 by antbonin          #+#    #+#             */
/*   Updated: 2025/02/11 14:35:02 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/ressource/libft.h"
#include "so_long.h"
#include <stdlib.h>

int	cleanup_textures(t_game *game)
{
	if (game->wall_img)
		mlx_destroy_image(game->mlx_ptr, game->wall_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx_ptr, game->floor_img);
	if (game->collectible_img)
		mlx_destroy_image(game->mlx_ptr, game->collectible_img);
	if (game->character_img)
		mlx_destroy_image(game->mlx_ptr, game->character_img);
	if (game->door_open)
		mlx_destroy_image(game->mlx_ptr, game->door_open);
	if (game->exit_img)
		mlx_destroy_image(game->mlx_ptr, game->exit_img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	free_tab(game->map);
	return (1);
}

int	init_textures(t_game *game)
{
	game->img_width = 80;
	game->img_height = 80;
	game->wall_img = mlx_xpm_file_to_image(game->mlx_ptr, "./assets/wall.xpm",
			&game->img_width, &game->img_height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx_ptr, "./assets/floor.xpm",
			&game->img_width, &game->img_height);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./assets/collectible.xpm", &game->img_width, &game->img_height);
	game->character_img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./assets/character.xpm", &game->img_width, &game->img_height);
	game->door_open = mlx_xpm_file_to_image(game->mlx_ptr,
			"./assets/open_tunnel.xpm", &game->img_width, &game->img_height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx_ptr, "./assets/exit.xpm",
			&game->img_width, &game->img_height);
	if (!game->wall_img || !game->floor_img || !game->collectible_img
		|| !game->character_img || !game->door_open || !game->exit_img)
	{
		cleanup_textures(game);
		exit(1);
		return (0);
	}
	return (1);
}

int	init_window_and_textures(t_game *game)
{
	game->mlx_ptr = mlx_init();
	game->wall_img = NULL;
	game->floor_img = NULL;
	game->collectible_img = NULL;
	game->character_img = NULL;
	game->door_open = NULL;
	game->door_open = NULL;
	game->exit_img = NULL;
	if (!game->mlx_ptr)
		return (1);
	if (!init_textures(game))
	{
		ft_putendl_fd("Error\n", 2);
		cleanup_textures(game);
		return (1);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map_width * 80,
			game->map_height * 80, "Map Window");
	if (!game->win_ptr)
	{
		cleanup_textures(game);
		return (1);
	}
	return (0);
}
