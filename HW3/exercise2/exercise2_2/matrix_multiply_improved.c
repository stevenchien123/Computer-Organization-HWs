void matrix_multiply(int *a, int *b, int *output, int i,
                           int k, int j) {
    // Inplement your code here
     for (int x = 0; x < i; x+=4) {
        for (int y = 0; y < j; y+=4) {
            for (int z = 0; z < k; z+=4) {
                // sum += a[x * k + z] * b[z * j + y];
		for(int xx = x; xx < x+4; xx++) {
		    for(int yy = y; yy < y+4; yy++) {
		    	for(int zz = z; zz < z+4; zz++) {
			    output[xx * j + yy] += a[xx * k + zz] * b[zz * j + yy];
			}
		    }
		}
            }
            // output[x * j + y] = sum;
        }
    }
    return;
}
