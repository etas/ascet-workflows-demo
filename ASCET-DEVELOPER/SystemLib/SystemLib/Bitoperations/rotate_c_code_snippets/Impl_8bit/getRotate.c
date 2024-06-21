return ((bitArray << k) |
		    (bitArray & ~(((uint8) 1 << (8-k)) -1))>>(8-k));
