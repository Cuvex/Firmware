/**
 ******************************************************************************
 * @file           : bip39_lib.h
 * @brief          : Header for bip39_lib.c file.
 *                   This file contains the common defines of the seed bip39 library.
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

#ifndef INC_BIP39_LIB_H_
#define INC_BIP39_LIB_H_

/********************************************************************** Include's **********************************************************************/
#include "stm32u5xx_hal.h"
#include "main.h"

/********************************************************************* Function's **********************************************************************/
bool getBip39Word(char *buffer);

/********************************************************************* Variable's **********************************************************************/
extern const char bip39_words_a[136][10];
extern const char bip39_words_b[117][10];
extern const char bip39_words_c[186][10];
extern const char bip39_words_d[112][10];
extern const char bip39_words_e[100][10];
extern const char bip39_words_f[106][10];
extern const char bip39_words_g[76][10];
extern const char bip39_words_h[64][10];
extern const char bip39_words_i[55][10];
extern const char bip39_words_j[20][10];
extern const char bip39_words_k[20][10];
extern const char bip39_words_l[76][10];
extern const char bip39_words_m[105][10];
extern const char bip39_words_n[41][10];
extern const char bip39_words_o[55][10];
extern const char bip39_words_p[132][10];
extern const char bip39_words_q[8][10];
extern const char bip39_words_r[108][10];
extern const char bip39_words_s[250][10];
extern const char bip39_words_t[121][10];
extern const char bip39_words_u[35][10];
extern const char bip39_words_v[46][10];
extern const char bip39_words_w[69][10];
extern const char bip39_words_y[6][10];
extern const char bip39_words_z[4][10];

#endif
