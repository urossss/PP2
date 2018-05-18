#include "dz4.h"

int main() {
	List lst = loadList();
	printList(lst);
	sort(lst);
	printList(lst);
	deleteList(&lst);
}