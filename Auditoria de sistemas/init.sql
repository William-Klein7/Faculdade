BEGIN;

CREATE TABLE perfis_permissao (
    id_perfil serial PRIMARY KEY,
    nome_perfil text NOT NULL,
    recurso text NOT NULL,
    tipo_permissao text NOT NULL,
    criticidade text NOT NULL,
    CONSTRAINT ck_perfis_permissao_criticidade
        CHECK (criticidade IN ('BAIXA', 'MEDIA', 'ALTA', 'CRITICA'))
);

CREATE TABLE usuarios (
    id_usuario serial PRIMARY KEY,
    nome text NOT NULL,
    login text NOT NULL UNIQUE,
    setor text NOT NULL,
    perfil int NOT NULL,
    status text NOT NULL,
    CONSTRAINT fk_usuarios_perfil
        FOREIGN KEY (perfil)
        REFERENCES perfis_permissao (id_perfil),
    CONSTRAINT ck_usuarios_status
        CHECK (status IN ('ATIVO', 'INATIVO', 'BLOQUEADO'))
);

CREATE TABLE conexoes_bd (
    id_conexao serial PRIMARY KEY,
    id_usuario int NOT NULL,
    data_hora_login timestamp NOT NULL,
    ip_origem text NOT NULL,
    banco text NOT NULL,
    status_login text NOT NULL,
    CONSTRAINT fk_conexoes_bd_usuario
        FOREIGN KEY (id_usuario)
        REFERENCES usuarios (id_usuario),
    CONSTRAINT ck_conexoes_bd_status_login
        CHECK (status_login IN ('SUCESSO', 'FALHA'))
);

CREATE TABLE auditoria_consultas (
    id_evento serial PRIMARY KEY,
    id_usuario int NOT NULL,
    data_hora timestamp NOT NULL,
    tipo_acao text NOT NULL,
    objeto_bd text NOT NULL,
    criticidade text NOT NULL,
    CONSTRAINT fk_auditoria_consultas_usuario
        FOREIGN KEY (id_usuario)
        REFERENCES usuarios (id_usuario),
    CONSTRAINT ck_auditoria_consultas_criticidade
        CHECK (criticidade IN ('BAIXA', 'MEDIA', 'ALTA', 'CRITICA'))
);

CREATE TABLE alteracoes_privilegios (
    id_alt serial PRIMARY KEY,
    id_usuario_alvo int NOT NULL,
    id_usuario_executor int NOT NULL,
    privilegio_anterior text NOT NULL,
    privilegio_novo text NOT NULL,
    data_hora timestamp NOT NULL,
    CONSTRAINT fk_alt_privilegios_usuario_alvo
        FOREIGN KEY (id_usuario_alvo)
        REFERENCES usuarios (id_usuario),
    CONSTRAINT fk_alt_privilegios_usuario_executor
        FOREIGN KEY (id_usuario_executor)
        REFERENCES usuarios (id_usuario)
);

CREATE TABLE incidentes_auditoria (
    id_incidente serial PRIMARY KEY,
    categoria text NOT NULL,
    descricao text NOT NULL,
    risco text NOT NULL,
    evidencias text NOT NULL,
    veredicto text NOT NULL
);

CREATE INDEX idx_usuarios_perfil ON usuarios (perfil);
CREATE INDEX idx_conexoes_bd_usuario_data ON conexoes_bd (id_usuario, data_hora_login);
CREATE INDEX idx_auditoria_consultas_usuario_data ON auditoria_consultas (id_usuario, data_hora);
CREATE INDEX idx_alteracoes_privilegios_alvo_data ON alteracoes_privilegios (id_usuario_alvo, data_hora);
CREATE INDEX idx_alteracoes_privilegios_executor_data ON alteracoes_privilegios (id_usuario_executor, data_hora);

