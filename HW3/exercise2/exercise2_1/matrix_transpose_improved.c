void matrix_transpose(int n, int *dst, int *src) {
    // Inplement your code here
        for (int x = 0; x < n; x+=8) {
            for (int y = 0; y < n; y+=8) {
		// dst[y + x * n] = src[x + y * n];
		for(int i = x; i < x+8; i++) {
		    for(int j = y; j < y+8; j++) {
		        dst[j + i * n] = src[i + j * n];
		    }
		}
	    }
	}
    }
