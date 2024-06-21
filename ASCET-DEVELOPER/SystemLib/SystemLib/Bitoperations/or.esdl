package SystemLib.Bitoperations;

/**
 * or returns the binary OR conjunction of the two arguments.
 */

@c_code
stateless class or
using Impl_16bit {
	/**
	 * The result of the binary OR conjunction of bitArray1 and bitArray2 is returned.
	 */
	public UnsignedInteger getOr(UnsignedInteger in bitArray1, UnsignedInteger in bitArray2);

	representation Impl_16bit {
		represent getOr.bitArray1 using {
			datatype = uint16;
		};
		represent getOr.bitArray2 using {
			datatype = uint16;
		};
		represent getOr return using {
			datatype = uint16;
		};
	}
	representation Impl_32bit {
		represent getOr.bitArray1 using {
			datatype = uint32;
		};
		represent getOr.bitArray2 using {
			datatype = uint32;
		};
		represent getOr return using {
			datatype = uint32;
		};
	}
	representation Impl_8bit {
		represent getOr.bitArray1 using {
			datatype = uint8;
		};
		represent getOr.bitArray2 using {
			datatype = uint8;
		};
		represent getOr return using {
			datatype = uint8;
		};
	}

}