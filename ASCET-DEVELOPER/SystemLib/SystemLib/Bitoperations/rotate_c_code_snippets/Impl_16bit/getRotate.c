return ((bitArray << k) |
		    (bitArray & ~(((uint16) 1 << (16-k)) -1))>>(16-k));
