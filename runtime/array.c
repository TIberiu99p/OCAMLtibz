/*
 * Example compiler
 * Copyright (C) 2015-2016 Scott Owens
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Allocation of multi-dimensional arrays of 64-bit ints. For an array of
 * length n, store the length of the array in element 0, and the array in 1 to
 * n inclusive. */

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

/* Since the first element of an array will have a different type than the
 * rest, and the last dimension's array will have numbers rather than pointers.
 * (A "flexible array member", available since C99, would be another, nicer way
 * of doing this.) */
union elt {
  uint64_t num;
  union elt *ptr;
};

/* Our compiler will assume that the integers and pointers in the array are
 * both exactly 64 bits in size. So let's check that our C compiler shares
 * the same understanding of this data structure. */
_Static_assert (sizeof (uint64_t)  == sizeof (uintptr_t), "uint64_t is uintptr_t");
_Static_assert (sizeof (uint64_t)  == 8, "uint64_t is exactly 64 bits in size");
_Static_assert (sizeof (union elt) == 8, "union fits in 64 bits");

typedef union elt elt;

#define S sizeof(elt)

/* A 1 dimensional array */
elt* allocate1(int64_t dim1) {
  elt* x = malloc(S*(dim1+1));
  for (unsigned long i = 0; i < dim1; i++)
    x[i+1].num = 0;
  x[0].num = dim1;
  return x;
}

/* A 2 dimensional array is an array of arrays */
elt* allocate2(int64_t dim1, int64_t dim2) {
  elt* x = malloc(S*(dim1+1));
  for (unsigned long i = 0; i < dim1; i++) {
    elt* y = malloc(S*(dim2+1));
    x[i+1].ptr = y;
    for (int64_t j = 0; j < dim2; j++)
      y[j+1].num = 0;
    y[0].num = dim2;
  }
  x[0].num = dim1;
  return x;
}

/* Allocate dimensions dim to num_dim where the length of each dimension is
 * given by the list dims[] */
elt* allocate_n_help(int64_t dim, int64_t num_dim, int64_t *dims) {
  if (dim == num_dim - 1)
    return allocate1(dims[dim]);
  else {
    elt* x = malloc(S*(dims[dim]+1));
    for (unsigned long i = 0; i < dims[dim]; i++) {
      x[i+1].ptr = allocate_n_help(dim+1, num_dim, dims);
    }
    x[0].num = dims[dim];
    return x;
  }
}

elt* allocate_n(int64_t num_dim, int64_t *dims) {
  return allocate_n_help(0, num_dim, dims);
}

elt* allocate3(int64_t dim1, int64_t dim2, int64_t dim3) {
  int64_t dims[] = {dim1, dim2, dim3};
  return allocate_n(3, dims);
}

elt* allocate4(int64_t dim1, int64_t dim2, int64_t dim3, int64_t dim4) {
  int64_t dims[] = {dim1, dim2, dim3, dim4};
  return allocate_n(4, dims);
}

elt* allocate5(int64_t dim1, int64_t dim2, int64_t dim3, int64_t dim4, int64_t dim5) {
  int64_t dims[] = {dim1, dim2, dim3, dim4, dim5};
  return allocate_n(5, dims);
}

elt* allocate6(int64_t dim1, int64_t dim2, int64_t dim3, int64_t dim4, int64_t dim5, int64_t dim6) {
  int64_t dims[] = {dim1, dim2, dim3, dim4, dim5, dim6};
  return allocate_n(6, dims);
}

elt* allocate7(int64_t dim1, int64_t dim2, int64_t dim3, int64_t dim4, int64_t dim5, int64_t dim6, int64_t dim7) {
  int64_t dims[] = {dim1, dim2, dim3, dim4, dim5, dim6, dim7};
  return allocate_n(7, dims);
}
