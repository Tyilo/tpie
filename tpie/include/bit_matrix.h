// Copyright (c) 1994 Darren Vengroff
//
// File: bit_matrix.h
// Author: Darren Vengroff <darrenv@eecs.umich.edu>
// Created: 11/4/94
//
// $Id: bit_matrix.h,v 1.6 1999-02-03 17:41:31 tavi Exp $
//
#ifndef _BIT_MATRIX_H
#define _BIT_MATRIX_H

#include <bit.h>
#include <matrix.h>

#include <sys/types.h>


// typedef matrix<bit> bit_matrix_0;

class bit_matrix : public matrix<bit> {
private:
    bit_matrix::bit_matrix(matrix<bit> &mb);
public:
    bit_matrix(unsigned int rows, unsigned int cols);
    virtual ~bit_matrix(void);

    bit_matrix operator=(const bit_matrix &rhs);
    
    // We can assign from an offset, which is typically a source
    // address for a BMMC permutation.
    bit_matrix &operator=(const off_t &rhs);

    operator off_t(void);

    friend bit_matrix operator+(bit_matrix &op1, bit_matrix &op2);
    friend bit_matrix operator*(bit_matrix &op1, bit_matrix &op2);
};

bit_matrix operator+(bit_matrix &op1, bit_matrix &op2);
bit_matrix operator*(bit_matrix &op1, bit_matrix &op2);

ostream &operator<<(ostream &s, bit_matrix &bm);

#endif // _BIT_MATRIX_H 
