/*
 * =======================================================================
 *
 *       Filename:  memutils.c
 *
 *    Description:  Mem utils to handle memory
 *
 *        Version:  1.0
 *        Created:  04/25/2022 02:25:36 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Orejuela 
 *   Organization:  Holberton School
 *
 * =======================================================================
 */
#include "utils.h"


/**
 * realloc_array - reallocates an array
 * @arr: pointer to array
 * @arr_size: pointer to array size
 * Return: pointer to reallocated array
 **/
void *realloc_array(void *arr, size_t *arr_size)
{
	*arr_size += (3 * sizeof(char *));
	return (realloc(arr, *arr_size));
}
