/*
 * In the International System of Units (SI), designations of multiples and subdivision of any unit may be arrived
 * by prepending the name of the unit with the prefixes deka, hecto, and kilo meaning, respectively, 10, 100, and
 * 1000, and deci, centi, and milli, meaning, respectively, one-tenth, one-hundredth, and one-thousandth.
 *
 * NOTE: This file contains the most commonly used non-conherent SI units with prefixes. For an extended list, import the
 * UnitExtensions project.
 *
 * See https://en.wikipedia.org/wiki/Metric_prefix.
 */

package units.si;

/**
 * Unit with SI prefix <i>centimeter</i>, measuring length. One centimeter is equal to one hundredth of a metre (0.01 m).
 */
unit cm = 1.0e-2*m;

/**
 * Unit with SI prefix <i>millimeter</i>, measuring length. One millimeter is equal to one thousandth of a meter (0.001 m).
 */
unit mm = 1.0e-3*m;

/**
 * Unit with SI prefix <i>kilometer</i>, measuring length. One kilometer is equal to one thousand meters (1000 m).
 */
unit km = 1.0e3*m;

/**
 * SI previous base unit <i>gram</i>, measuring mass. It was replaced by the kilogram in order to obtain coherence
 * with the practical units ampere and volt. 1 kg is equal to 1000 g.
 */
unit g = 1.0e-3*kg;

/**
 * Unit with SI prefix <i>milligram</i>, measuring mass. One milligram is equal to one thousandth of a gram (0.001 g).
 */
unit mg = 1.0e-6*kg;

/**
 * Unit with SI prefix <i>millisecond</i>, measuring time. One millisecond is equal to one thousandth of a second (0.001 s).
 */
unit ms = 1.0e-3*s;

/**
 * Unit with SI prefix <i>microsecond</i> (μs), measuring time. One microsecond is equal to one millionth 
 * of a second (1×10<sup>-6</sup> s).
 */
unit mus = 1.0e-6*s;
