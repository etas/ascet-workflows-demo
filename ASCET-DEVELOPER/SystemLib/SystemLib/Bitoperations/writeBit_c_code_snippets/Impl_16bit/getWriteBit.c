if(aBool)
	return (bitArray | (((uint16) 1) << position));
else
	return (bitArray & ~((uint16)1<<position));

