package SystemLib.Nonlinears;

/** Limiter returns the input x limited by mn and mx. */

stateless class Limiter {
	/** The input x is limited by mn and mx and is returned, i.e max( min(x, mx), mn). There is no check if mn <= mx. */
	@no_side_effect
	@generated("blockdiagram", "ea6947b0")
	public real value(real in mn, real in x, real in mx) {
		return max(min(x, mx), mn); // Main/value 1
	}
}