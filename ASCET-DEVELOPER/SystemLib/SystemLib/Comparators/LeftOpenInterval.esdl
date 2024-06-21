package SystemLib.Comparators;

/** 
 * LeftOpenInterval returns TRUE if the value x is in the left open interval defined by A and B.
*/

stateless class LeftOpenInterval  {
	/** 
	 * TRUE is returned if A < x <= B. Otherwise, FALSE is returned.
	 */
	@no_side_effect
	@generated("blockdiagram", "918ddec3")
	public boolean value(real in A, real in x, real in B) {
		return((A < x) && (x <= B)); // Main/value 1
	}
}