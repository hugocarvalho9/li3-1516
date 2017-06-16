all: GereVendas clean

GereVendas: produtos clientes filial faturaçao
	gcc -g -ansi -Wextra -pedantic -O0 -o GereVendas ./main.c ./produtos ./clientes ./filial ./faturaçao

produtos: 
	gcc -c -g -O0 Produtos.c -o produtos

clientes: 
	gcc -c -g -O0 Clientes.c -o clientes

filial:
	gcc -c -g -O0 Filial.c -o filial

faturaçao:
	gcc -c -g -O0 Faturacao.c -o faturaçao

clean:
	rm produtos clientes filial faturaçao