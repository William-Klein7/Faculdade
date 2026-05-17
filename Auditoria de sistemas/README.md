# Sistema de Auditoria de Banco de Dados

Este projeto sobe um ambiente PostgreSQL local via Docker Compose para simular um sistema corporativo de auditoria de banco de dados.

Ao iniciar o container pela primeira vez, o PostgreSQL executa automaticamente o arquivo `init.sql`, criando:

- As tabelas do modelo de auditoria
- As chaves primárias e estrangeiras
- Os comentários de documentação do banco
- Os dados fictícios para testes

## Estrutura do projeto

```text
.
|-- docker-compose.yml
|-- init.sql
|-- seed_eletromissoes.sql
|-- README.md
```

## Tecnologias utilizadas

- Docker
- Docker Compose
- PostgreSQL 15 Alpine

## Pré-requisitos

Antes de executar o projeto, instale:

- Docker Desktop
- Docker Compose

Observação:

- Em versões recentes do Docker Desktop, o comando padrão costuma ser `docker compose`
- Em ambientes antigos, pode ser necessário usar `docker-compose`

## Configuração do banco

O serviço definido no `docker-compose.yml` utiliza os seguintes parâmetros:

- Container: `postgres_trabalho_auditoria`
- Imagem: `postgres:15-alpine`
- Banco: `auditoria_db`
- Usuário: `admin`
- Senha: `adminpassword`
- Porta local: `5432`

## Como subir o ambiente

No diretório do projeto, execute:

```bash
docker compose up -d
```

Se sua instalação usar o binário legado:

```bash
docker-compose up -d
```

Esse comando irá:

1. Baixar a imagem do PostgreSQL, se necessário
2. Criar o volume persistente do banco
3. Subir o container `postgres_trabalho_auditoria`
4. Executar automaticamente o arquivo `init.sql` na primeira inicialização

## Como verificar se o container está rodando

```bash
docker ps
```

Você também pode verificar os logs:

```bash
docker compose logs -f
```

Ou, no formato antigo:

```bash
docker-compose logs -f
```

## Como acessar o PostgreSQL no container

Para abrir o terminal `psql` dentro do container:

```bash
docker exec -it postgres_trabalho_auditoria psql -U admin -d auditoria_db
```

Depois disso, você poderá executar comandos SQL diretamente.

## Consultas úteis para validação

### Listar tabelas criadas

No `psql`:

```sql
\dt
```

### Ver a estrutura de uma tabela

```sql
\d usuarios
```

### Consultar os dados inseridos

```sql
SELECT * FROM perfis_permissao;
SELECT * FROM usuarios;
SELECT * FROM conexoes_bd;
SELECT * FROM auditoria_consultas;
SELECT * FROM alteracoes_privilegios;
SELECT * FROM incidentes_auditoria;
```

### Consultar conexões com falha

```sql
SELECT *
FROM conexoes_bd
WHERE status_login = 'FALHA';
```

### Consultar acessos fora do horário comercial

```sql
SELECT *
FROM conexoes_bd
WHERE EXTRACT(HOUR FROM data_hora_login) < 8
   OR EXTRACT(HOUR FROM data_hora_login) >= 18;
```

### Consultar eventos em objeto sensível

```sql
SELECT *
FROM auditoria_consultas
WHERE objeto_bd = 'folha_pagamento';
```

### Consultar usuários com perfil crítico

```sql
SELECT u.id_usuario, u.nome, u.login, p.nome_perfil, p.criticidade
FROM usuarios u
JOIN perfis_permissao p ON p.id_perfil = u.perfil
WHERE p.nome_perfil IN ('DBA', 'SUPERUSER');
```

## Tabelas criadas no banco

O script `init.sql` cria as seguintes tabelas:

- `perfis_permissao`
- `usuarios`
- `conexoes_bd`
- `auditoria_consultas`
- `alteracoes_privilegios`
- `incidentes_auditoria`

O modelo inclui cenários de auditoria como:

- Usuários com privilégios `DBA` e `SUPERUSER`
- Conexões realizadas às 3h da manhã
- Múltiplas falhas de autenticação para o mesmo usuário
- Consultas ao objeto sensível `folha_pagamento`
- Alterações indevidas de privilégios

## Carga massiva da Eletromissoes