COMMENT ON TABLE perfis_permissao IS 'Cataloga os perfis corporativos e as permissões concedidas sobre recursos de banco de dados monitorados pela auditoria.';
COMMENT ON COLUMN perfis_permissao.id_perfil IS 'Identificador único do perfil de permissão.';
COMMENT ON COLUMN perfis_permissao.nome_perfil IS 'Nome corporativo do perfil de acesso, como DBA, SUPERUSER ou AUDITOR.';
COMMENT ON COLUMN perfis_permissao.recurso IS 'Recurso, objeto ou ambiente de banco de dados ao qual a permissão se aplica.';
COMMENT ON COLUMN perfis_permissao.tipo_permissao IS 'Tipo de privilégio concedido no contexto do recurso monitorado.';
COMMENT ON COLUMN perfis_permissao.criticidade IS 'Classificação de criticidade do perfil para fins de risco e conformidade.';

COMMENT ON TABLE usuarios IS 'Armazena os usuários internos ou terceiros com acesso aos ambientes de banco de dados auditados.';
COMMENT ON COLUMN usuarios.id_usuario IS 'Identificador único do usuário auditado.';
COMMENT ON COLUMN usuarios.nome IS 'Nome completo do usuário cadastrado no contexto corporativo.';
COMMENT ON COLUMN usuarios.login IS 'Login corporativo utilizado para autenticação nos bancos de dados.';
COMMENT ON COLUMN usuarios.setor IS 'Área organizacional à qual o usuário está vinculado.';
COMMENT ON COLUMN usuarios.perfil IS 'Referência ao perfil de permissão atribuído ao usuário.';
COMMENT ON COLUMN usuarios.status IS 'Situação do usuário no processo de governança de acessos.';

COMMENT ON TABLE conexoes_bd IS 'Registra tentativas de autenticação e sessões de acesso aos bancos de dados monitorados.';
COMMENT ON COLUMN conexoes_bd.id_conexao IS 'Identificador único do evento de conexão.';
COMMENT ON COLUMN conexoes_bd.id_usuario IS 'Usuário responsável pela tentativa de acesso ao banco.';
COMMENT ON COLUMN conexoes_bd.data_hora_login IS 'Data e hora da tentativa de autenticação ou abertura de sessão.';
COMMENT ON COLUMN conexoes_bd.ip_origem IS 'Endereço IP de origem da conexão, usado para rastreabilidade.';
COMMENT ON COLUMN conexoes_bd.banco IS 'Nome do banco de dados ou ambiente acessado.';
COMMENT ON COLUMN conexoes_bd.status_login IS 'Resultado da tentativa de autenticação, como SUCESSO ou FALHA.';

COMMENT ON TABLE auditoria_consultas IS 'Mantém a trilha de consultas e ações executadas sobre objetos sensíveis ou relevantes para auditoria.';
COMMENT ON COLUMN auditoria_consultas.id_evento IS 'Identificador único do evento auditado.';
COMMENT ON COLUMN auditoria_consultas.id_usuario IS 'Usuário que executou a ação no banco de dados.';
COMMENT ON COLUMN auditoria_consultas.data_hora IS 'Data e hora da ação registrada pela trilha de auditoria.';
COMMENT ON COLUMN auditoria_consultas.tipo_acao IS 'Tipo de operação realizada, como SELECT, UPDATE, DELETE ou ALTER.';
COMMENT ON COLUMN auditoria_consultas.objeto_bd IS 'Objeto do banco de dados impactado ou consultado.';
COMMENT ON COLUMN auditoria_consultas.criticidade IS 'Nível de criticidade atribuído ao evento auditado.';

COMMENT ON TABLE alteracoes_privilegios IS 'Histórico de concessões, revogações ou mudanças de privilégios entre usuários auditados.';
COMMENT ON COLUMN alteracoes_privilegios.id_alt IS 'Identificador único da alteração de privilégio.';
COMMENT ON COLUMN alteracoes_privilegios.id_usuario_alvo IS 'Usuário que recebeu ou perdeu o privilégio.';
COMMENT ON COLUMN alteracoes_privilegios.id_usuario_executor IS 'Usuário que executou a alteração de privilégio.';
COMMENT ON COLUMN alteracoes_privilegios.privilegio_anterior IS 'Privilégio existente antes da alteração registrada.';
COMMENT ON COLUMN alteracoes_privilegios.privilegio_novo IS 'Privilégio resultante após a alteração registrada.';
COMMENT ON COLUMN alteracoes_privilegios.data_hora IS 'Data e hora em que a alteração de privilégio foi executada.';

