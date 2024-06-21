package SystemLib.Bitoperations;

/**
 * clearBit resets the bit at the specified position of the argument. 
 */

@c_code
stateless class clearBit
using Impl_16bit {
	/**
	 * The argument bitArray is returned with a zero-bit at the specified position.
	 */
	public UnsignedInteger getClearBit(UnsignedInteger in bitArray, UnsignedInteger in position);

	representation Impl_16bit {
		represent getClearBit.bitArray using {
			datatype = uint16;
		};
		represent getClearBit.position using {
			datatype = uint8;
		};
		represent getClearBit return using {
			datatype = uint16;
		};
	}
	representation Impl_32bit {
		represent getClearBit.bitArray using {
			datatype = uint32;
		};
		represent getClearBit.position using {
			datatype = uint8;
		};
		represent getClearBit return using {
			datatype = uint32;
		};
	}
	representation Impl_8bit {
		represent getClearBit.bitArray using {
			datatype = uint8;
		};
		represent getClearBit.position using {
			datatype = uint8;
		};
		represent getClearBit return using {
			datatype = uint8;
		};
	}

}