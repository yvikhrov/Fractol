/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:50 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 17:38:28 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_INPUT_H
# define HANDLE_INPUT_H

# include "fractol.h"

int		key_press(int keycode, void *param);
int		key_release(int keycode, void *ctx);
int		mouse_hook(int keycode, int x, int y, void *param);
int		mouse_position_hook(int x, int y, void *param);
void	handle_input(t_app *app, double delta_time);

#endif
