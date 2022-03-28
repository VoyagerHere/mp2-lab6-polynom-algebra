#include "hash_table_list.h"
#include "eq_exception.h"
#include "list.h"
#include "table_string.h"


unsigned int HashTableList::Hash(const std::string& key)
{
    unsigned long hashval = 0;
    int len = key.length();
    for (int i = 0; i < len; i++) {
        hashval = (hashval << 3) + key[3];
    }
    return hashval;
}

TableString* HashTableList::find_str(const std::string& key)
{
    int index = Hash(key);
    for(ListIterator<TableString*> it = table[index]->begin();
        it != table[index]->end(); ++it)
    {
        if((*it)->key == key) {
            curr_pos = it;
            return (*it);
        }
    }
    return nullptr;
}

void HashTableList::insert(const TableString& data)
{
    if(is_full()) {
        throw EqException(error_code::k_OUT_OF_MEMORY);
    }
    else {
        int index = Hash(data.key);
        TableString* tmp = new TableString(data);
        ListIterator<TableString*> it =  table[index]->begin();
        table[index]->insert(it, tmp);
        data_cnt++;
    }
}


void HashTableList::erase(const std::string& key)
{
    int index = Hash(key);

    if((*this).find_str(key) == nullptr) {
        throw(EqException(error_code::k_NOT_FOUND));
    }
    else {
        table[index]->erase(curr_pos);
    }
    
    throw EqException(error_code::k_NOT_FOUND);

}

bool HashTableList::is_full() const
{
    try {
        TableString* pNode = new TableString();
    }
    catch(std::bad_alloc& e) {
        return 1;
    }
    
    return 0;
}

bool  HashTableList::is_tab_ended() const
{
    return curr_index >= size;

}

bool HashTableList::reset()
{
    curr_pos = table[0]->begin();
    curr_index = 0;
    return is_tab_ended();
}

bool HashTableList::go_next()
{
    if(is_tab_ended()) {
        return false;
    }

    if(curr_pos != table[curr_index]->end()) {
        ++curr_pos;
    }
    else {
        curr_index++;
        curr_pos = table[curr_index]->begin();
    }
    return true;
}




void HashTableList::print()
{
    operator<<(std::cout, *this);
}


TableString*  HashTableList::get_value()
{
    return (*curr_pos);
}