if(aBool)
	return (bitArray | (((uint8) 1) << position));
else
	return (bitArray & ~((uint8) 1<<position));
