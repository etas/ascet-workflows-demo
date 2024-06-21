package SystemLib.Bitoperations;

/**
 * toggleBit inverts the bit at the specified position of the argument.
 */
 @c_code
stateless class toggleBit
using Impl_16bit {
	/**
	 * The argument bitArray is returned with the bit at the specified position toggled.
	 */
	public UnsignedInteger getToggleBit(UnsignedInteger in bitArray, UnsignedInteger in position);

	representation Impl_16bit {
		represent getToggleBit.bitArray using {
			datatype = uint16;
		};
		represent getToggleBit.position using {
			datatype = uint8;
		};
		represent getToggleBit return using {
			datatype = uint16;
		};
	}
	representation Impl_32bit {
		represent getToggleBit.bitArray using {
			datatype = uint32;
		};
		represent getToggleBit.position using {
			datatype = uint8;
		};
		represent getToggleBit return using {
			datatype = uint32;
		};
	}
	representation Impl_8bit {
		represent getToggleBit.bitArray using {
			datatype = uint8;
		};
		represent getToggleBit.position using {
			datatype = uint8;
		};
		represent getToggleBit return using {
			datatype = uint8;
		};
	}

}