#include "Lista.h"

Lista::Lista(): tamanho(0) {
}

unsigned& Lista::get_tamanho() {
	return tamanho;
}

bool Lista::vazia() {
	return this->get_tamanho() == 0;
}

bool Lista::cheia() {
	return false;
}
