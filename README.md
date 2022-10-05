# Trabalho de Sistemas Operacionais

# Resumo

Este trabalho consiste na elaboração de quatro códigos, um vídeo explicando cada um deles e um relatório analisando os resultados destes.

# Código Auxiliar

O código auxiliar é responsável por gerar duas matrizes m1 x n1 e m2 x n2, sendo os valores lidos pela linha de comando nessa ordem, preenchendo-as com valores aleatórios de 0 a 99 e escrevendo cada uma delas em arquivos de nomes lidos como últimos argumentos da linha de comando. Este código é utiliado para gerar as matrizes requisitadas para a análise dos Experimentos 1 e 2, que pode ser encontrada no relatório presente neste repositório.

# Códigos

Os códigos fazem uso de algumas funções auxiliares para implementar o produto de matrizes, tais quais:


*matrix_generator:*
Lê um arquivo com uma matriz e gera um vetor de vetores com os valores lidos.

*tokenizer:*
Recebe uma string e um caracter de separação; separa a string em diversas strings utilizando como delimitador o caracter de separação, que é, por default, um espaço.

# Código Sequencial

O código sequencial é responsável por executar o produto de duas matrizes m1 x n1 e n1 x n2. Este código usa uma função auxiliar além das anteriores, que é:

*record:*
Recebe uma matriz e a escreve no arquivo, registrando, primeiro, as dimensões e, depois, cada elemento, cuja posição é denotada por c_{ij}, onde i é a linha e j a coluna. Ao fim, registra o tempo gasto na multiplicação.

O produto é executado na função MatProd, que segue a definição tradicional de uma multiplicação de matrizes e é feita sequencialmente - ou seja, sem fazer uso da programação paralela.

# Código Processos

Cada parte do produto é feita pela função calculations, que é chamada em cada processo. A própria função faz o registro no arquivo, que é diferente para cada processo. Ela é responsável por executar o produto de P elementos, sendo este P recebido na linha de comando.

# Código Threads

Cada parte do produto é feita pela função calculations, que é chamada em cada thread. A própria função faz o registro no arquivo, que é diferente para cada thread. Ela é responsável por executar o produto de P elementos, sendo este P recebido na linha de comando.
