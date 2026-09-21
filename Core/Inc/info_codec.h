/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
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
#ifndef ENC_CODEC_H
#define ENC_CODEC_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*** Configuration ***/
#define ENC_TOKEN_LEN 11   // "E123456789K"

/*** Err8r codes ***/
typedef enum
{
	ENC_OK = 0,
	ENC_ERR_NULL = -1,
	ENC_ERR_FMT = -2,
	ENC_ERR_RANGE = -3,
	ENC_ERR_CHECKSUM = -4,
	ENC_ERR_OUTCAP = -5
} enc_err_t;

/*** Data fields ***/
typedef struct
{
	uint8_t f1, f2, f3;   //Firmware version digits (0-9)
	uint8_t hw;           //Hardware version (1-9)
	uint8_t mx, my;       //Matrix M-X:Y (1-6)
	uint8_t p;            //P flag (0-1)
	uint8_t c;            //C flag (0-1)
	uint8_t b;            //BIT flag (0-1)
} enc_fields_t;

/*** API ***/
/*
 * @brief Validate field ranges
 */
enc_err_t enc_validate(const enc_fields_t *f);

/*
 * @brief Encode fields into reduced token "E.........."
 * @param f        Input fields
 * @param out      Output buffer
 * @param outCap   Output buffer capacity (>= ENC_TOKEN_LEN + 1)
 */
enc_err_t enc_encode_fields_to_reduced(const enc_fields_t *f, char *out, size_t outCap);

/**
 * @brief Decode reduced token to fields
 */
enc_err_t enc_decode_reduced_to_fields(const char *reduced, enc_fields_t *out);

/*
 * @brief Render fields into ASCII original format "ENC,vF1.F2.F3(H),M-X:Y,P-P,C-C,BITB"
 */
enc_err_t enc_render_original( const enc_fields_t *f, char *out, size_t outCap );

/*
 * @brief Encode ASCII original → reduced token
 */
enc_err_t enc_encode_original_to_reduced(const char *original, char *outReduced, size_t outCap);

/*
 * @brief Decode reduced token → ASCII original
 */
enc_err_t enc_decode_reduced_to_original(const char *reduced, char *outOriginal, size_t outCap);

/*
 * @brief Auto detect input format and convert
 */
enc_err_t enc_convert_either_way(const char *input, char *out, size_t outCap);

#ifdef __cplusplus
}
#endif

#endif /* ENC_CODEC_H */
