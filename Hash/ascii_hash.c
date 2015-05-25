#include<stdio.h>
typedef unsigned int Index;

Index hash1(const char *key, int TableSize)
{
	unsigned int hash_val = 0;
	while (*key != '\0')
		hash_val += *key++;

	return hash_val % TableSize;
}

Index hash2(const char *key, int TableSize)
{
	return (key[0] + 27 * key[1] + 729 * key[2]) % TableSize;
}

Index hash3(const char *key, int TableSize)
{
	unsigned int hash_val = 0;
	while (*key != '\0')
		hash_val = (hash_val << 5) + *key;

	return hash_val % TableSize;
}
