#include "NoConstrucao.h"

NoConstrucao::NoConstrucao(Construcao* item) : item(item), proximo(nullptr), anterior(nullptr) {
}

NoConstrucao::NoConstrucao() : item(nullptr), proximo(nullptr), anterior(nullptr) {
}

NoConstrucao::~NoConstrucao() {
	delete item;
}

Construcao*& NoConstrucao::get_item() {
	return this->item;
}

void NoConstrucao::set_item(Construcao* item) {
	this->item = item;
}

NoConstrucao* NoConstrucao::get_proximo() const {
	return proximo;
}

void NoConstrucao::set_proximo(NoConstrucao* proximo) {
	this->proximo = proximo;
}

NoConstrucao* NoConstrucao::get_anterior() const {
	return anterior;
}

void NoConstrucao::set_anterior(NoConstrucao* anterior) {
	this->anterior = anterior;
}
