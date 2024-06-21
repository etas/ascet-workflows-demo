package SystemLib.Bitoperations;

/**
 * xor returns the binary exclusive OR conjunction of the two arguments.
 */
 @c_code
stateless class xor
using Impl_16bit {
	/**
	 * The result of the binary exclusive OR conjunction of bitArray1 and bitArray2 is returned.
	 */
	public UnsignedInteger getXor(UnsignedInteger in bitArray1, UnsignedInteger in bitArray2);

	representation Impl_16bit {
		represent getXor.bitArray1 using {
			datatype = uint16;
		};
		represent getXor.bitArray2 using {
			datatype = uint16;
		};
		represent getXor return using {
			datatype = uint16;
		};
	}
	representation Impl_32bit {
		represent getXor.bitArray1 using {
			datatype = uint32;
		};
		represent getXor.bitArray2 using {
			datatype = uint32;
		};
		represent getXor return using {
			datatype = uint32;
		};
	}
	representation Impl_8bit {
		represent getXor.bitArray1 using {
			datatype = uint8;
		};
		represent getXor.bitArray2 using {
			datatype = uint8;
		};
		represent getXor return using {
			datatype = uint8;
		};
	}

}