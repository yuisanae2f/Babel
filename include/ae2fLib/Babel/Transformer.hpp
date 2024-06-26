#pragma once
#include "./Transformer.h"

#ifdef __cplusplus
#ifndef AE2F_BABEL_TRANSFORMER_CPP
#define AE2F_BABEL_TRANSFORMER_CPP
namespace ae2f {
	namespace Babel {
		class Transformer;
	}

	template<>
	class fun<Babel::Transformer> {
	public:
		class pure;
		class coloured;

		/// <param name="t">: reading method</param>
		/// <param name="dest">: ptr type dest</param>
		/// <param name="src">: ptr type src</param>
		template<typename t, typename dest = void, typename src = void>
		class binder;
	};

	template<>
	class fun<Babel::Transformer>::binder<fun<Babel::Transformer>::pure> : public def<struct ae2f_Babel_Transformer> {
	public:
		typedef ae2f_Babel_Transformer_fun fun;
		typedef ae2f::fun<Babel::Transformer>::binder<ae2f::fun<Babel::Transformer>::pure> itself;

	private:
		ptr p;
	public:
		Container::Dynamic::ptr& buffin;

		inline binder(ptr p)
			: p(p), buffin(p->in) {}

		inline ptr raw() {
			return p;
		}

		/// <param name="a">: output buffer</param>
		/// <param name="b">: output index</param>
		inline void trigger(void* a, uint32_t b) {
			ae2f_Babel_Transformer_trigger(this->p, b, a);
		}

#define ae2f_colour template<typename aa, typename bb>

		/// <param name="aa">: ptr type dest</param>
		/// <param name="bb">: ptr type src</param>
		ae2f_colour inline const fun purise(void(*a)(aa*, bb*, uint32_t, bool)) {
			return ((fun)a);
		}

		/// <param name="aa">: ptr type dest</param>
		/// <param name="bb">: ptr type src</param>
		ae2f_colour inline operator ae2f::fun<Babel::Transformer>::binder<ae2f::fun<Babel::Transformer>::coloured, aa, bb>();

#undef ae2f_colour
	};

	/// <param name="aa">: ptr type dest</param>
	/// <param name="bb">: ptr type src</param>
	template<typename aa, typename bb>
	class fun<Babel::Transformer>::binder<fun<Babel::Transformer>::coloured, aa, bb> :
		public fun::binder<fun::pure>
	{
	public:
		inline binder(ptr p)
			: binder<ae2f::fun<ae2f::Babel::Transformer>::pure>(p) {}

		typedef void(*fun)(aa*, bb*, uint32_t, bool);

		inline aa operator()(uint32_t i) {
			if (!this->raw()->in)
				throw 0;

			aa rtn;
			::ae2f_Babel_Transformer_trigger(this->raw(), i, (void*)&rtn);
			return rtn;
		}

		inline fun colourise(binder<pure>::fun a) {
			return (fun)a;
		}
	};

	/// <param name="aa">: ptr type dest</param>
	/// <param name="bb">: ptr type src</param>
	template<typename aa, typename bb>
	inline ae2f::fun<Babel::Transformer>::binder<ae2f::fun<Babel::Transformer>::pure>::operator
		ae2f::fun<ae2f::Babel::Transformer>::binder<ae2f::fun<ae2f::Babel::Transformer>::coloured, aa, bb>() {
		return this->p;
	}

	namespace Babel {
		class Transformer :
			public fun<Transformer>::binder<fun<Transformer>::pure> {
		private:
			struct ae2f_Babel_Transformer obj;
		public:
			/// <param name="a">: function</param>
			/// <param name="b">: element size</param>
			/// <param name="c">: output for each element</param>
			/// <param name="d">: buffer addr</param>
			inline Transformer(
				void(*a)(void*, void*, uint32_t, bool),
				uint32_t b,
				uint32_t c,
				Container::Dynamic::getter d
			) : binder(&obj) {
				ae2f_Babel_Transformer(&this->obj, a, b, c, d.raw());
			}

			inline Transformer(
				ptr a
			) : binder(&obj) {}

#define ae2f_colour template<typename aa, typename bb>
			ae2f_colour class Coloured;

			/// <param name="aa">: ptr type dest</param>
			/// <param name="bb">: ptr type src</param>
			ae2f_colour operator Coloured<aa, bb>();
#undef ae2f_colour
		};


		/// <param name="aa">: ptr type dest</param>
		/// <param name="bb">: ptr type src</param>
		template<typename aa = void, typename bb = void>
		class Transformer::Coloured :
			public ae2f::fun<Transformer>::binder<ae2f::fun<Transformer>::coloured, aa, bb>
		{
		private:
			orig obj;

		public:
			typedef ae2f::fun<Transformer>::binder<ae2f::fun<Transformer>::coloured, aa, bb> binder;

			/// <param name="a">: function</param>
			/// <param name="b">: element size</param>
			/// <param name="c">: output for each element</param>
			/// <param name="d">: buffer addr</param>
			inline Coloured(
				void(*a)(aa*, bb*, uint32_t, bool),
				uint32_t b,
				uint32_t c,
				Container::Dynamic::getter d
			)
				: binder(&this->obj)
			{
				::ae2f_Babel_Transformer(&this->obj, (Transformer::fun)a, b, c, d.raw());
			}

			inline Coloured(
				ptr a
			)
				: Transformer(a) {}
		};

		template<typename aa, typename bb>
		inline Transformer::operator Coloured<aa, bb>() {
			return &this->raw();
		}
	}
}
#endif // !AE2F_BABEL_TRANSFORMER_CPP

#endif // AE2F_CPP