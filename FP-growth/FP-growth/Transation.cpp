#include "Transation.h"


void Transation::go(){
	if (count == 0)	return;
	items++;
	count--;
	return;
}