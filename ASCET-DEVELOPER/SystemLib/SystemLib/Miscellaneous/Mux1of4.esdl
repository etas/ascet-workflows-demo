package SystemLib.Miscellaneous;

/** Mux1of4 switches between the four inputs values s0,...,s3 on the binary representation of their index.
*/


stateless class Mux1of4 {
	/** The input value si (index i) is returned with i = b0 + 2*b1, interpreting FALSE as 0 and TRUE as 1. */
	@no_side_effect
	@generated("blockdiagram", "f42121e2")
	public real value(real in s0, real in s1, real in s2, real in s3, boolean in b0, boolean in b1) {
		return(if b1 then(if b0 then s3 else s2) else(if b0 then s1 else s0)); // Main/value 1
	}
}