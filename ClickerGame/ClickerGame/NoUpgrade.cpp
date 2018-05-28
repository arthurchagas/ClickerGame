#include "NoUpgrade.h"

NoUpgrade::NoUpgrade(Upgrade* item): item(item), proximo(nullptr), anterior(nullptr) {
}

NoUpgrade::NoUpgrade(): item(nullptr), proximo(nullptr), anterior(nullptr) {
}

NoUpgrade::~NoUpgrade() {
	delete item;
}

Upgrade*& NoUpgrade::get_item() {
	return item;
}

void NoUpgrade::set_item(Upgrade* item) {
	this->item = item;
}

NoUpgrade* NoUpgrade::get_proximo() const {
	return proximo;
}

void NoUpgrade::set_proximo(NoUpgrade* proximo) {
	this->proximo = proximo;
}

NoUpgrade* NoUpgrade::get_anterior() const {
	return anterior;
}

void NoUpgrade::set_anterior(NoUpgrade* anterior) {
	this->anterior = anterior;
}
