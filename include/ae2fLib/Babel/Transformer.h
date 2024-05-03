#pragma once

#ifndef AE2F_IGNORE_MISSINGS
#include "ae2fLib/Container/Dynamic.hpp"
#endif // !AE2F_IGNORE_MISSINGS

#include <stdbool.h>

#ifndef AE2F_BABEL_TRANSFORMER
#define AE2F_BABEL_TRANSFORMER

/// <param name="dest">: where the data copied to</param>
/// <param name="src">: where the data source is contained</param>
/// <param name="index">: the index for the output element</param>
/// <param name="isvalid">: whether the pointer of source[src] is valid</param>
typedef void(*ae2f_Babel_Transformer_fun)(void* dest, void* src, uint32_t index, bool isvalid);

typedef struct ae2f_Babel_Transformer {
	ae2f_Babel_Transformer_fun fun;

	uint32_t
		elWidth,
		elCount;

	ptr_ae2f_Dynamic in;	// linear input buffer

}* ptr_ae2f_Babel_Transformer; // certain hash structure

#endif // !AE2F_BABEL_TRANSFORMER

#ifndef AE2F_BABEL_TRANSFORMER_FUN
#define AE2F_BABEL_TRANSFORMER_FUN

AE2F_CPP_PREFIX AE2F
/// <param name="a">: ptr stream</param>
/// <param name="b">: transformer function</param>
/// <param name="c">: element size</param>
/// <param name="d">: output count from each element</param>
/// <param name="e">: buffer address</param>
void ae2f_Babel_Transformer(
	ptr_ae2f_Babel_Transformer a,
	ae2f_Babel_Transformer_fun b,
	uint32_t c,
	uint32_t d,
	ptr_ae2f_Dynamic e
);

AE2F_CPP_PREFIX
/// <param name="a">: ptr stream</param>
/// <param name="b">: output index</param>
/// <param name="c">: output buffer address</param>
void ae2f_Babel_Transformer_trigger(
	ptr_ae2f_Babel_Transformer a, 
	uint32_t b, 
	void* c
);

#endif // !AE2F_BABEL_TRANSFORMER_FUN