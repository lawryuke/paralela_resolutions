# Lab 02: Algorithm Performance and Cache Memory Evaluation

## eequirements
- GCC (g++)
- Python 3 (with Matplotlib and NumPy)
- Valgrind and KCachegrind

## 1. nested loops experiment
Compile and run:
```bash
g++ a.cpp -o a
./a
```

## 2. matrix multiplication (classic vs blocked)
Compile and run:
```bash
g++ b.cpp -o b
./b
```
## 3. generate graphs
```bash
python gra.py
```
*(the `.png` images will be created in the same directory)*

## 4. Valgrind and KCachegrind analysis
oo evaluate cache behavior without compiler interference:
```bash
g++ -g -O3 -fno-inline cache_test.cpp -o cache_test
valgrind --tool=cachegrind --cache-sim=yes ./cache_test
```
oo visualize the results:
```bash
kcachegrind cachegrind.out.XXXX
```
