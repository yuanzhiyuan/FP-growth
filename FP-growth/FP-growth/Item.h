#ifndef GUARD_Item_h
#define GUARD_Item_h
class Item{
public:
	Item(){};
	Item(int id) :id(id), sup(0){};
	~Item();
	int getid() const{ return id; }
	unsigned getsup() const{ return sup; }
	void sup_add(unsigned added = 1);
	bool operator<(const Item& i) const{ return sup < i.getsup(); };
private:
	int id;
	unsigned sup;
};



#endif