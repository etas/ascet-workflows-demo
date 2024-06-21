if(aBool)
	return (bitArray | (((uint32) 1) << position));
else
	return (bitArray & ~((uint32)1<<position));