COMMENT ON TABLE incidentes_auditoria IS 'Consolida ocorrências identificadas pela auditoria, com evidências e conclusão para tratamento corporativo.';
COMMENT ON COLUMN incidentes_auditoria.id_incidente IS 'Identificador único do incidente de auditoria.';
COMMENT ON COLUMN incidentes_auditoria.categoria IS 'Categoria de risco ou desvio identificado pela auditoria.';
COMMENT ON COLUMN incidentes_auditoria.descricao IS 'Descrição executiva e técnica do incidente apurado.';
COMMENT ON COLUMN incidentes_auditoria.risco IS 'Classificação de risco associada ao incidente.';
COMMENT ON COLUMN incidentes_auditoria.evidencias IS 'Resumo das evidências coletadas para comprovação do incidente.';
COMMENT ON COLUMN incidentes_auditoria.veredicto IS 'Conclusão final da análise de auditoria sobre o incidente.';

INSERT INTO perfis_permissao (id_perfil, nome_perfil, recurso, tipo_permissao, criticidade) VALUES
(1, 'DBA', 'cluster_postgresql', 'ADMINISTRACAO_TOTAL', 'CRITICA'),
(2, 'SUPERUSER', 'instancia_financeira', 'SUPERUSER', 'CRITICA'),
(3, 'AUDITOR', 'logs_auditoria', 'LEITURA', 'MEDIA'),
(4, 'ANALISTA_RH', 'folha_pagamento', 'LEITURA_RESTRITA', 'ALTA'),
(5, 'DESENVOLVEDOR', 'schema_app', 'DML', 'MEDIA');

INSERT INTO usuarios (id_usuario, nome, login, setor, perfil, status) VALUES
(1, 'Mariana Costa', 'mcosta', 'Infraestrutura', 1, 'ATIVO'),
(2, 'Carlos Souza', 'csouza', 'Financeiro', 2, 'ATIVO'),
(3, 'Fernanda Lima', 'flima', 'Auditoria', 3, 'ATIVO'),
(4, 'Juliana Rocha', 'jrocha', 'RH', 4, 'ATIVO'),
(5, 'Rafael Nunes', 'rnunes', 'Desenvolvimento', 5, 'BLOQUEADO');

INSERT INTO conexoes_bd (id_conexao, id_usuario, data_hora_login, ip_origem, banco, status_login) VALUES
(1, 1, '2026-04-22 03:12:00', '10.10.5.21', 'auditoria_corp', 'SUCESSO'),
(2, 2, '2026-04-22 03:18:00', '172.16.0.45', 'financeiro_prod', 'SUCESSO'),
(3, 5, '2026-04-22 08:01:00', '10.10.8.99', 'app_prod', 'FALHA'),
(4, 5, '2026-04-22 08:03:00', '10.10.8.99', 'app_prod', 'FALHA'),
(5, 5, '2026-04-22 08:05:00', '10.10.8.99', 'app_prod', 'FALHA'),
(6, 3, '2026-04-22 09:20:00', '10.10.4.33', 'auditoria_corp', 'SUCESSO'),
(7, 4, '2026-04-22 14:10:00', '10.10.6.18', 'rh_prod', 'SUCESSO');

INSERT INTO auditoria_consultas (id_evento, id_usuario, data_hora, tipo_acao, objeto_bd, criticidade) VALUES
(1, 2, '2026-04-22 03:25:00', 'SELECT', 'folha_pagamento', 'CRITICA'),
(2, 1, '2026-04-22 03:30:00', 'ALTER', 'usuarios_sistema', 'CRITICA'),
(3, 3, '2026-04-22 09:25:00', 'SELECT', 'trilha_auditoria', 'MEDIA'),
(4, 4, '2026-04-22 14:15:00', 'SELECT', 'folha_pagamento', 'ALTA'),
(5, 5, '2026-04-22 08:06:00', 'SELECT', 'folha_pagamento', 'ALTA'),
(6, 2, '2026-04-22 03:27:00', 'SELECT', 'dados_bancarios_fornecedores', 'CRITICA'),
(7, 1, '2026-04-22 11:00:00', 'CREATE ROLE', 'temp_admin', 'ALTA');

