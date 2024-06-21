package SystemLib.Bitoperations;

/**
 * writeByte writes the values of eight logical inputs to the eight least significant bits of the argument.
 */

@c_code
stateless class writeByte
using Impl_16bit {
	/**
	 * The argument is returned with the values of b0 to b7 written to the bit positions 0 to 7. 0 is the position of the LSB and the logical values TRUE and FALSE are mapped to 1 and 0 respectively.
	 */
	public UnsignedInteger getWriteByte(UnsignedInteger in bitArray, boolean in b0, boolean in b1, boolean in b2, boolean in b3, boolean
			in b4, boolean in b5, boolean in b6, boolean in b7);

	representation Impl_16bit {
		represent getWriteByte.b0 using {
			datatype = sint8;
		};
		represent getWriteByte.b1 using {
			datatype = sint8;
		};
		represent getWriteByte.b2 using {
			datatype = sint8;
		};
		represent getWriteByte.b3 using {
			datatype = sint8;
		};
		represent getWriteByte.b4 using {
			datatype = sint8;
		};
		represent getWriteByte.b5 using {
			datatype = sint8;
		};
		represent getWriteByte.b6 using {
			datatype = sint8;
		};
		represent getWriteByte.b7 using {
			datatype = sint8;
		};
		represent getWriteByte.bitArray using {
			datatype = uint16;
		};
		represent getWriteByte return using {
			datatype = uint16;
		};
	}
	representation Impl_32bit {
		represent getWriteByte.b0 using {
			datatype = sint8;
		};
		represent getWriteByte.b1 using {
			datatype = sint8;
		};
		represent getWriteByte.b2 using {
			datatype = sint8;
		};
		represent getWriteByte.b3 using {
			datatype = sint8;
		};
		represent getWriteByte.b4 using {
			datatype = sint8;
		};
		represent getWriteByte.b5 using {
			datatype = sint8;
		};
		represent getWriteByte.b6 using {
			datatype = sint8;
		};
		represent getWriteByte.b7 using {
			datatype = sint8;
		};
		represent getWriteByte.bitArray using {
			datatype = uint32;
		};
		represent getWriteByte return using {
			datatype = uint32;
		};
	}
	representation Impl_8bit {
		represent getWriteByte.b0 using {
			datatype = sint8;
		};
		represent getWriteByte.b1 using {
			datatype = sint8;
		};
		represent getWriteByte.b2 using {
			datatype = sint8;
		};
		represent getWriteByte.b3 using {
			datatype = sint8;
		};
		represent getWriteByte.b4 using {
			datatype = sint8;
		};
		represent getWriteByte.b5 using {
			datatype = sint8;
		};
		represent getWriteByte.b6 using {
			datatype = sint8;
		};
		represent getWriteByte.b7 using {
			datatype = sint8;
		};
		represent getWriteByte.bitArray using {
			datatype = uint8;
		};
		represent getWriteByte return using {
			datatype = uint8;
		};
	}

}