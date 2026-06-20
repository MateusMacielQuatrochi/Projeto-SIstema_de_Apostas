Sistema de Gerenciamento de Loterias (C++)

Este projeto foi desenvolvido como trabalho acadêmico durante o segundo semestre da faculdade de Sistemas de Informação. Trata-se de um sistema baseado em console para o gerenciamento completo de um ecossistema de loterias (apostadores, concursos e apostas), aplicando conceitos de Estruturas de Dados Homogêneas e Heterogêneas, e manipulação de arquivos binários em disco.

## 👥 Desenvolvedores
* **Arthur Orosco**
* **Mateus Maciel**
* **Gabriel Pereira / Renan Carvalho**

---

## 🎯 Projetos Ambientais em Pauta (Contexto do Sistema)
O sistema simula e organiza as escalas de apoio para projetos ecológicos em destaque, tais como:
* **BioFiltro Escolar:** Tratamento natural de águas cinzas.
* **Plástico Verde:** Produção de bioplástico com casca de banana.
* **Eco Luz:** Geração de energia solar com materiais recicláveis.

---

## 🛠️ Tecnologias Utilizadas e Arquitetura

O projeto foi inteiramente construído utilizando **C++ clássico**, aplicando conceitos de Estruturas de Dados Heterogêneas (`structs`) e persistência de arquivos binários em disco.

### 1. Bibliotecas Utilizadas
* `<conio2.h>`: Responsável por toda a interface visual (gerenciamento avançado do cursor com `gotoxy` e aplicação de cores com `textcolor`).
* `<stdio.h>` e `<stdlib.h>`: Operações de entrada/saída de dados e manipulação do sistema.
* `<string.h>` e `<ctype.h>`: Tratamento, validação e manipulação de Strings (como CPFs e Nomes).
* `<windows.h>`: Controle de temporização da interface visual (`Sleep`).
* `<time.h>`: Inicialização de geradores numéricos pseudo-aleatórios para simulações (`srand`).

### 2. Persistência de Dados e Arquivos Binários
Para evitar a perda de dados ao fechar o console, o sistema cria e manipula arquivos binários diretamente na pasta de execução:
* `Apostadores.dat` (Dados dos Voluntários)
* `Concursos.dat` (Dados dos Projetos/Ações)
* `Apostas.dat` (Relação de Engajamento e Bilhetes)

---

## 📂 Estrutura das Estruturas de Dados (`structs`)

O núcleo do sistema funciona de maneira relacional por meio de Chaves Primárias (`PK`):

* **`TpConcurso`**: Modela a ação ambiental. Armazena o ID do projeto, vetor de números de identificação (`NumSort`), data e status do registro.
* **`TpApostadores`**: Modela o voluntário. Utiliza o **CPF como Chave Primária**, registrando Nome, DDD e Telefone do apoiador.
* **`TpAposta`**: Modela o vínculo. Utiliza uma **Chave Primária Composta** (`NumCurso` + `CPF`), guardando a quantidade de números apostados/apoiados e as dezenas selecionadas.

---

## ⚙️ Funcionalidades do Sistema

A aplicação conta com um sistema de **Molduras Personalizadas** (renderizadas via tabela ASCII estendida) que protegem e delimitam os seguintes módulos navegáveis:

* **Módulo de Cadastros:** Rotinas com verificação exaustiva de duplicidade em arquivos para novos Concursos, Apostadores e Apostas.
* **Módulo de Buscas:** Localização rápida de registros em disco (`BusAposta_exaust`, `BuscarCPF`, etc.).
* **Módulo de Alterações:** Edição em tempo real de dados cadastrais ou modificação das dezenas jogadas nos bilhetes.
* **Módulo de Exclusão (Lógica e Física):** Os registros desativados recebem a flag de status `'I'` (Inativo). O sistema conta com a função `ExAposta_fisico`, que limpa o armazenamento gerando arquivos temporários purgados de lixo de memória.
* **Módulo de Relatórios Avançados:** * Exibição completa de apostadores comuns e premiados.
  * Estatísticas de dezenas que mais/menos aparecem nos sorteios e bilhetes.
  * Relatório de desempenho específico por quantidade de acertos (Terno, Quadra e Quina).
* **Módulo de Massa de Testes (`InsereTeste`):** Opção rápida integrada ao menu principal (`[F]`) para preencher o sistema instantaneamente com dados simulados para testes de rotina.

---

## 🚀 Como Executar

### Pré-requisitos
Por utilizar as bibliotecas nativas `<windows.h>` e `<conio2.h>`, este sistema é feito exclusivamente para rodar em ambientes **Windows**.

### Compilação via terminal:
Caso utilize o GCC/MinGW no terminal, certifique-se de lincar a biblioteca conio2:
```bash
g++ main.cpp -o Naturalize -lconio

📋 Observações Importantes (Aviso Acadêmico)

⚠️ Este é um projeto estritamente didático e de nível acadêmico de segundo semestre. Possui limitações estruturais intrínsecas:

    Gravação sequencial direta em arquivos em modo texto plano/binário.

    Interface gráfica limitada ao buffer padrão do Prompt de Comando do Windows (cmd.exe).

📄 Licença

Este projeto é distribuído sob a licença MIT.
