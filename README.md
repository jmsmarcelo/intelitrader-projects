# Intelitrader Projects

Este repositório contém três desafios desenvolvidos em linguagem C como parte do processo técnico da Intelitrader. Cada projeto foi elaborado com foco em boas práticas de programação, tratamento de memória dinâmica, entrada do usuário e lógica algorítmica clara.

## 📚 Desafios

### 1. Criptografia na rede do navio

#### [Teste Online](https://onlinegdb.com/3ywz5FlrX)

#### Exemplo

```bash
Welcome to ShipEncryptor

Options:
 1. Encrypt message
 2. Decrypt message
 3. Quit

Choose an option (1, 2 or 3): 1

Enter the message to encrypt: Hello World

Encrypted message: 10000111 01010101 11000101 11000101 11110101 00000001 01110110 11110101 00100100 11000101 01000101 00000011

Choose an option (1, 2 or 3): 2

Enter the message to decrypt: 10000111 01010101 11000101 11000101 11110101 00000001 01110110 11110101 00100100 11000101 01000101 00000011

Decrypted message: Hello World

Choose an option (1, 2 or 3): 3
Goodbye!
```

---

### 2. Menor distância de dois arrays

#### [Teste Online](https://onlinegdb.com/WUA6wDiok)

#### Exemplo

```bash
Welcome to Shortest distance between two arrays

Input the numbers for array 1: -1, 5
Input the numbers for array 2: 26, 6

Minimum distance: 1 (betwween 5 in array 1 and 6 in array 2)

Input again(y), or quit(q)? q
Goodbye!
```

---

### 3. Livro de ofertas

#### [Teste Online](https://onlinegdb.com/1BCetUmWp)

#### Exemplo

```bash
Welcome to Order Book

Options: y = yes, q = quit

Input updates? (y or q): y
Input: 12
1,0,15.4,50
2,0,15.5,50
2,2,0,0
2,0,15.4,10
3,0,15.9,30
3,1,0,20
4,0,16.50,200
5,0,17.00,100
6,0,16.59,20
5,2,0,0
1,2,0,0
2,1,15.6,0

+----------+-----------+----------+
| Position |   Price   | Quantity |
+----------+-----------+----------+
|        1 |     15.40 |       10 |
+----------+-----------+----------+
|        2 |     15.60 |       20 |
+----------+-----------+----------+
|        3 |     16.50 |      200 |
+----------+-----------+----------+
|        4 |     16.59 |       20 |
+----------+-----------+----------+
Input updates? (y or q): q
Goodbye!
```

## 🛠️ Como Executar

### Pré-Requisitos

- Para compilar:
  - Linux: **GCC** (GNU Compiler Collection)
  - Windows: **MSVC** (via Developer Command Prompt)
- Para executar:
  - Qualquer terminal (Bash, CMD ou PowerShell)

### Etapas para Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/jmsmarcelo/intelitrader-projects
   cd intelitrader-projects
   ```
2. Compile o desafio escolhido:
   ```bash
   mkdir  build             # criar uma pasta para melhor organização
   cd build

   # Linux:
   gcc  -o <nome_do_executável> ../my_solutions/<nome_do_arquivo>.c

   # Windows (MSVC):
   cl /Fe:<nome_do_executável> ..\my_solutions\<nome_do_arquivo>.c

   # Exemplo:
   gcc -o ship-encryptor ../my_solutions/ship_encryptor.c       # Linux
   cl /Fe:ship-encryptor.exe ..\my_solutions\ship_encryptor.c   # Windows
   ```
3. Executar o aplicativo:
   ```bash
   ./<nome_do_executável>   # Linux
   .\<nome_do_executável>   # Windows

   # Exemplo:
   ./ship-encryptor         # Linux
   ship-encryptor.exe       # Windows
   ```

## 👨‍💻 Autor

Desenvolvido por **[Jose Marcelo](https://jmsmarcelo.github.io)**

*Desafios  resolvidos com foco   em clareza, validação  de entrada e uso eficiente de ponteiros e memória dinâmica em C.*

## 📝 Licença

Este projeto está licenciado sob os termos da Licença MIT. Veja o arquivo [LICENSE](https://github.com/jmsmarcelo/intelitrader-projects/blob/main/LICENSE) para mais detalhes.
