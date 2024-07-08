/**
 ******************************************************************************
 * @file           : slip39_lib.h
 * @brief          : Header for slip39_lib.c file.
 *                   This file contains the common defines of the seed slip39 library.
 ******************************************************************************
 * @attention
 *
 * Portion Copyright (C) 2024 Semilla3 OÜ.  All Rights Reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef INC_slip39_LIB_H_
#define INC_slip39_LIB_H_

/********************************************************************** Include's **********************************************************************/
#include "stm32u5xx_hal.h"
#include "main.h"

/********************************************************************* Function's **********************************************************************/
bool getSlip39Word(char *buffer);

/********************************************************************* Variable's **********************************************************************/
extern const char slip39_words_a[67][10];
extern const char slip39_words_b[47][10];
extern const char slip39_words_c[71][10];
extern const char slip39_words_d[68][10];
extern const char slip39_words_e[70][10];
extern const char slip39_words_f[58][10];
extern const char slip39_words_g[39][10];
extern const char slip39_words_h[32][10];
extern const char slip39_words_i[31][10];
extern const char slip39_words_j[12][10];
extern const char slip39_words_k[7][10];
extern const char slip39_words_l[47][10];
extern const char slip39_words_m[57][10];
extern const char slip39_words_n[11][10];
extern const char slip39_words_o[19][10];
extern const char slip39_words_p[80][10];
extern const char slip39_words_q[4][10];
extern const char slip39_words_r[55][10];
extern const char slip39_words_s[115][10];
extern const char slip39_words_t[56][10];
extern const char slip39_words_u[19][10];
extern const char slip39_words_v[27][10];
extern const char slip39_words_w[27][10];
extern const char slip39_words_y[4][10];
extern const char slip39_words_z[1][10];

#endif
