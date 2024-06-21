package SystemLib.Math;

/**
 * MathLib implements interface to C standard library.
 * By default all math functions are implemented with double precision. Therefore default representation R64 is used.
 * Also in case of physical code generation this class will use double precision variant of math functions.
 * To use the single precision variant, consumer of this class has to select R32 representation.
 */
@include("math.h")
stateless class MathLib
using R64 {
	@symbol("acos")
	extern public real acos(real val);

	@symbol("asin")
	extern public real asin(real val);

	@symbol("atan")
	extern public real atan(real val);

	@symbol("atan2")
	extern public real atan2(real x, real y);

	@symbol("ceil")
	extern public real ceil(real val);

	@symbol("cos")
	extern public real cos(real val);

	@symbol("cosh")
	extern public real cosh(real val);

	@symbol("exp")
	extern public real exp(real val);

	@symbol("floor")
	extern public real floor(real val);

	@symbol("log")
	extern public real log(real val);

	@symbol("log10")
	extern public real log10(real val);

	@symbol("pow")
	extern public real pow(real val, real factor);

	@symbol("sin")
	extern public real sin(real val);

	@symbol("sinh")
	extern public real sinh(real val);

	@symbol("sqrt")
	extern public real sqrt(real val);

	@symbol("tan")
	extern public real tan(real val);

	@symbol("tanh")
	extern public real tanh(real val);

	representation R32 {
		@symbol("acosf")
		represent acos;
		@symbol("asinf")
		represent asin;
		@symbol("atanf")
		represent atan;
		@symbol("atan2f")
		represent atan2;
		@symbol("ceilf")
		represent ceil;
		@symbol("cosf")
		represent cos;
		@symbol("coshf")
		represent cosh;
		@symbol("expf")
		represent exp;
		@symbol("floorf")
		represent floor;
		@symbol("logf")
		represent log;
		@symbol("log10f")
		represent log10;
		@symbol("powf")
		represent pow;
		@symbol("sinf")
		represent sin;
		@symbol("sinhf")
		represent sinh;
		@symbol("sqrtf")
		represent sqrt;
		@symbol("tanf")
		represent tan;
		@symbol("tanhf")
		represent tanh;

		represent sqrt.val using {
			datatype = float32;
		};
		represent pow.factor using {
			datatype = float32;
		};
		represent cos.val using {
			datatype = float32;
		};
		represent sinh.val using {
			datatype = float32;
		};
		represent tanh.val using {
			datatype = float32;
		};
		represent acos.val using {
			datatype = float32;
		};
		represent atan2.x using {
			datatype = float32;
		};
		represent exp.val using {
			datatype = float32;
		};
		represent log10.val using {
			datatype = float32;
		};
		represent sqrt return using {
			datatype = float32;
		};
		represent sin return using {
			datatype = float32;
		};
		represent tan return using {
			datatype = float32;
		};
		represent cosh return using {
			datatype = float32;
		};
		represent asin return using {
			datatype = float32;
		};
		represent atan return using {
			datatype = float32;
		};
		represent exp return using {
			datatype = float32;
		};
		represent log10 return using {
			datatype = float32;
		};
		represent floor return using {
			datatype = float32;
		};
		represent pow.val using {
			datatype = float32;
		};
		represent sin.val using {
			datatype = float32;
		};
		represent tan.val using {
			datatype = float32;
		};
		represent cosh.val using {
			datatype = float32;
		};
		represent asin.val using {
			datatype = float32;
		};
		represent atan.val using {
			datatype = float32;
		};
		represent atan2.y using {
			datatype = float32;
		};
		represent log.val using {
			datatype = float32;
		};
		represent ceil.val using {
			datatype = float32;
		};
		represent floor.val using {
			datatype = float32;
		};
		represent pow return using {
			datatype = float32;
		};
		represent cos return using {
			datatype = float32;
		};
		represent sinh return using {
			datatype = float32;
		};
		represent tanh return using {
			datatype = float32;
		};
		represent acos return using {
			datatype = float32;
		};
		represent atan2 return using {
			datatype = float32;
		};
		represent log return using {
			datatype = float32;
		};
		represent ceil return using {
			datatype = float32;
		};
	}
	representation R64 {
		represent sqrt.val using {
			datatype = float64;
		};
		represent pow.val using {
			datatype = float64;
		};
		represent pow.factor using {
			datatype = float64;
		};
		represent sin.val using {
			datatype = float64;
		};
		represent cos.val using {
			datatype = float64;
		};
		represent tan.val using {
			datatype = float64;
		};
		represent sinh.val using {
			datatype = float64;
		};
		represent cosh.val using {
			datatype = float64;
		};
		represent tanh.val using {
			datatype = float64;
		};
		represent asin.val using {
			datatype = float64;
		};
		represent acos.val using {
			datatype = float64;
		};
		represent atan.val using {
			datatype = float64;
		};
		represent atan2.x using {
			datatype = float64;
		};
		represent atan2.y using {
			datatype = float64;
		};
		represent exp.val using {
			datatype = float64;
		};
		represent log.val using {
			datatype = float64;
		};
		represent log10.val using {
			datatype = float64;
		};
		represent ceil.val using {
			datatype = float64;
		};
		represent floor.val using {
			datatype = float64;
		};
		represent sqrt return using {
			datatype = float64;
		};
		represent pow return using {
			datatype = float64;
		};
		represent sin return using {
			datatype = float64;
		};
		represent cos return using {
			datatype = float64;
		};
		represent tan return using {
			datatype = float64;
		};
		represent sinh return using {
			datatype = float64;
		};
		represent cosh return using {
			datatype = float64;
		};
		represent tanh return using {
			datatype = float64;
		};
		represent asin return using {
			datatype = float64;
		};
		represent acos return using {
			datatype = float64;
		};
		represent atan return using {
			datatype = float64;
		};
		represent atan2 return using {
			datatype = float64;
		};
		represent exp return using {
			datatype = float64;
		};
		represent log return using {
			datatype = float64;
		};
		represent log10 return using {
			datatype = float64;
		};
		represent ceil return using {
			datatype = float64;
		};
		represent floor return using {
			datatype = float64;
		};
	}
}
