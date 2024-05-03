#include "ae2fLib/Babel/Transformer.h"

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
) {
	a->elCount = d;
	a->elWidth = c;
	a->fun = b;
	a->in = e;
}

void ae2f_Babel_Transformer_trigger(ptr_ae2f_Babel_Transformer a, uint32_t b, void* c) {
	if (a->fun)
		a->fun(
			c, 
			(void*)(a->in->c.bt1 + a->elWidth * (b / a->elCount)), 
			(b % a->elCount), 
			(a->in->len > a->elWidth * (b / a->elCount))
		);
}