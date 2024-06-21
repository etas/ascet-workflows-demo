	// set the eight low significant bits of bitArray
	bitArray = bitArray & ~((uint8) 255);
	if (b7) bitArray = bitArray | (uint8) 128;
	if (b6) bitArray = bitArray | (uint8) 64;
	if (b5) bitArray = bitArray | (uint8) 32;
	if (b4) bitArray = bitArray | (uint8) 16;
	if (b3) bitArray = bitArray | (uint8) 8;
	if (b2) bitArray = bitArray | (uint8) 4;
	if (b1) bitArray = bitArray | (uint8) 2;
	if (b0) bitArray = bitArray | (uint8) 1;
	return bitArray;

