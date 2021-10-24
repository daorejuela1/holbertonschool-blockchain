/*
 * ============================================================================
 *
 *       Filename:  ec_to_pub.c
 *
 *    Description: extracts the public key from an EC_KEY opaque structure
 *
 *        Version:  1.0
 *        Created:  10/24/2021 03:23:19 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Orejuela
 *   Organization: Holberton
 *
 * ===========================================================================
 */
#include "hblk_crypto.h"
/**
 * ec_to_pub - extracts the public key from an EC structure
 * @key: pointer to the EC_KEY structure
 * @pub:  address at which to store the extracted public key
 *
 * Return: public key from an EC_KEY
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_GROUP *ec_group = NULL;
	const EC_POINT *ec_point = NULL;

	if (!key || !pub)
		return (NULL);
	ec_point = EC_KEY_get0_public_key(key);
	ec_group = EC_KEY_get0_group(key);
	if (!ec_group || !ec_point)
		return (NULL);
	if (!EC_POINT_point2oct(ec_group, ec_point, POINT_CONVERSION_UNCOMPRESSED,
				pub, EC_PUB_LEN, NULL))
		return (NULL);
	return (pub);
}
