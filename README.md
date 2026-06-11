# Sistema de Manutenção de Contas Bancárias em C

Este projeto consiste em um sistema de gerenciamento de clientes e contas bancárias utilizando persistência em **arquivos binários com registros de tamanho fixo**, desenvolvido para fins acadêmicos.

## 🚀 Funcionalidades

O sistema disponibiliza um menu interativo com as seguintes operações:
1. **Cadastrar Cliente:** Grava um registro diretamente em uma posição física escolhida pelo usuário utilizando `fseek()`.
2. **Consultar Cliente:** Localiza dados do cliente através do número da conta.
3. **Atualizar Saldo:** Permite alterar o saldo de uma conta existente, voltando o ponteiro de escrita com `fseek()`.
4. **Encerrar Conta:** Realiza a exclusão lógica do cliente alterando uma flag de controle (`ativo = 0`), preservando a integridade do tamanho fixo dos registros.
5. **Listar Clientes:** Exibe os dados a partir da posição atual do cursor no arquivo.
6. **Restaurar Leitura (`rewind()`):** Retorna o cursor de leitura do arquivo para a posição inicial (`0`), permitindo listar ou buscar dados desde o início novamente.

## 🛠️ Detalhes Técnicos

- **Manipulação de Arquivos Binários:** Uso de funções nativas do C (`fread` e `fwrite`) para manipulação ágil dos blocos de memória da `struct`.
- **Registros de Tamanho Fixo:** Facilita o cálculo do deslocamento de bytes exato para inserções e consultas diretas (`posicao * sizeof(Cliente)`).

## 💻 Como Executar

1. Compile o código com um compilador C (ex: GCC):
   ```bash
   gcc main.c -o sistema_contas

   ./sistema_contas
