/*
Combinations algorithm
    Copyright (C) 2017  eelvi

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef COMBI_H
#define COMBI_H

#include <iostream>
#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;


template <class element_t>
class combinations{
public:
    combinations(const std::vector<element_t>& evec, int choose);
	
    //whether there is a next combination, alternatively you can check the return value of next_combination()
    bool has_next();
    //how many combinations were generated up to the call
    int get_count();
    
    //generates a combinations, updates the tuple and returns a pointer to it, the size of the tuple is r (choose) 
    	//it will return null once all combinations were generated
    const element_t* next_combination();

    ~combinations();

private:

    //internal, initialization
    void init_state();
    //internal function to update the output tuple
    void update_tuple();

    //n: number of elements in set, r: chosen elements
    const std::vector<element_t>* m_evec_ptr=nullptr;
    const element_t* m_evec_data=nullptr;
    unique_ptr<element_t[]> m_tuple;  //current choice tuple
    vector<bool> m_cstate; // an array of bools as many as n (number of elements in the input set)
    unique_ptr<int[]> m_counttable; // an array of ints as many as r (choose)
    int m_cstate_size; //n (number of elements in the input set)
    int m_choose; // r (choose)
    int m_count_idx; //kept to keep track of currently focused on element in counttable
    bool m_done; //signaling that we exhausted all combinations
    // when it is zero we have a ready result, otherwise more processing is needed by recursively calling next_combination()
    int m_depth; 
    //keeping count of how many we done (not needed for the algorithm's operation)
    int m_comb_count; 

};

//implementation
#include "combi.tpp"

#endif
