/*
 * The International System of Units (SI) assigns special names to 22 derived units, which includes two dimensionless
 * derived units, the radian (rad) and the steradian (sr).
 *
 * NOTE: This file contains the most commonly used units out of the 22 total derived SI units with special names. For a complete
 * list, import the UnitExtensions project.
 *
 * See https://en.wikipedia.org/wiki/SI_derived_unit.
 */

package units.si;

/**
 * Unit <i>radian</i>, measuring plane angle. It is a dimensionless unit equivalent to m⋅m<sup>-1</sup>.
 */
unit rad = m/m;

/**
 * Unit <i>steradian</i>, measuring solid angle. It is a dimensionless unit equivalent to m<sup>2</sup>⋅m<sup>-2</sup>.
 */
unit sr = m^2/m^2;

/**
 * Unit <i>hertz</i>, measuring frequency. It is equivalent to s<sup>-1</sup>.
 */
unit Hz = s^-1;

/**
 * Unit <i>newton</i>, measuring force or weight. It is equivalent to kg⋅m⋅s<sup>-2</sup>.
 */
unit N = kg*m*s^-2;

/**
 * Unit <i>pascal</i>, measuring pressure or stress. It is equivalent to N⋅m<sup>2</sup>.
 */
unit Pa = kg*m^-1*s^-2;

/**
 * Unit <i>joule</i>, measuring energy, work or heat. It is equivalent to N⋅m, C⋅V, and W⋅s.
 */
unit J = kg*m^2*s^-2;

/**
 * Unit <i>watt</i>, measuring power or radiant flux. It is equivalent to J⋅s<sup>-1</sup> and V⋅A.
 */
unit W = kg*m^2*s^-3;

/**
 * Unit <i>coulomb</i>, measuring electric charge or quantity of electricity. It is equivalent to A⋅s and F⋅V.
 */
unit C = A*s;

/**
 * Unit <i>volt</i>, measuring voltage, electrical potential difference, or electromotive force. It is equivalent
 * to W⋅A<sup>-1</sup> and J⋅C<sup>-1</sup>
 */
unit V = kg*m^2*A^-1*s^-3;

/**
 * Unit <i>farad</i>, measuring electrical capacitance. It is equivalent to C⋅V<sup>-1</sup> and s⋅Ω<sup>-1</sup>.
 */
unit F = A^2*s^4*kg^-1*m^-2;

/**
 * Unit <i>ohm</i> (Ω), measuring electrical resistance, impedance, or reactance. It is equivalent
 * to S<sup>-1</sup> and V⋅A<sup>-1</sup>.
 */
unit Ohm = kg*m^2*A^-2*s^-3;

/**
 * Unit <i>degree celsius</i> (°C), measuring temperature relative to 273.15 K.
 */
unit degC;
