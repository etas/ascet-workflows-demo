/*
 * A list of common coherent derived units used in e.g. mechanics, expressed in term of SI base units.
 *
 * See https://en.wikipedia.org/wiki/SI_derived_unit.
 */

package units.common;

import units.si.kg;
import units.si.m;
import units.si.km;
import units.si.s;
import units.non_si.h;

/**
 * Square meter, measuring area.
 */
unit m2 = m^2;

/**
 * Cubic meter, measuring volume.
 */
unit m3 = m^3;

/**
 * Meter per second, measuring speed or velocity.
 */
unit mps = m/s;

/**
 * Kilometer per hour, measuring speed or velocity.
 */
unit kmph = km/h;

/**
 * Meter per square second, measuring acceleration (rate of change of velocity).
 */
unit mps2 = m/(s^2);

/**
 * Kilogram per cubic meter, measuring density.
 */
unit kgpm3 = kg/m3;
