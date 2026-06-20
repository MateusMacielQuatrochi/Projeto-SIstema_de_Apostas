Sistema de Gerenciamento de Loterias (C++)

Este projeto foi desenvolvido como trabalho acadêmico durante o segundo semestre da faculdade de Sistemas de Informação. Trata-se de um sistema baseado em console para o gerenciamento completo de um ecossistema de loterias (apostadores, concursos e apostas), aplicando conceitos de Estruturas de Dados Homogêneas e Heterogêneas, e manipulação de arquivos binários em disco.
👥 Desenvolvedores

    Arthur Orosco

    Mateus Maciel

    Gabriel Pereira

💻 Sobre o Projeto

O software simula as operações de uma banca de jogos lotéricos (com mecânica semelhante à Quina/Mega-Sena), operando integralmente através de uma interface baseada em caracteres (CLI) renderizada diretamente no prompt de comando do Windows.

O sistema organiza e gerencia as informações através de persistência em arquivos binários (.dat), garantindo que os dados de concursos, apostadores e cartões de apostas preenchidos permaneçam gravados após o encerramento do programa.
🛠️ Especificações Técnicas e Arquitetura
1. Bibliotecas Utilizadas

    <conio2.h>: Gerenciamento avançado de tela em modo texto (posicionamento de cursor com gotoxy e manipulação de cores com textcolor).

    <stdio.h> e <stdlib.h>: Operações padrões de Entrada/Saída e alocação de recursos.

    <string.h> e <ctype.h>: Manipulação, validação e tratamento de Strings e caracteres.

    <windows.h>: Controle do fluxo de temporização da aplicação (Sleep).

    <time.h>: Semente para aleatoriedade na simulação de sorteios (srand).

2. Estrutura de Dados (Modelagem das Structs)

O projeto define chaves primárias relacionais (PK) simulando conceitualmente uma modelagem de banco de dados:

    TpConcurso: Armazena o código identificador do concurso, os 5 números sorteados (TFNS), a data de realização e a flag de status do registro.

    TpApostadores: Contém os dados cadastrais do cliente, usando o CPF como Chave Primária, além de Nome, DDD e Telefone.

    TpAposta: Representa o bilhete jogado. Vincula o CPF do Apostador ao Número do Concurso (Chave Primária Composta), guardando a quantidade de números jogados (até 10 números) e o vetor com as dezenas escolhidas.

3. Gerenciamento de Memória e Registros

    Exclusão Lógica vs. Física: O sistema implementa exclusão lógica alterando a propriedade status do registro para 'I' (Inativo). Adicionalmente, possui rotinas de Exclusão Física (ExAposta_fisico), que limpam o arquivo gerando um arquivo temporário contendo apenas os dados com status 'A' (Ativo).

🗂️ Funcionalidades do Sistema

O sistema é modularizado através de menus interativos protegidos por molduras estéticas:

    Módulo de Cadastros: Registro validado contra duplicidades de Concursos, Apostadores (por CPF) e Bilhetes de Apostas.

    Módulo de Buscas: Localização rápida em disco baseada em chaves de pesquisa.

    Módulo de Alterações: Permite atualizar dados cadastrais ou refazer marcações de dezenas nos bilhetes.

    Módulo de Exclusão: Interface para desativação ou purga definitiva de dados.

    Módulo de Relatórios Avançados:

        Estatísticas de números que mais ou menos aparecem em sorteios/apostas.

        Resumo de apostadores premiados no concurso.

        Filtro de busca por quantidade específica de acertos (ex: acertadores de Terno, Quadra e Quina).

    Módulo de Teste Automatizado: Carga de dados rápida predefinida (InsereTeste) para validação imediata do comportamento do software sem necessidade de digitação manual exaustiva.
