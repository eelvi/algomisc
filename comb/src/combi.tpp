/*
Combinations algorithm.
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
	    
template <class element_t>
combinations<element_t>::combinations(const std::vector<element_t>& evec, int choose)
{
	if (evec.size()<choose)
	    throw -7;
	m_evec_ptr = &evec;
	m_evec_data = evec.data();
	if (!m_evec_data)
	    throw -6;
	
	m_choose = choose;
	m_tuple = unique_ptr<element_t[]>(new element_t[m_choose]);
	m_counttable = unique_ptr<int[]>(new int[m_choose]);
	m_cstate = {};
	m_cstate_size=evec.size();
	m_done=false;
	init_state();
}



//algorithm
template <class element_t>
const element_t* combinations<element_t>::next_combination()
{
	if (m_done)
	    return nullptr;

	if (!m_comb_count){ //first permutation
	    m_comb_count++;
	    if (m_cstate_size==m_choose)
		m_done=true;
	    return m_tuple.get();
	}
	//algorithm
	int fua = -1; //index of first unmasked element, -1 means not found
	
	//next loop needs optimization maybe
	for (int i=0; i<m_cstate_size; i++){
	    if (!m_cstate[i]){
		continue;
	    }
	    else if (i+((m_choose-1)-m_count_idx)<m_cstate_size){ //magic condition :)
		fua = i;
		while (m_depth){ //usually doesn't get executed
		    m_cstate[fua]=false; 
		    m_counttable[m_count_idx++]=fua++;
		    m_depth--;
		}

		break;
	    }
	}

	if (fua<0){ // no unmasked element found
	    m_count_idx--; //focus on previous (higher) counting idx
	    for (int i=m_counttable[m_count_idx]+1; i<m_cstate_size; i++){
		m_cstate[i]=true; //unmask all elements after current focus
	    }
	    m_depth++;
	    next_combination(); 
	    m_comb_count--;
	}
	else {
	    if (fua>0){ 
		m_cstate[fua]=false;
		m_counttable[m_count_idx]=fua;
	    }
	}
	
	
	//end condition
	if (m_count_idx==m_choose-1){
	    if(m_counttable[0]==m_cstate_size-m_choose)
		if (m_counttable[m_choose-1]==m_cstate_size-1)
		    m_done=true;
	}
		
	m_comb_count++; 
	update_tuple(); //updates it according to new counttable values
	return m_tuple.get();	
}





template <class element_t>
void combinations<element_t>::init_state()
{
    m_cstate.insert(m_cstate.end(), m_cstate_size, true);

    for (int i=0; i<m_choose; i++){
	m_counttable[i]=i;
	m_cstate[i]=false;
    }
    m_count_idx = m_choose-1;
    m_depth = 0;
    m_comb_count =0;
    update_tuple(); 
}

template <class element_t>
bool combinations<element_t>::has_next()
{
    return !m_done;
}

template <class element_t>
int combinations<element_t>::get_count()
{
    return m_comb_count;
}

template <class element_t>
void combinations<element_t>::update_tuple()
{
    
	    #if 1==0 //dbg
	    for (int i=0; i<m_cstate_size; i++)
	    { std::cout << (m_cstate[i]?"t":"f"); }
	    std::cout << std::endl;
	    #endif
    
    for (int idx=0; idx<m_choose; idx++){
    m_tuple[idx]=m_evec_data[m_counttable[idx]]; //copies elements 
    }
}

template <class element_t>
combinations<element_t>::~combinations()
{

}


