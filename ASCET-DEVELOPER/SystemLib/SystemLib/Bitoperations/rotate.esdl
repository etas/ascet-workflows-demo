package SystemLib.Bitoperations;

/**
 * rotate rotates the bits of the argument to the left by the specified number of positions.
 */

@c_code
stateless class rotate
using Impl_16bit {
	/**
	 * The result of the left-rotation of bitArray1 by k positions is returned.
	 */
	public UnsignedInteger getRotate(UnsignedInteger in bitArray, UnsignedInteger in k);

	representation Impl_16bit {
		represent getRotate.bitArray using {
			datatype = uint16;
		};
		represent getRotate.k using {
			datatype = uint8;
		};
		represent getRotate return using {
			datatype = uint16;
		};
	}
	representation Impl_32bit {
		represent getRotate.bitArray using {
			datatype = uint32;
		};
		represent getRotate.k using {
			datatype = uint8;
		};
		represent getRotate return using {
			datatype = uint32;
		};
	}
	representation Impl_8bit {
		represent getRotate.bitArray using {
			datatype = uint8;
		};
		represent getRotate.k using {
			datatype = uint8;
		};
		represent getRotate return using {
			datatype = uint8;
		};
	}

}