O arquivo `seed_eletromissoes.sql` foi criado para substituir os dados iniciais por uma massa de dados mais realista da empresa fictícia Eletromissoes.

Esse script:

- limpa as tabelas com `TRUNCATE ... RESTART IDENTITY`
- recria os perfis de permissão coerentes com o organograma
- insere exatamente 500 usuários
- gera milhares de conexões e eventos de auditoria para 90 dias
- injeta anomalias propositais para testes de segurança

Para executar a carga massiva no PowerShell:

```powershell
Get-Content .\seed_eletromissoes.sql -Raw | docker exec -i postgres_trabalho_auditoria psql -U admin -d auditoria_db
```

Alternativa robusta, copiando o arquivo para dentro do container:

```powershell
docker cp .\seed_eletromissoes.sql postgres_trabalho_auditoria:/tmp/seed_eletromissoes.sql
docker exec -it postgres_trabalho_auditoria psql -U admin -d auditoria_db -f /tmp/seed_eletromissoes.sql
```

Se estiver usando `cmd` ou Git Bash, a redireção com `<` também funciona:

```bash
docker exec -i postgres_trabalho_auditoria psql -U admin -d auditoria_db < seed_eletromissoes.sql
```

Depois, valide rapidamente:

```bash
docker exec -it postgres_trabalho_auditoria psql -U admin -d auditoria_db
```

No `psql`:

```sql
SELECT COUNT(*) FROM usuarios;
SELECT COUNT(*) FROM conexoes_bd;
SELECT COUNT(*) FROM auditoria_consultas;
SELECT COUNT(*) FROM alteracoes_privilegios;
SELECT COUNT(*) FROM incidentes_auditoria;
```

## Como parar o ambiente

```bash
docker compose down
```

Ou:

```bash
docker-compose down
```

Esse comando remove o container, mas mantém o volume com os dados.

## Como recriar o banco do zero

Importante:

- O PostgreSQL executa scripts em `/docker-entrypoint-initdb.d/` apenas quando o diretório de dados está vazio
- Isso significa que o `init.sql` roda somente na primeira criação do banco

Se você alterar o `init.sql` e quiser que ele seja executado novamente, remova também o volume:

```bash
docker compose down -v
docker compose up -d
```

Ou:

```bash
docker-compose down -v
docker-compose up -d
```

## Como testar a conexão externamente

Você pode conectar em qualquer cliente PostgreSQL usando:

- Host: `localhost`
- Port: `5432`
- Database: `auditoria_db`
- User: `admin`
- Password: `adminpassword`

Exemplos de ferramentas:

- DBeaver
- pgAdmin
- DataGrip
- Azure Data Studio com extensão PostgreSQL

## Solução de problemas

### Porta 5432 já está em uso

Se outra instância do PostgreSQL estiver usando a porta `5432`, altere o mapeamento no `docker-compose.yml`:

```yaml
ports:
  - "5433:5432"
```

Nesse caso, conecte usando a porta `5433`.

### O script SQL não foi executado

Isso normalmente acontece porque o volume já existia e o banco foi inicializado anteriormente.

Recrie o ambiente com:

```bash
docker compose down -v
docker compose up -d
```

### O container não sobe

Verifique os logs:

```bash
docker compose logs
```

### Quero conferir se o banco foi criado corretamente

Entre no `psql` e rode:

```sql
SELECT current_database();
SELECT COUNT(*) FROM usuarios;
SELECT COUNT(*) FROM conexoes_bd;
SELECT COUNT(*) FROM auditoria_consultas;
```

## Comandos rápidos

Subir ambiente:

```bash
docker compose up -d
```

Ver logs:

```bash
docker compose logs -f
```

Entrar no banco:

```bash
docker exec -it postgres_trabalho_auditoria psql -U admin -d auditoria_db
```

Parar ambiente:

```bash
docker compose down
```

Recriar do zero:

```bash
docker compose down -v
docker compose up -d
```

## Observação final

Este ambiente foi pensado para estudo, demonstração e validação do modelo de auditoria em PostgreSQL. Para uso real em produção, recomenda-se complementar com:

- Controle de acesso por roles reais do PostgreSQL
- Criptografia e gestão segura de segredos
- Políticas de backup
- Auditoria nativa com extensões ou trilhas adicionais
- Monitoramento e alertas de segurança
