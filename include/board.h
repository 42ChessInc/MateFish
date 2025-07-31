/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:29:39 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/31 12:43:38 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
typedef uint64_t	Bitboard;

typedef struct
{
	Bitboard	pieces[2][6]; //Squares occupied by each piece (6) for each color (2)

	Bitboard	ocuppied; //All ocuppied squares (both black and white)
	Bitboard	ocuppiedColor[2]; //Ocuppied squares by color
}	t_board;

#endif
