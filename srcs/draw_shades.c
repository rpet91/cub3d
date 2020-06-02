/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_shades.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 16:18:30 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/12 17:45:13 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**		Adds shades in map. The further the distance, the darker it becomes.
*/

int		add_shades(int rgb, double distance)
{
	double	shade;

	shade = (8.0 / distance) / 3.0;
	if (shade > 1)
		shade = 1;
	if (shade < 0.3)
		shade = 0.3;
	rgb = (((int)((0xFF & rgb >> 16) * shade) << 16) +
			((int)((0xFF & rgb >> 8) * shade) << 8) +
			((int)(0xFF & rgb) * shade));
	return (rgb);
}