INSERT INTO alteracoes_privilegios (id_alt, id_usuario_alvo, id_usuario_executor, privilegio_anterior, privilegio_novo, data_hora) VALUES
(1, 5, 1, 'DESENVOLVEDOR', 'DBA', '2026-04-21 18:40:00'),
(2, 4, 2, 'ANALISTA_RH', 'SUPERUSER', '2026-04-22 02:55:00'),
(3, 2, 1, 'DBA', 'SUPERUSER', '2026-04-20 22:10:00'),
(4, 5, 3, 'DBA', 'LEITURA', '2026-04-22 08:20:00'),
(5, 1, 2, 'DBA', 'SUPERUSER', '2026-04-22 03:05:00');

INSERT INTO incidentes_auditoria (id_incidente, categoria, descricao, risco, evidencias, veredicto) VALUES
(1, 'ACESSO_FORA_DO_HORARIO', 'Login fora do horario comercial realizado por Carlos Souza no banco financeiro_prod as 03:18.', 'CRITICO', 'CONEXOES_BD.id_conexao=2', 'ESCALONAR_PARA_SEGURANCA'),
(2, 'MULTIPLAS_FALHAS_AUTENTICACAO', 'Tres falhas consecutivas de autenticacao para o usuario Rafael Nunes no banco app_prod.', 'ALTO', 'CONEXOES_BD.id_conexao IN (3,4,5)', 'USUARIO_BLOQUEADO'),
(3, 'CONSULTA_OBJETO_SENSIVEL', 'Consulta ao objeto folha_pagamento identificada em contexto sensivel de auditoria.', 'ALTO', 'AUDITORIA_CONSULTAS.id_evento IN (1,4,5)', 'EM_INVESTIGACAO'),
(4, 'ELEVACAO_INDEVIDA_DE_PRIVILEGIO', 'Usuario Juliana Rocha teve privilegio elevado de ANALISTA_RH para SUPERUSER.', 'CRITICO', 'ALTERACOES_PRIVILEGIOS.id_alt=2', 'NAO_CONFORME'),
(5, 'USO_DE_SUPERUSER', 'Execucao de acoes com perfil SUPERUSER em ambiente financeiro durante a madrugada.', 'CRITICO', 'USUARIOS.id_usuario=2; CONEXOES_BD.id_conexao=2; AUDITORIA_CONSULTAS.id_evento IN (1,6)', 'INCIDENTE_CONFIRMADO');

SELECT setval(pg_get_serial_sequence('perfis_permissao', 'id_perfil'), COALESCE((SELECT MAX(id_perfil) FROM perfis_permissao), 1), true);
SELECT setval(pg_get_serial_sequence('usuarios', 'id_usuario'), COALESCE((SELECT MAX(id_usuario) FROM usuarios), 1), true);
SELECT setval(pg_get_serial_sequence('conexoes_bd', 'id_conexao'), COALESCE((SELECT MAX(id_conexao) FROM conexoes_bd), 1), true);
SELECT setval(pg_get_serial_sequence('auditoria_consultas', 'id_evento'), COALESCE((SELECT MAX(id_evento) FROM auditoria_consultas), 1), true);
SELECT setval(pg_get_serial_sequence('alteracoes_privilegios', 'id_alt'), COALESCE((SELECT MAX(id_alt) FROM alteracoes_privilegios), 1), true);
SELECT setval(pg_get_serial_sequence('incidentes_auditoria', 'id_incidente'), COALESCE((SELECT MAX(id_incidente) FROM incidentes_auditoria), 1), true);

COMMIT;
