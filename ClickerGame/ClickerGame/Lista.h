#ifndef LISTA_H
#define LISTA_H

class Lista {
protected:
	unsigned tamanho;
public:
	Lista();
	~Lista() = default;

	unsigned& get_tamanho();
	bool vazia();
	static bool cheia();
private:
};
#endif //LISTA_H