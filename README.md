# As Crônicas de Eldoria

## 1. Sobre o jogo

**As Crônicas de Eldoria** é um RPG de tabuleiro desenvolvido em linguagem C. O jogador escolhe uma classe, percorre diferentes regiões, enfrenta monstros, coleta recompensas, evolui seu personagem e enfrenta chefes para salvar o reino de Eldoria.

O jogo possui três fases com níveis de dificuldade progressivos, sistema de combate por turnos, movimentação com dados, habilidades especiais, equipamentos, poções, moedas de ouro e evolução de personagem.

## 2. História

Há muitos séculos, o reino de Eldoria era protegido pelo poderoso Coração da Luz.

Um antigo feiticeiro, conhecido como Rei Demoníaco, corrompeu o cristal e espalhou uma terrível maldição pelo reino. Monstros surgiram, cidades foram destruídas e a escuridão tomou conta das terras.

Agora, um herói foi escolhido para recuperar os três fragmentos do Coração da Luz e derrotar o responsável pela destruição.

### As três fases

- **Fase 1 – Floresta Sombria:** atravesse a floresta e derrote o Ogro Rei.
- **Fase 2 – A Masmorra:** enfrente criaturas amaldiçoadas e derrote o Lich.
- **Fase 3 – Reino Demoníaco:** enfrente os guardiões e derrote o Rei Demoníaco.

## 3. Classes disponíveis

O jogador pode escolher entre três classes. Todas começam no nível 1, com 50 moedas de ouro e três usos de habilidade especial.

### Guerreiro

Personagem voltado para resistência e defesa.

- Vida inicial: 140
- Ataque inicial: 20
- Defesa inicial: 15
- Agilidade inicial: 8
- Inteligência inicial: 5
- Equipamentos: Espada e Escudo.
- Habilidade especial: **Golpe Poderoso**, que causa dano baseado no ataque do personagem e na defesa do inimigo.

### Arqueiro

Personagem especializado em ataques e agilidade.

- Vida inicial: 130
- Ataque inicial: 21
- Defesa inicial: 10
- Agilidade inicial: 11
- Inteligência inicial: 8
- Equipamentos: Arco e Armadura Leve.
- Habilidade especial: **Disparo Preciso**, que pode causar dano adicional dependendo do resultado do dado.

### Mago

Personagem especializado em inteligência e magia.

- Vida inicial: 120
- Ataque inicial: 29
- Defesa inicial: 7
- Agilidade inicial: 8
- Inteligência inicial: 11
- Equipamentos: Cajado e Manto Arcano.
- Habilidade especial: **Bola de Fogo**, que causa dano direto e aplica queimadura ao inimigo.

*Os atributos iniciais consideram os atributos-base, os bônus da classe e os equipamentos iniciais.*

## 4. Monstros e chefes

### Fase 1 – Floresta Sombria

| Monstro | Vida | Ataque | Defesa |
|---|---:|---:|---:|
| Goblin | 40 | 8 | 5 |
| Lobo Selvagem | 50 | 12 | 7 |
| Guerreiro Esqueleto | 60 | 16 | 10 |
| **Ogro Rei (chefe)** | **100** | **18** | **10** |

### Fase 2 – Masmorra

| Monstro | Vida | Ataque | Defesa |
|---|---:|---:|---:|
| Morto Vivo | 65 | 16 | 10 |
| Golem Guardião | 120 | 13 | 20 |
| Aranha Gigante | 70 | 18 | 8 |
| **Lich (chefe)** | **180** | **25** | **15** |

### Fase 3 – Reino Demoníaco

| Monstro | Vida | Ataque | Defesa |
|---|---:|---:|---:|
| Demônio | 130 | 28 | 15 |
| Cavaleiro Amaldiçoado | 160 | 30 | 22 |
| Cão Infernal | 120 | 32 | 12 |
| **Rei Demoníaco (chefe)** | **300** | **35** | **20** |

Os monstros comuns são selecionados aleatoriamente entre os três disponíveis em cada fase.

## 5. Tabuleiro e movimentação

Cada fase possui um tabuleiro com 10 casas. O jogador utiliza um dado de seis lados para determinar quantas casas avançará.

### Tipos de casas

| Símbolo | Casa | Efeito |
|---|---|---|
| V | Vazia | Nenhum evento especial. |
| C | Combate | Enfrenta um monstro aleatório. |
| T | Tesouro | Recebe moedas de ouro. |
| H | Cura | Recupera 20 pontos de vida. |
| A | Armadilha | Recebe dano aleatório. |
| L | Loja | Permite comprar poções. |
| M | Missão | Apresenta a história e libera o confronto com o chefe. |
| B | Chefe | Inicia a batalha contra o chefe da fase. |

A casa do chefe só pode ser acessada após a conclusão da missão narrativa da fase.

### Organização dos tabuleiros

- **Fácil:** Vazia, Combate, Tesouro, Vazia, Cura, Combate, Armadilha, Loja, Missão e Chefe.
- **Médio:** Vazia, Combate, Cura, Tesouro, Combate, Armadilha, Loja, Combate, Missão e Chefe.
- **Difícil:** Vazia, Combate, Armadilha, Loja, Combate, Tesouro, Cura, Combate, Missão e Chefe.

## 6. Sistema de combate

O combate acontece por turnos. Durante sua vez, o jogador pode escolher:

