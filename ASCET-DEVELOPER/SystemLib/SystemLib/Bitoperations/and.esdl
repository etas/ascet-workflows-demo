package SystemLib.Bitoperations;

type UnsignedInteger is integer 0 ..;

/**
 * and returns the binary AND conjunction of the two arguments.
 */

@c_code
stateless class and
using Impl_16bit {
	/**
	 * The result of the binary AND conjunction of bitArray1 and bitArray2 is returned.
 	 */
	public UnsignedInteger getAnd(UnsignedInteger in bitArray1, UnsignedInteger in bitArray2);

	representation Impl_16bit {
		represent getAnd.bitArray1 using {
			datatype = uint16;
		};
		represent getAnd.bitArray2 using {
			datatype = uint16;
		};
		represent getAnd return using {
			datatype = uint16;
		};
	}
	representation Impl_32bit {
		represent getAnd.bitArray1 using {
			datatype = uint32;
		};
		represent getAnd.bitArray2 using {
			datatype = uint32;
		};
		represent getAnd return using {
			datatype = uint32;
		};
	}
	representation Impl_8bit {
		represent getAnd.bitArray1 using {
			datatype = uint8;
		};
		represent getAnd.bitArray2 using {
			datatype = uint8;
		};
		represent getAnd return using {
			datatype = uint8;
		};
	}
}