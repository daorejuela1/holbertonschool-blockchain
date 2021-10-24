/*
 * ===========================================================================
 *
 *       Filename:  ec_from_pub.c
 *
 *    Description:  Creates an EC structure from a public key
 *
 *        Version:  1.0
 *        Created:  10/24/2021 04:26:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Orejuela
 *   Organization:  Holberton
 *
 * ==========================================================================
 */

#include "hblk_crypto.h"
/**
 * ec_from_pub - creates an EC structure from a pub key
 * @pub:  contains the public key to be converted
 *
 * Return: pointer to the created EC_KEY structure upon success,
 * or NULL upon failure
 */
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *ec_struct = NULL;
	EC_POINT *ec_point = NULL;
	const EC_GROUP *ec_group;

	if (!pub)
		return (NULL);
	ec_struct = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!ec_struct)
		return (NULL);
	ec_group = EC_KEY_get0_group(ec_struct);
	ec_point = EC_POINT_new(ec_group);
	if (!ec_point || !ec_group)
	{
		EC_KEY_free(ec_struct);
		return (NULL);
	}
	if (!EC_POINT_oct2point(ec_group, ec_point, pub, EC_PUB_LEN, NULL)
			|| !EC_KEY_set_public_key(ec_struct, ec_point))
	{
		EC_KEY_free(ec_struct);
		EC_POINT_free(ec_point);
		return (NULL);
	}
	EC_POINT_free(ec_point);
	return (ec_struct);
}