1. **Atacar:** realiza um ataque normal.
2. **Defender:** reduz pela metade o dano recebido no próximo ataque inimigo.
3. **Habilidade especial:** utiliza uma habilidade específica da classe.
4. **Fugir:** tenta escapar de um combate comum.
5. **Usar poção:** recupera pontos de vida.

Não é possível fugir de uma batalha contra um chefe.

### Fórmula do ataque normal

O ataque recebe um bônus baseado em um dado de 20 lados:

`Ataque total = Ataque do personagem + (D20 / 4)`

O dano é calculado por:

`Dano = Ataque total - (Defesa do monstro / 2)`

O dano mínimo é 1.

- **Falha crítica:** resultado 1 no dado, causando zero de dano.
- **Acerto crítico:** resultado 20 no dado, aumentando o ataque em 50%.

### Ataque dos monstros

`Ataque total = Ataque do monstro + (D20 / 4)`

`Dano = Ataque total - Defesa do personagem`

O dano mínimo é 1. Caso o personagem esteja defendendo, o dano recebido é reduzido pela metade.

### Habilidades especiais

- **Guerreiro – Golpe Poderoso:** ataque baseado no ataque do personagem, com bônus de 5, reduzido pela defesa do monstro.
- **Arqueiro – Disparo Preciso:** causa dano baseado no dobro do ataque, reduzido pela metade da defesa do monstro. Resultados altos no dado aumentam o dano.
- **Mago – Bola de Fogo:** causa dano baseado no ataque e na inteligência, reduzido pela defesa do monstro. Também aplica 5 pontos de dano de queimadura durante 3 turnos.

Cada personagem começa com três usos de habilidade especial. Os usos são restaurados ao subir de nível.

### Tentativa de fuga

A fuga utiliza um dado de 20 lados:

`Resultado = D20 + (Agilidade / 4)`

O jogador consegue fugir quando o resultado é igual ou superior a 15.

## 7. Experiência e evolução

Ao derrotar monstros, o jogador recebe pontos de experiência (XP).

Ao alcançar 100 XP, o personagem sobe de nível e recebe:

- +20 de vida máxima;
- recuperação completa da vida;
- +3 de ataque;
- +1 de defesa;
- restauração dos usos da habilidade especial.

Além disso, ao derrotar um monstro comum e sobreviver ao combate, o jogador recebe um bônus aleatório:

- +1 de ataque;
- +1 de defesa;
- +1 de agilidade;
- +1 de inteligência;
- +5 de vida máxima.

## 8. Ouro, tesouros e loja

O jogador começa a aventura com 50 moedas de ouro.

Ao encontrar um tesouro, recebe uma quantidade aleatória de 1 a 30 moedas.

A loja oferece:

| Item | Preço | Efeito |
|---|---:|---|
| Poção pequena | 20 moedas | Recupera 30 de vida. |
| Poção grande | 40 moedas | Recupera 60 de vida. |

As poções não podem ultrapassar a vida máxima do personagem.

Os monstros e chefes também concedem moedas de ouro ao serem derrotados.

### Recompensas dos chefes

- **Ogro Rei:** Cristal de Vitalidade – +20 de vida máxima e atual.
- **Lich:** Núcleo Arcano – +5 de ataque e +5 de inteligência.
- **Rei Demoníaco:** Coração Demoníaco – +10 de ataque, +10 de defesa e +10 de inteligência.

## 9. Condições de vitória e derrota

**Vitória:** derrotar o Rei Demoníaco na terceira fase e completar a aventura.

**Derrota:** perder todos os pontos de vida durante a jornada.

Ao final, o jogo apresenta um resumo da aventura com nome do personagem, nível, experiência, vida, ouro, fase alcançada e resultado final.

## 10. Estruturas utilizadas na programação

O projeto foi desenvolvido em linguagem C e utiliza:

- **Struct:** para representar personagens, monstros e itens.
- **Enum:** para definir classes, tipos de itens, casas do tabuleiro, ações de combate e dificuldades.
- **Vetores:** para armazenar monstros e organizar os tabuleiros.
- **Ponteiros:** para modificar atributos de personagens e monstros dentro das funções.
- **Funções:** para separar os sistemas de movimentação, combate, inventário, recompensas e evolução.
- **Aleatoriedade:** utilizando `rand()`, `srand()` e `time()` para dados, eventos e seleção de monstros.

O código principal está localizado em `src/main.c`.

## 11. Como compilar e executar

É necessário ter o GCC instalado.

### Windows (PowerShell)

Na pasta principal do projeto, execute:

```bash
gcc -Wall -Wextra -o rpg src/main.c -lm
```

Depois:

```powershell
.\rpg.exe
```

### Linux

```bash
gcc -Wall -Wextra -o rpg src/main.c -lm
./rpg
```

### macOS

```bash
gcc -Wall -Wextra -o rpg src/main.c -lm
./rpg
```

## 12. Estrutura do projeto

```text
cronicas-de-eldoria/
│
├── README.md
├── src/
│   └── main.c
├── images/
│   ├── personagens/
│   └── monstros/
└── video/
    └── link_video.md
```

## 13. Desenvolvedor

- **Nome:** Felipe Gabriel Medeiros de Araújo
- **Matrícula:** 20250068156
- **Curso:** Sistemas de Informação
- **Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)

## 14. Demonstração

Vídeo de apresentação e demonstração do jogo:

(https://youtu.be/-YAE-eFubnQ)
