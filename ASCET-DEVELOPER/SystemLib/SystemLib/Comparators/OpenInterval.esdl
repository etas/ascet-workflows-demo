package SystemLib.Comparators;

/** 
 * OpenInterval returns TRUE if the value x is in the open interval defined by A and B.
*/

stateless class OpenInterval {
	/** 
	 * TRUE is returned if A < x < B. Otherwise, FALSE is returned.
	 */
	@no_side_effect
	@generated("blockdiagram", "eb44a45d")
	public boolean value(real in A, real in x, real in B) {
		return((A < x) && (x < B)); // Main/value 1
	}
}