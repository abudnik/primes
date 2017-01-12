## 1. Algorithms for finding prime numbers
Most commonly used method of finding all primes up to a given limit is called a prime number sieve.
Sieve of Eratosthenes, sieve of Sundaram, sieve of Atkin and Pritchard's wheel sieve are notable examples of prime number sieves.
The sieve of Eratosthenes has `O(n log log n)` time and `O(n)` bit space complexity. Segmented version of sieve of Eratosthenes has `O(n log log n)` time complexity and `O(sqrt n)` bit space complexity.
Relatively simple and elegant approach of finding primes in `O(n)` time and space complexity described in [2].

Another method of finding all prime numbers in the range is applying a primality test for every number in this range. Trial division test gives algorithm with `O(n sqrt n)` time and `O(1)` space complexity. Various sophisticated primality tests [4] lower time complexity to `O(n (log n)^c)`, where `c > 1`.

## 2. Algorithm description
An algorithm, presented in this article, is a memory-optimized version of the sieve of Eratosthenes. Algorithm goes through a sequence of numbers between 2 and n. Let S denote a set of multiples of a previously found primes. If some number `p ∉ S`, then p is a prime and it is necessary to add `p * p` to the set S. Otherwise p is a composite number, multiple to some prime pb. In this case it is necessary to remove p from set S and to add smallest number `x = i * pb`, where `x > p` and `x ∉ S`.
Significant optimization is adding to set S only primes whose square is not greater than n.

Algorithm implementation in Python:

```python
def find_primes(n, n_sqrt):
    S = {}
    print(2)
    for i in range(3, n, 2): # for every odd number
        if i in S:   # i is not prime
            p = S[i] # i is multiple to prime p
            del S[i] # remove i from S
            v = i + p + p
            while v in S:
                v += p + p
            S[v] = p # add v multiple to prime p
        else:        # i is prime
            if i <= n_sqrt:
                S[i * i] = i
            print(i)
```

## 3. Proof of correctness
In number theory, the fundamental theorem of arithmetic, also called the unique-prime-factorization theorem, states that every integer greater than 1 either is prime itself or is the product of prime numbers, and that this product is unique, up to the order of the factors:
`n = p1^d1 * p2^d2 ... pk^dk`, where `p1 < p2 < ... < pk` - prime numbers, `d1..dk` - some natural numbers.
Let's show that at some stage the algorithm considers the number `n > 2` presented in set S if and only if n is a composite number: <br />
a) If n is a composite number, then relying on fundamental arithmetic theorem, it can be represented in the form `n = p * i`, where p - prime number, i - some natural number. If `i = p`, then `n = p * p`, which corresponds to the case where the square of prime number is added to the set S in a previous step of the algorithm. If `i != p`, then number `np = p * (i - 2)` was taken in a previous step of the algorithm as a composite number according to the main hypothesis. And as for any composite number, algorithm adds number `x = np + 2 * p` to the set S. But `x = p * (i - 2) + 2 * p = p * i = n`, resulting `n ∈ S`, if n is a composite number. <br />
b) If n is a prime number, then n has no positive divisors other than 1 and itself. Set S was initially empty and only composite numbers are added to it, thereby `n ∉ S`, if n is not a composite number.

## 4. Complexity analysis
For every prime p will be performed approximately `n/p` searches, insertions and deletions in the set S.
This is similar to the `O(n log log n)` time complexity of the sieve of Eratosthenes, requiring amortized `O(1)` time complexity for searches, insertions and deletions in the set S. Set S can be implemented as a hash table. <br />
Number of prime numbers below a given number is approximately `n/ln` [1]. As the algorithm adds only prime numbers not greater than `sqrt n`, then the cardinality of S is `O(sqrt n / ln n)`, that requires `O(sqrt n)` bits of memory.

## 5. Performance comparison of algorithm implementations for finding prime numbers

Execution time in seconds of a given algorithms for different N:

N | Sieve of Eratosthenes | Given algorithm | Segmented sieve of Eratosthenes
--- | --- | --- | ---
10 * 10 ^ 6 | 0.124 | 0.143 | 0.111
50 * 10 ^ 6 | 0.607 | 0.712 | 0.525
10 * 10 ^ 7 | 1.205 | 1.36 | 1.014
50 * 10 ^ 7 | 7.561 | 7.076 | 4.767
10 * 10 ^ 8 | 15.545 | 14.835 | 9.145
50 * 10 ^ 8 | - | 76.393 | 51.565
10 * 10 ^ 9 | - | 148.051 | 99.514

All three algorithms were implemented in C++ and compiled with GCC 4.8.4 on Ubuntu 14.04.
Machine specification: Intel(R) Xeon(R) CPU E5-2660 @ 2.20GHz; 128 Gb RAM.

## 6. Conclusion
A new algorithm for finding prime numbers up to a given limit with `O(n log log n)` time and `O(sqrt n)` bits space complexity was developed. The practical implementation of the algorithm is faster than the sieve of Eratosthenes, for large n, but slightly slower than segmented sieve of Eratosthenes. The proposed algorithm in this article can be considered as a simple and quite effective alternative to existing methods of finding prime numbers up to a given limit.

## References

[1] Knuth, D. The art of computer programming, vol 2 (3rd ed.): seminumerical algorithms <br />
[2] D. Gries and J. Misra, A linear sieve algorithm for finding prime numbers, Comm. ACM 21 (12) (1978) <br />
[3] P. Pritchard, Linear prime-number sieves: A family tree, Sci. Comp. Prog. 9 (1987) <br />
[4] Weisstein, Eric W. "Primality Test." From MathWorld--A Wolfram Web Resource. http://mathworld.wolfram.com/PrimalityTest.html <br />
[5] Jonathan P. Sorenson Two Compact Incremental Prime Sieves CoRR abs/1503.02592 (2015)
