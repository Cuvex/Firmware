/**
 ******************************************************************************
 * @file           : xmr_lib.h
 * @brief          : Header for xmr_lib.c file.
 *                   This file contains the common defines of the seed xmr library.
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

#ifndef INC_XMR_LIB_H_
#define INC_XMR_LIB_H_

/********************************************************************** Include's **********************************************************************/
#include "stm32u5xx_hal.h"
#include "main.h"

/********************************************************************* Function's **********************************************************************/
bool getXmrWord(char *buffer);

/********************************************************************* Variable's **********************************************************************/
extern const char xmr_words_a[140][10];
extern const char xmr_words_b[80][10];
extern const char xmr_words_c[63][10];
extern const char xmr_words_d[88][10];
extern const char xmr_words_e[75][10];
extern const char xmr_words_f[71][10];
extern const char xmr_words_g[70][10];
extern const char xmr_words_h[62][10];
extern const char xmr_words_i[51][10];
extern const char xmr_words_j[44][10];
extern const char xmr_words_k[21][10];
extern const char xmr_words_l[73][10];
extern const char xmr_words_m[66][10];
extern const char xmr_words_n[58][10];
extern const char xmr_words_o[69][10];
extern const char xmr_words_p[92][10];
extern const char xmr_words_q[3][10];
extern const char xmr_words_r[80][10];
extern const char xmr_words_s[141][10];
extern const char xmr_words_t[96][10];
extern const char xmr_words_u[55][10];
extern const char xmr_words_v[48][10];
extern const char xmr_words_w[54][10];
extern const char xmr_words_y[14][10];
extern const char xmr_words_z[12][10];

#endif
