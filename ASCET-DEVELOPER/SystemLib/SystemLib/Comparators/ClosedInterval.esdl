package SystemLib.Comparators;

/** 
 * ClosedInterval returns TRUE if the value x is in the closed interval defined by A and B.
*/

stateless class ClosedInterval {
	/** 
	 * TRUE is returned if A <= x <= B. Otherwise, FALSE is returned.
	 */
	@no_side_effect
	@generated("blockdiagram", "6846b816")
	public boolean value(real in A, real in x, real in B) {
		return((A <= x) && (x <= B)); // Main/value 1
	}
}