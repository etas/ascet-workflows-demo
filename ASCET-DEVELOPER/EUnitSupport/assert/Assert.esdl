package assert;

type SignedInteger is native integer using sint32;

type UnsignedInteger is native integer using uint32;

/**
 * Interface to google-test framework with numeric assertion functions that verify the behavior of a class state or 
 * function against the expected behavior.
 * <p>
 * The assertions come in pairs that test the same thing but have different effects on the current function. 
 * <li> assert* versions generate fatal failures when they fail, and abort the current function.
 * <li> expect* versions generate nonfatal failures, which don't abort the current function.
 * <p>
 * Assertion methods for signed integers (sint32), unsigned integers (uint32) and real values (float64) can be used to compare
 * numeric values.
 */
@include("Etas_Ascet_Assertion.h")
stateless class Assert {
	
	/* ***********************************************************************************************************
	 * assert* versions generate fatal failures when they fail, and abort the current function
	 * Use assert* if it doesn't make sense to continue when the assertion in question fails.
	 * ***********************************************************************************************************/
	 
	/**
	 * Basic assertion that verifies aCondition is true.
	 * The method yields a fatal failure and returns from the current function
	 */
	@symbol("ASSERT_TRUE") 
	extern public void assertTrue(boolean aCondition);
	
	/**
	 * Basic assertion that verifies aCondition is false.
	 * The method yields a fatal failure and returns from the current function
	 */
	@symbol("ASSERT_FALSE") 
	extern public void assertFalse(boolean aCondition);
	
	/**
	 * Binary comparison that verifies two real values are equal (value == expected). The method yields a fatal failure and 
	 * returns from the current function. 
	 * <p>
	 * Due to round-off errors, it is very unlikely that two floating-points will match exactly. Therefore,
	 * it is better to compare by a fixed relative error bound, except for values close to 0 due to the loss of precision.
	 * <p>
	 * See also:
	 * <li> assertFloatEqual(value, expected)
	 * <li> assertDoubleEqual(value, expected)
	 * <li> assertNear(value, expected, abs_error)
	 * <p>
	 */
	@symbol("ASSERT_EQ") 
	extern public void assertEqual(real value, real expected);
	
	/**
	 * Binary comparison that verifies two integer values are equal (value == expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_INT_EQ")
	extern public void assertIntEqual(SignedInteger value, SignedInteger expected);
	
	/**
	 * Binary comparison that verifies two unsigned integer values are equal (value == expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_UINT_EQ")	
	extern public void assertUIntEqual(UnsignedInteger value, UnsignedInteger expected);
	
	/**
	 * Floating-point comparison that verifies two float values are almost equal (abs(value - expected) <= FLT_EPSILON.
	 * FLT_EPSILON is set to 4ULPs (Units in the Last Place). The method yields a fatal failure and returns from the current function.
	 * <p>
	 * To select a specific error bound, use assertNear(value, expected, abs_error)
	 */	
	@symbol("ASSERT_FLOAT_EQ") 
	extern public void assertFloatEqual(real value, real expected);
	
	/**
	 * Floating-point comparison that verifies two double values are almost equal (abs(value - expected) <= FLT_EPSILON).
	 * FLT_EPSILON is set to 4ULPs (Units in the Last Place). The method yields a fatal failure and returns from the current function.
	 * <p>
	 * To select a specific error bound, use assertNear(value, expected, abs_error)
	 */	
	@symbol("ASSERT_DOUBLE_EQ") 
	extern public void assertDoubleEqual(real value, real expected);
	
	/**
	 * Floating-point comparison that verifies two double values are almost equal with the difference does not exceed the given absolute error.
	 * The method yields a fatal failure and returns from the current function.
	 * <p>
	 * If the system default error bound shall be selected, use 
	 * <li>assertFloatEqual(value, expected)
	 * <li>assertDoubleEqual(value, expected)
	 */
	@symbol("ASSERT_NEAR")	
	extern public void assertNear(real value, real expected, real abs_error);
	
	/**
	 * Binary comparison that verifies two real values are not equal (value != expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_NE") 
	extern public void assertNotEqual(real value, real expected);
	
	/**
	 * Binary comparison that verifies two integer values are not equal (value != expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_INT_NE") 
	extern public void assertIntNotEqual(SignedInteger value, SignedInteger expected);
	
	/**
	 * Binary comparison that verifies two unsigned integer values are not equal (value != expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_UINT_NE")	 
	extern public void assertUIntNotEqual(UnsignedInteger value, UnsignedInteger expected);

	/**
	 * Binary comparison that verifies a real value is less than expected (value < expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_LT") 
	extern public void assertLessThan(real value, real expected);

	/**
	 * Binary comparison that verifies an integer value is less than expected (value < expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_INT_LT")	
	extern public void assertIntLessThan(SignedInteger value, SignedInteger expected);

	/**
	 * Binary comparison that verifies an unsigned integer value is less than expected (value < expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_UINT_LT") 
	extern public void assertUIntLessThan(UnsignedInteger value, UnsignedInteger expected);
	
	/**
	 * Binary comparison that verifies a real value is less than or equal to expected (value <= expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_LE")
	extern public void assertLessThanOrEqual(real value, real expected);
	
	/**
	 * Binary comparison that verifies an integer value is less than or equal to expected (value <= expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_INT_LE") 
	extern public void assertIntLessThanOrEqual(SignedInteger value, SignedInteger expected);

	/**
	 * Binary comparison that verifies an unsigned integer value is less than or equal to expected (value <= expected).
	 * The method yields a fatal failure and returns from the current function.
	 */	
	@symbol("ASSERT_UINT_LE") 
	extern public void assertUIntLessThanOrEqual(UnsignedInteger value, UnsignedInteger expected);
	
	/**
	 * Binary comparison that verifies a real value is greater than expected (value > expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_GT") 
	extern public void assertGreaterThan(real value, real expected);
	
	/**
	 * Binary comparison that verifies an integer value is greater than expected (value <= expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_INT_GT")	 
	extern public void assertIntGreaterThan(SignedInteger value, SignedInteger expected);

	/**
	 * Binary comparison that verifies an unsigned integer value is greater than expected (value <= expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_UINT_GT") 
	extern public void assertUIntGreaterThan(UnsignedInteger value, UnsignedInteger expected);

	/**
	 * Binary comparison that verifies a real value is greater than or equal to expected (value >= expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_GE") 
	extern public void assertGreaterThanOrEqual(real value, real expected);
	
	/**
	 * Binary comparison that verifies an integer value is greater than or equal to expected (value >= expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_INT_GE")	
	extern public void assertIntGreaterThanOrEqual(SignedInteger value, SignedInteger expected);

	/**
	 * Binary comparison that verifies an unsigned integer value is greater than or equal to expected (value >= expected).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_UINT_GE") 
	extern public void assertUIntGreaterThanOrEqual(UnsignedInteger value, UnsignedInteger expected);
	
	/**
	 * Numeric comparison that verifies a real value is in expected range (left <= value <= right).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_BETWEEN") 
	extern public void assertBetween(real value, real left, real right);
	
	/**
	 * Numeric comparison that verifies an integer value is in expected range (left <= value <= right).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_INT_BETWEEN") 
	extern public void assertIntBetween(SignedInteger value, SignedInteger left, SignedInteger right);
	
	/**
	 * Numeric comparison that verifies an unsigned integer value is in expected range (left <= value <= right).
	 * The method yields a fatal failure and returns from the current function.
	 */
	@symbol("ASSERT_UINT_BETWEEN") 
	extern public void assertUIntBetween(UnsignedInteger value, UnsignedInteger left, UnsignedInteger right);
	
	/* ***********************************************************************************************************
	 * EXPECT_* versions generate nonfatal failures, which don't abort the current function. 
	 * Usually EXPECT_* are preferred, as they allow more than one failure to be reported in a test.
	 * ***********************************************************************************************************/
	 
	/**
	 * Basic expect assertion that verifies aCondition is true.
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_TRUE") 
	extern public void expectTrue(boolean aCondition);

	/**
	 * Basic expect assertion that verifies aCondition is false.
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_FALSE") 
	extern public void expectFalse(boolean aCondition);

	/**
	 * Binary comparison that verifies two real values are equal (value == expected). The method yields a nonfatal failure, 
	 * allowing the function to continue running.
	 * <p>
	 * Due to round-off errors, it is very unlikely that two floating-points will match exactly. Therefore,
	 * it is better to compare by a fixed relative error bound, except for values close to 0 due to the loss of precision.
	 * <p>
	 * See also:
	 * <li> expectFloatEqual(value, expected)
	 * <li> expectDoubleEqual(value, expected)
	 * <li> expectNear(value, expected, abs_error)
	 * <p>
	 */
	@symbol("EXPECT_EQ") 
	extern public void expectEqual(real value, real expected);

	/**
	 * Binary comparison that verifies two integer values are equal (value == expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_INT_EQ") 
	extern public void expectIntEqual(SignedInteger value, SignedInteger expected);

	/**
	 * Binary comparison that verifies two unsinged integer values are equal (value == expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */	
	@symbol("EXPECT_UINT_EQ") 
	extern public void expectUIntEqual(UnsignedInteger value, UnsignedInteger expected);

	/**
	 * Floating-point comparison that verifies two float values are almost equal (abs(value - expected) <= FLT_EPSILON.
	 * FLT_EPSILON is set to 4ULPs (Units in the Last Place). The method yields a nonfatal failure, allowing the function to continue running.
	 * <p>
	 * To select a specific error bound, use expectNear(value, expected, abs_error)
	 */
	@symbol("EXPECT_FLOAT_EQ") 
	extern public void expectFloatEqual(real value, real expected);
	
	/**
	 * Floating-point comparison that verifies two double values are almost equal (abs(value - expected) <= FLT_EPSILON).
	 * FLT_EPSILON is set to 4ULPs (Units in the Last Place). The method yields a nonfatal failure, allowing the function to continue running.
	 * <p>
	 * To select a specific error bound, use expectNear(value, expected, abs_error)
	 */	
	@symbol("EXPECT_DOUBLE_EQ") 
	extern public void expectDoubleEqual(real value, real expected);
	
	/**
	 * Floating-point comparison that verifies two double values are almost equal with the difference does not exceed the given absolute error.
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 * <p>
	 * If the system default error bound shall be selected, use 
	 * <li>expectFloatEqual(value, expected)
	 * <li>expectDoubleEqual(value, expected)
	 */	
	@symbol("EXPECT_NEAR") 
	extern public void expectNear(real value, real expected, real abs_error);
	
	/**
	 * Binary comparison that verifies two real values are not equal (value != expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_NE") 
	extern public void expectNotEqual(real value, real expected);
	
	/**
	 * Binary comparison that verifies two integer values are not equal (value != expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */	
	@symbol("EXPECT_INT_NE") 
	extern public void expectIntNotEqual(SignedInteger value, SignedInteger expected);
	
	/**
	 * Binary comparison that verifies two unsigned integer values are not equal (value != expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */	
	@symbol("EXPECT_UINT_NE") 
	extern public void expectUIntNotEqual(UnsignedInteger value, UnsignedInteger expected);

	/**
	 * Binary comparison that verifies a real value is less than expected (value < expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_LT") 
	extern public void expectLessThan(real value, real expected);

	/**
	 * Binary comparison that verifies an integer value is less than expected (value < expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_INT_LT") 
	extern public void expectIntLessThan(SignedInteger value, SignedInteger expected);

	/**
	 * Binary comparison that verifies an unsigned integer value is less than expected (value < expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_UINT_LT") 
	extern public void expectUIntLessThan(UnsignedInteger value, UnsignedInteger expected);
	
	/**
	 * Binary comparison that verifies a real value is less than or equal to expected (value <= expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_LE") 
	extern public void expectLessThanOrEqual(real value, real expected);
	
	/**
	 * Binary comparison that verifies an integer value is less than or equal to expected (value <= expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */	
	@symbol("EXPECT_INT_LE") 
	extern public void expectIntLessThanOrEqual(SignedInteger value, SignedInteger expected);

	/**
	 * Binary comparison that verifies an unsigned integer value is less than or equal to expected (value <= expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_UINT_LE") 
	extern public void expectUIntLessThanOrEqual(UnsignedInteger value, UnsignedInteger expected);
	
	/**
	 * Binary comparison that verifies a real value is greater than expected (value > expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_GT")	 
	extern public void expectGreaterThan(real value, real expected);
	
	/**
	 * Binary comparison that verifies an integer value is greater than expected (value <= expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_INT_GT") 
	extern public void expectIntGreaterThan(SignedInteger value, SignedInteger expected);

	/**
	 * Binary comparison that verifies an unsigned integer value is greater than expected (value <= expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_UINT_GT") 
	extern public void expectUIntGreaterThan(UnsignedInteger value, UnsignedInteger expected);

	/**
	 * Binary comparison that verifies a real value is greater than or equal to expected (value >= expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_GE") 
	extern public void expectGreaterThanOrEqual(real value, real expected);
	
	/**
	 * Binary comparison that verifies an integer value is greater than or equal to expected (value >= expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_INT_GE") 
	extern public void expectIntGreaterThanOrEqual(SignedInteger value, SignedInteger expected);

	/**
	 * Binary comparison that verifies an unsigned integer value is greater than or equal to expected (value >= expected).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_UINT_GE") 
	extern public void expectUIntGreaterThanOrEqual(UnsignedInteger value, UnsignedInteger expected);
	
	/**
	 * Numeric comparison that verifies a real value is in expected range (left <= value <= right).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_BETWEEN") 
	extern public void expectBetween(real value, real left, real right);
	
	/**
	 * Numeric comparison that verifies an integer value is in expected range (left <= value <= right).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_INT_BETWEEN") 
	extern public void expectIntBetween(SignedInteger value, SignedInteger left, SignedInteger right);
	
	/**
	 * Numeric comparison that verifies an unsigned integer value is in expected range (left <= value <= right).
	 * The method yields a nonfatal failure, allowing the function to continue running.
	 */
	@symbol("EXPECT_UINT_BETWEEN") 
	extern public void expectUIntBetween(UnsignedInteger value, UnsignedInteger left, UnsignedInteger right);
	
	/**
	 * An explicit success for documentary purposes. It does not have any effect as only failures influence
	 * the result of a test - without failures, tests succeed naturally.
	 */
	@symbol("SUCCEED") 
	extern public void succeed();

	/**
	 * An explicit fatal failure that immediately returns from the current function.
	 */
	@symbol("FAIL") 
	extern public void fail();

	/**
	 * A fatal failure that immediately returns from the current function. Use this method
	 * to indicate yet unimplemented tests.
	 */
	@symbol("UNIMPLEMENTED") 
	extern public void unimplemented();
}
