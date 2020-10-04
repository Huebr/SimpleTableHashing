// SimpleTableHashing.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include <chrono>
#include <stdint.h>
#include <iostream>
#include <random>
#include <vector>
#include <cstdio>
#pragma warning(disable:4996)//disable some vs safety warnings

using namespace std;

struct item { 
	int64_t data = 0;
	int8_t  bit = 0;
};

template <class element>
struct hashtable{
	int64_t T[8][256];
	int64_t n_elems = 0;
	int64_t n_removed = 0;
	vector<element> *ht;
	//create table to be used by simple hashing
	hashtable() {
	}
	hashtable(int size) {
		ht = new vector<element>(size);
		ht->resize(size);
		cout << "TAM:" <<size << endl;
		initialize_table();
	}
	~hashtable() {
		delete ht;
	}

	void initialize_table() {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 generator(seed);

		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 256; ++j) {
				T[i][j] = generator();
			}
		}

	}

	// simple table hashing implementation
	int64_t SimpleTableHashing(int64_t input)
	{
		int64_t i;
		int64_t h = 0;
		int8_t c;
		for (i = 0; i < 8; i++) {
			c = input;
			h ^= T[i][c];
			input = input >> 8;
		}
		return h;
	}


	void dobrar() {
		int64_t m = ht->capacity();
		vector<element> *temp = ht;
		ht = new vector<element>(m * 2);
		n_removed = 0;
		for (int i = 0; i < m; ++i) {
			if ((*temp)[i].bit == 1)incluir((*temp)[i].data,false);
		}
		delete temp;
	}

	void dividir() {
		int64_t m = ht->capacity();
		vector<element> *temp = ht;
		ht = new vector<element>(m / 2);
		n_removed = 0;
		for (int i = 0; i < m; ++i) {
			if ((*temp)[i].bit == 1)incluir((*temp)[i].data,false);
		}
		delete temp;
	}


	
	void incluir(int64_t data,bool debug) {
		int64_t hash = SimpleTableHashing(data);
		int64_t m = ht->capacity();
		for (int i = 0; i < m; ++i) {
			int64_t idx = (hash + i) % m;
			if ((*ht)[idx].bit != 1) {
				if ((*ht)[idx].bit == 3) n_removed--;
				(*ht)[idx].data = data;
				(*ht)[idx].bit = 1;
				if (debug)cout << hash % m << " " << idx << endl;
				break;
			}
		}
		//use debug variable to verify if function is external or internal
		if (debug) n_elems++;
		if (n_elems > (m/2)&&debug) {
			dobrar();
			cout << "DOBRAR TAM: " << m * 2 << endl;
		}

	}

	int64_t buscar(int64_t data) {
		int64_t hash = SimpleTableHashing(data);
		int64_t m = ht->capacity();
		cout << hash % m <<" ";
		for (int i = 0; i < m; ++i) {
			int64_t idx = (hash + i) % m;
			if (data == (*ht)[idx].data && (*ht)[idx].bit == 1) {
				return idx;
			}
			else if ((*ht)[idx].bit == 0)break;
		}
		return -1;
	}
	void limpar() {
		int64_t m = ht->capacity();
		vector<element> *temp = ht;
		ht = new vector<element>(m);
		for (int i = 0; i < m; ++i) {
			if ((*temp)[i].bit == 1)incluir((*temp)[i].data, false);
		}
		cout << "LIMPAR" << endl;
		delete temp;
	}

	void remover(int64_t data) {
		int64_t hash = SimpleTableHashing(data);
		int64_t m = ht->capacity();
		bool flag=false;
		bool cleared = false;

		for (int i = 0; i < m; ++i) {
			int64_t idx = (hash + i) % m;
			if ((*ht)[idx].data == data && (*ht)[idx].bit == 1) {
				(*ht)[idx].bit = 3;
				n_removed++;
				cout << hash % m << " " << idx << endl;
				cleared = true;
				break;
			}
		}

		if (cleared) {
			n_elems--;
			if (n_elems < (m / 4)) {
				dividir();
				cout << "DIVIDIR TAM: " << m / 2 << endl;
			}
			else if (n_removed > m / 4) limpar();
		}
		else cout << hash % m << " " << -1 << endl;
	}

};




int main(int argc,char **argv)
{
	if (argc != 3) {
		cout << "Arquivos não foram passados como argumento"<<endl;
		cout << "usage: program input_name.txt output_name.txt" << endl;
		cout << "obs: crie o arquivo de saida antes de chamar o programa." << endl;
		return -1;
	}

	FILE *fp;
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		cout << "erro abrindo arquivo de entrada.";
		return -1;
	}
	if (freopen(argv[2],"w+",stdout)==NULL) {
		cout << "erro abrindo arquivo de saida.";
		return -1;
	}

	char op[3];
	hashtable<item> ht(4);
	int data;
	char trash;


	if(fscanf(fp, "%c%c%c:%d", &op[0], &op[1], &op[2], &data) == 4) {
		do {
			switch (op[0])
			{
			case 'I':
				cout << "INC:" << data << endl;
				ht.incluir(data, true);
				break;
			case 'R':
				cout << "REM:" << data << endl;
				ht.remover(data);
				break;
			case 'B':
				cout << "BUS:" << data << endl;
				cout << ht.buscar(data) << endl;
				break;
			default:
				cout << "codigo de operacao invalido" << endl;
				break;
			}
		} while (fscanf(fp, "%c%c%c%c:%d", &trash, &op[0], &op[1], &op[2], &data) == 5);
	}
	
}