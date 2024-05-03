# Critical Dependency
- [Container](https://github.com/yuisanae2f/Container)/[Dynamic](https://github.com/yuisanae2f/Container/blob/main/include/ae2fLib/Container/Dynamic.md)

# Transformer
> is the data generator.  
> generates the function from the seed value as `in`.

> This structure assumes an element the given input buffer `in` sliced as bytes of `elWidth`,
> and generates the data as the count of `elCount` from each sliced element.

> Data translation must follow the format of [`ae2f_Babel_Transformer_fun`](#ae2f_babel_transformer_fun)

Code
```c
typedef struct ae2f_Babel_Transformer {
	ae2f_Babel_Transformer_fun fun;

	uint32_t
		elWidth,
		elCount;

	ptr_ae2f_Dynamic in;

}* ptr_ae2f_Babel_Transformer;
```

Ref
- [ae2f_Dynamic](https://github.com/yuisanae2f/Container/blob/main/include/ae2fLib/Container/Dynamic.md)
- [ae2f_Babel_Transformer_fun](#ae2f_babel_transformer_fun)

## `elWidth`
> is a size expectation of each element from [`in`](#in).

Ref
- [in](#in)

## `elCount`
> is a count expectation of the translated data from each element.

Ref
- [in](#in)

## `in`
> an linear buffer which points the source to translate.

Ref
- [ae2f_Dynamic](https://github.com/yuisanae2f/Container/blob/main/include/ae2fLib/Container/Dynamic.md)

## `ae2f_Babel_Transformer_fun`
> is the pointer type of custom function in order to translate the linear input.

Function Writings Instruction
> copies the interpreted data from `src` to `dest`.  
> translates the data from `src` as an Element and copies to `dest`.

Args
> The data from `src` is assumed pointer of every input element from [a linear buffer](#in) of [the structure](#transformer).  
> `idx` is the index from 0 to [`elCount`](#elcount).  
> provided certain memory point is not accessible, `isvalid` will be zero.  

Code
```c
typedef void(*ae2f_Babel_Transformer_fun)(void* dest, void* src, uint32_t idx, bool isvalid);
```

# ready
## ae2f_Babel_Transformer
> initialises the structrue.

Code
```c
void ae2f_Babel_Transformer(
	ptr_ae2f_Babel_Transformer this,
	ae2f_Babel_Transformer_fun funPointer,
	uint32_t elSize,
	uint32_t outCount,
	ptr_ae2f_Dynamic buffer
);
```

Ref
- [ae2f_Babel_Transformer_fun](#ae2f_babel_transformer_fun)

# function trigger
## ae2f_Babel_Transformer_trigger
> is the getter for the translated data.  
> will be translated as an array of translated element.

> copies 

Code
```c
void ae2f_Babel_Transformer_trigger(
	ptr_ae2f_Babel_Transformer this, 
	uint32_t idx, 
	void* buffer
);
```

Ref
- [ae2f_Babel_Transformer_fun](#ae2f_babel_transformer_fun)

# Abstractor
> C++ is type-strict language.  
> It is not able to pass the function pointer with arguments with different data type.

> Following classes translate the given function pointer to the primitive one.

## pure
> Handles the primitive type of function.

Ref
- [ae2f_Babel_Transformer_fun](#ae2f_babel_transformer_fun)

## coloured
> Handles the function with templates.

## binder
> is the function data type handler.

Code
```cpp
template<typename t, typename dest = void, typename src = void>
class binder;
```

Ref
- [Abstractor](#abstractor)
- [Transformer](#transformer)

### `t`
> decides the method of initialising.

- [pure](#pure)
- [coloured](#coloured)

### `dest`, `src`
> decides the type of `dest`, `src` from [`ae2f_Babel_Transformer_fun`](#ae2f_babel_transformer_fun).

Ref
- [ae2f_Babel_Transformer_fun](#ae2f_babel_transformer_fun)

### `fun`
> is the variated function pointer type.

Code
```cpp
typedef void(*fun)(dest*, src*, uint32_t, bool);
```

Ref
- [coloured](#coloured)
- [ae2f_Babel_Transformer_fun](#ae2f_babel_transformer_fun)

### purise
> returns the function pointer `fp` in a type of [`ae2f_Babel_Transformer_fun`](#ae2f_babel_transformer_fun).

Code
```cpp
template<typename aa, typename bb>
const fun purise(void(*fp)(aa*, bb*, uint32_t, bool));
```

### colourise
> is only applicable when [`t`](#t) is [`coloured`](#coloured).

> returns the function pointer `fp` which argument's data type has changed.

Code
```cpp
fun colourise(binder<pure>::fun fp);
```

Ref
- [t](#t)
- [coloured](#coloured)
- [dest, src](#dest-src)

# Classes
## Transformer
- [binder](#binder)::[pure](#pure)
## Transformer::Coloured
- [binder](#binder)::[coloured](#coloured)