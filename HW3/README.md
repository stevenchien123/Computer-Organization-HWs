# **Computer Organization HW3**
## **25/05/19**
* Download HW3 file from firefox.

## **25/06/01**
```C=
// cachesim.cc
void cache_sim_t::init()
{
  if (sets == 0 || (sets & (sets-1)))
    help();
  if (linesz < 8 || (linesz & (linesz-1)))
    help();

  idx_shift = 0;
  for (size_t x = linesz; x>1; x >>= 1)
    idx_shift++;

  tags = new uint64_t[sets*ways]();

  // FIFO
  fifo_queues.resize(sets);
  for(size_t i=0; i<sets; i++){
    for(size_t j=0; j<ways; j++){
      fifo_queues[i].push(j);
    }
  }

uint64_t cache_sim_t::victimize(uint64_t addr)
{
  size_t idx = (addr >> idx_shift) & (sets-1);
  
  // FIFO
  size_t way = fifo_queues[idx].front();
  uint64_t victim = tags[idx*ways + way];
  
  fifo_queues[idx].pop();
  fifo_queues[idx].push(way);
  
  tags[idx*ways + way] = (addr >> idx_shift) | VALID;
  return victim;
}

uint64_t fa_cache_sim_t::victimize(uint64_t addr)
{
  uint64_t old_tag = 0;
  if (tags.size() == ways)
  {
    auto it = tags.begin();

    // FIFO
    size_t way = fifo_queues[0].front();

    std::advance(it, way);
    old_tag = it->second;
    tags.erase(it);

    fifo_queues[0].pop();
    fifo_queues[0].push(way);
  }
  tags[addr >> idx_shift] = (addr >> idx_shift) | VALID;
  return old_tag;
}
```
```C=
// cachesim.h
class cache_sim_t
{
  public:
  // ...

  protected:
  // FIFO
  std::vector<std::queue<size_t>> fifo_queues;
}
```
* Implement FIFO Replacement Policy.
* Design Philosophy:
    * Default replacement order is 0 -> 1 -> 2 -> 3 -> 0 -> ...
    * Implemented with a queue.

```C=
// exercise2_1
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
```
```C=
// exercise2_2
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
```
* Using Loop Tiling technique.
