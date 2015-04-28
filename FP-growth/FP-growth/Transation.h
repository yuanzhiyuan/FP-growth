#ifndef GUARD_Transation_h
#define GUARD_Transation_h
class Transation{
public:
	Transation() :count(0), items(0){}
	Transation(unsigned count) :count(count){ items = new int[count]; }
	Transation(unsigned count, int* items) :count(count), items(items){}
	~Transation(){ delete items; }
	unsigned get_count() const{ return count; }
	int* get_items() const{ return items; }

private:
	unsigned count;//有多少个item
	int* items;//包含的item的id数组


};



#endif