#include "array_table.h"
#include "eq_exception.h"
#include "table.h"
#include "table_string.h"

bool ArrayTable::set_current_pos(int pos)
{
   curr_pos = ((pos > -1) && (pos < data_cnt)) ? pos : 0;
   return is_tab_ended(); 
}

bool ArrayTable::is_tab_ended() const
{
    return curr_pos >= data_cnt;
}

bool ArrayTable::reset()
{
    curr_pos = 0;
    return is_tab_ended();
}

bool ArrayTable::go_next()
{
  if(!is_tab_ended()) {
    curr_pos++;
  }
  return is_tab_ended();
}

int ArrayTable::get_current_pos() const
{
  return curr_pos;
}

TableString* ArrayTable::get_value()
{
    return tbl[curr_pos];
}

TableIterator ArrayTable::end() const
{
  return TableIterator{nullptr};
} 

TableIterator ArrayTable::begin() const
{
  return TableIterator{tbl[0]};
}

// Need Exception
void ArrayTable::erase(const std::string& key)
{
    TableString* tmp = find_str(key);
    if(tmp == nullptr) {
        throw(EqException(error_code::k_NOT_FOUND));
    }
    else {
      tbl[curr_pos] = tbl[data_cnt - 1];
      tbl[--data_cnt] = nullptr;
    }
}

void ArrayTable::print() const
{
    operator<<(std::cout, *this);
}

bool ArrayTable::is_full() const
{
    return data_cnt >= size;
}


void ArrayTable::insert(const TableString& data)
{
    if(is_full()) {
      throw(EqException(error_code::k_OUT_OF_MEMORY));
    }
    else {
      tbl[data_cnt] = new TableString(data);
      data_cnt++;
    }
}


TableString* ArrayTable::find_str(const std::string& key)
{
    for(TableIterator it = this->begin();
        it != this->end(); ++it)
    {
        if((*it).key == key) {
          return &(*it);
        }
    }
    return nullptr;
}


TableBody* ArrayTable::find(const std::string& key)
{
    for(TableIterator it = this->begin();
        it != this->end(); ++it)
    {
        if((*it).key == key) {
          return &((*it).body);
        }
    }
    return nullptr;
}