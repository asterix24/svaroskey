#include "keyhash.h"

struct KeyHash {
	uint32_t buckets[NUM_KEYHASH_BUCKETS];
};

typedef struct
{
	uint8_t bucket;
	uint8_t slot;
} BucketMappingResult;

static KeyHash _key_hash;

KeyHash* fetch_key_hash() {
    return &_key_hash;
}

void clear_key_hash(KeyHash* kh)
{
	size_t i = 0;
	for (i = 0; i < NUM_KEYHASH_BUCKETS; i++)
	{
		kh->buckets[i] = 0;
	}
}

static BucketMappingResult map_key_id(key_id_t k_id)
{
	/* Suppose we need to map the 74th key. k_id is 73 because ids are
	 * 0-based indexes.
	 * The relevant location in the key hash is the 3rd bucket, 10th bit.
	 * As a visual aid, a visualization of the 4 buffers follows.
	 *
	 * 0           bucket 0          31 32          bucket 1          63
	 * v                              v v                              v
	 * ................................ ................................
	 * .........x...................... ................................
	 * ^                              ^ ^                              ^
	 * 64          bucket 2          95 96          bucket 3         127
	 *
	 * The `x` in the above visualization represents the bit for the key
	 * with id 73
	 *
	 * It's easy to see that for ids in the range 0..31 a division by 32,
	 * which gets truncated due to how integer division works in c, will
	 * yield a result of 0, which is the index for the bucket that contains
	 * the bit for that id.
	 *
	 * The bit itself is the offset starting from the first element of the
	 * bucket in which the bit itself is found. Mathematically, that's the
	 * modulo operation.
	 *
	 * Returning to our example for id 73 we have that the bit is in bucket
	 * with index (73 / 32) = 2, and the bit itself is in position
	 * 73 % 32 = 9.
	 */
	uint8_t bucket = k_id / 32;
	uint8_t slot = k_id % 32;
	return (BucketMappingResult){ bucket, slot };
}

void set_pressed(KeyHash* kh, key_id_t k_id)
{
	BucketMappingResult r = map_key_id(k_id);
	kh->buckets[r.bucket] |= (1 << r.slot);
}

void set_released(KeyHash* kh, key_id_t k_id)
{
	BucketMappingResult r = map_key_id(k_id);
	kh->buckets[r.bucket] &= ~(1 << r.slot);
}

bool is_pressed(KeyHash* kh, key_id_t k_id)
{
	BucketMappingResult r = map_key_id(k_id);
	return (kh->buckets[r.bucket] >> r.slot) == 1;
}
