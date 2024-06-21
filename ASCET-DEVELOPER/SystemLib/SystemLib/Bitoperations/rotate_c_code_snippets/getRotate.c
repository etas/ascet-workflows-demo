return ((bitArray << k) |
		    (bitArray & ~(((uint32) 1 << (32-k)) -1))>>(32-k));
