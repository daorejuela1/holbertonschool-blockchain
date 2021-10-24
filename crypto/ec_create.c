/*
 * =========================================================================
 *
 *       Filename:  ec_create.c
 *
 *    Description: creates a new EC key pair usin secp256k1 .
 *
 *        Version:  1.0
 *        Created:  10/24/2021 01:59:08 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: David Orejuela
 *   Organization: Holberton
 *
 * =========================================================================
 */
#include "hblk_crypto.h"
/**
 * ec_create - creates a new ec key part
 *
 * Return: return a pointer to an EC_KEY structure,
 * containing both the public and private keys, or NULL upon failure
 */
EC_KEY *ec_create(void)
{
	EC_KEY *key_pair;

	key_pair = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key_pair)
		return (NULL);
	if (!EC_KEY_generate_key(key_pair))
	{
		EC_KEY_free(key_pair);
		return (NULL);
	}
	return (key_pair);
}
