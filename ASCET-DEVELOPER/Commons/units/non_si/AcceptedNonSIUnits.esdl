/*
 * This is a list of units that are not defined as part of the International System of Units (SI) but are otherwise
 * mentioned in the SI Brochure, listed as being accepted for use alongside SI-units, or for explanatory purposes.
 *
 * NOTE: The SI prefixes can be used with several of these units, but not, for example, with the non-SI units of time.
 *
 * NOTE: This file contains the most commonly used non-SI units. For an extended list, import the UnitExtensions project.
 *
 * See https://en.wikipedia.org/wiki/Non-SI_units_mentioned_in_the_SI.
 */

package units.non_si;

import units.si.s;
import units.si.m;

/**
 * Unit <i>minute</i>, measuring time. 1 minute is equivalent to 60 s.
 */
unit minute = 60*s;

/**
 * Unit <i>hour</i>, measuring time. 1 h is equivalent to 60 minute or 3600 s.
 */
unit h = 3600*s;

/**
 * Unit <i>day</i>, measuring time. 1 d is equivalent to 24 h or 1440 minute or 86400 s.
 */
unit d = 86400*s;

/**
 * Unit <i>litre</i>, measuring volume. 1 l is equivalent to 0.001 m<sup>3</sup>.
 */
unit l = 1.0e-3*m^3;
