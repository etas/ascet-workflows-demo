	// set the eight low significant bits of bitArray
	bitArray = bitArray & ~((uint16) 255);
	if (b7) bitArray = bitArray | (uint16) 128;
	if (b6) bitArray = bitArray | (uint16) 64;
	if (b5) bitArray = bitArray | (uint16) 32;
	if (b4) bitArray = bitArray | (uint16) 16;
	if (b3) bitArray = bitArray | (uint16) 8;
	if (b2) bitArray = bitArray | (uint16) 4;
	if (b1) bitArray = bitArray | (uint16) 2;
	if (b0) bitArray = bitArray | (uint16) 1;
	return bitArray;
