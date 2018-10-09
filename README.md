# suffix_array

These two algorithms can construct [**suffix array**](https://en.wikipedia.org/wiki/Suffix_array) in O(n) time.
- DC3
- SA-IS
  

## DC3

![](http://www.cs.cmu.edu/afs/cs/user/chaominy/www/418_project/skew.png)

## SA-IS

![](https://upload.wikimedia.org/wikipedia/de/2/25/Sais-bsp.gif)
![](https://ieeexplore.ieee.org/mediastore_new/IEEE/content/media/12/6008534/5582081/5582081-fig-1-source-small.gif)
---

## How to build
**prerequisite**
[google test](https://github.com/google/googletest)  

```bash
git clone https://github.com/weisystak/suffix_array.git
cd suffix_array
mkdir build && cd build
cmake ..
make
./DC3_test
```
