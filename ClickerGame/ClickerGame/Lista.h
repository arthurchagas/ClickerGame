#pragma once

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
