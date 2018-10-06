# suffix_array

These two algorithms can construct [**suffix array**](https://en.wikipedia.org/wiki/Suffix_array) in O(n) time.
- DC3
- SA-IS
  

## DC3

![](http://www.cs.cmu.edu/afs/cs/user/chaominy/www/418_project/skew.png)

## SA-IS

![](https://upload.wikimedia.org/wikipedia/de/2/25/Sais-bsp.gif)

---
## How to build

```bash
git clone git@github.com:weisystak/suffix_array.git
cd suffix_array
mkdir build && cd build
cmake ..
make
./DC3_test
```