#include <cstdint>
#include <cstdio>
#include <cmath>
#include <inttypes.h>


const uint64_t MAX_N = 1 * 1000 * 1000 * 1000ULL;
const uint64_t MAX_N_SQRT = sqrt(MAX_N);

typedef int64_t index_t;

class HashTable
{
public:
	HashTable(size_t n)
	: size(1 << (uint64_t)ceil(log2(n))),
	 mask(size - 1),
	 keys(new uint64_t[size]),
	 values(new uint64_t[size])
	{}

	~HashTable() {
		delete[] keys;
		delete[] values;
	}

	void insert(uint64_t k, uint64_t v) {
		size_t i = k & mask;
		while (keys[i]) {
			i = (i + 1) & mask;
		}
		keys[i] = k;
		values[i] = v;
	}

	index_t search(uint64_t k) const {
		size_t i = k & mask;
		while (keys[i]) {
			if (keys[i] == k)
				return i;
			else
				i = (i + 1) & mask;
		}
		return -1;
	}

	void remove(index_t i) {
		keys[i] = 0;

		for (i = (i + 1) & mask; keys[i]; i = (i + 1) & mask) {
			const uint64_t key = keys[i];
			keys[i] = 0;
			insert(key, values[i]);
		}
	}

	uint64_t get_value(index_t pos) const {
		return values[pos];
	}

private:
	const size_t size, mask;
	uint64_t *keys, *values;
};

void FindPrimes()
{
	HashTable ht(MAX_N_SQRT);

	printf("2 ");

	for (uint64_t n = 3; n < MAX_N; n += 2) {
		const index_t pos = ht.search(n);
		if (pos >= 0) {
			const uint64_t p = ht.get_value(pos);
			ht.remove(pos);
			uint64_t v = n + p + p;
			for (; ht.search(v) >= 0; v += p + p);
			ht.insert(v, p);
		} else {
			if (n <= MAX_N_SQRT) {
				ht.insert(n * n, n);
			}
			printf("%" PRIu64 " " , n);
		}
	}
}

int main()
{
	FindPrimes();
	return 0;
}
