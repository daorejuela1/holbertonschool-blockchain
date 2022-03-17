#include "blockchain.h"


/**
 * hash_matches_difficulty - determines if hash matches difficulty
 * @hash: hash buffer
 * @difficulty: difficulty to match
 * Return: 1 if matches else 0
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
		uint32_t difficulty)
{
	uint8_t *ptr = (uint8_t *)hash;
	uint32_t difficulty_match = 0;
	int i;

	if (!hash)
		return (0);
	while (ptr < hash + SHA256_DIGEST_LENGTH)
	{
		for (i = 7; i >= 0; i--)
		{
			if ((*ptr >> i) & 1)
				return (difficulty_match == difficulty);
			difficulty_match++;
		}
		ptr++;
	}
	return (difficulty_match == difficulty);
}
