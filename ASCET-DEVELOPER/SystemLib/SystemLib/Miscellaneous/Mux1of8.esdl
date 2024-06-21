package SystemLib.Miscellaneous;

/** Mux1of8 switches between the eight inputs values s0,...,s7 on the binary representation of their index. */


stateless class Mux1of8 {
	/** The input value si(index i) is returned with i = b0 + 2*b1+ 4*b2, interpreting FALSE as 0 and TRUE as 1. */
	@no_side_effect
	@generated("blockdiagram", "1b85b563")
	public real value(real in s0, real in s1, real in s2, real in s3, real in s4, real in s5, real in s6, real in s7, boolean in b0, boolean in b1, boolean in b2) {
		return(if b2 then(if b1 then(if b0 then s7 else s6) else(if b0 then s5 else s4)) else(if b1 then(if b0 then s3 else s2) else(if b0 then s1 else s0))); // Main/value 1
	}
}