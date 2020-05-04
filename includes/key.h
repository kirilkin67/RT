/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 23:49:30 by wrhett            #+#    #+#             */
/*   Updated: 2020/05/04 15:09:37 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H
# ifdef __linux__
#  define KEY_W			119
#  define KEY_A			97
#  define KEY_S			115
#  define KEY_D			100
#  define KEY_Q			113
#  define KEY_E			101
#  define KEY_ESC		65307
#  define KEY_SPACE		32
#  define KEY_2			50
#  define KEY_3			51
#  define NUM_KEY_1		65436
#  define NUM_KEY_2		65433
#  define NUM_KEY_3		65435
#  define NUM_KEY_4		65430
#  define NUM_KEY_5		65437
#  define NUM_KEY_6		65432
#  define NUM_KEY_7		65429
#  define NUM_KEY_8		65431
#  define NUM_KEY_9		65434
#  define NUM_KEY_0		65438
#  define NUM_KEY_PLUS	65451
#  define NUM_KEY_MINUS	65453
#  define NUM_LEFT		65361
#  define NUM_RIGHT		65363
#  define NUM_DOWN		65364
#  define NUM_UP		65362
# else
#  define KEY_Q			12
#  define KEY_E			14
#  define KEY_W			13
#  define KEY_A			0
#  define KEY_S			1
#  define KEY_D			2
#  define KEY_Z			6
#  define KEY_X			7
#  define KEY_SPACE		49
#  define KEY_ESC		53
#  define KEY_2			19
#  define KEY_3			20
#  define NUM_KEY_1		83
#  define NUM_KEY_2		84
#  define NUM_KEY_3		85
#  define NUM_KEY_4		86
#  define NUM_KEY_5		87
#  define NUM_KEY_6		88
#  define NUM_KEY_7		89
#  define NUM_KEY_8		91
#  define NUM_KEY_9		92
#  define NUM_KEY_PLUS	69
#  define NUM_KEY_MINUS	78
#  define NUM_LEFT		123
#  define NUM_RIGHT		124
#  define NUM_DOWN		125
#  define NUM_UP		126
# endif
#endif
