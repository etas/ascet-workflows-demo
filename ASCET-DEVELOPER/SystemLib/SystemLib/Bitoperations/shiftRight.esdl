package SystemLib.Bitoperations;

/**
 * shiftRight shifts all bits of the argument to the right. The left bits are filled with zeros.
 */

@c_code
stateless class shiftRight
using Impl_16bit {
	/**
	 * The result of the right-shift by k positions is returned. 
	 */
	public UnsignedInteger getShiftRight(UnsignedInteger in bitArray, UnsignedInteger in k);

	representation Impl_16bit {
		represent getShiftRight.bitArray using {
			datatype = uint16;
		};
		represent getShiftRight.k using {
			datatype = uint8;
		};
		represent getShiftRight return using {
			datatype = uint16;
		};
	}
	representation Impl_32bit {
		represent getShiftRight.bitArray using {
			datatype = uint32;
		};
		represent getShiftRight.k using {
			datatype = uint8;
		};
		represent getShiftRight return using {
			datatype = uint32;
		};
	}
	representation Impl_8bit {
		represent getShiftRight.bitArray using {
			datatype = uint8;
		};
		represent getShiftRight.k using {
			datatype = uint8;
		};
		represent getShiftRight return using {
			datatype = uint8;
		};
	}

}