	// set the eight low significant bits of bitArray
	bitArray = bitArray & ~((uint32) 255);
	if (b7) bitArray = bitArray | (uint32) 128;
	if (b6) bitArray = bitArray | (uint32) 64;
	if (b5) bitArray = bitArray | (uint32) 32;
	if (b4) bitArray = bitArray | (uint32) 16;
	if (b3) bitArray = bitArray | (uint32) 8;
	if (b2) bitArray = bitArray | (uint32) 4;
	if (b1) bitArray = bitArray | (uint32) 2;
	if (b0) bitArray = bitArray | (uint32) 1;
	return bitArray;
