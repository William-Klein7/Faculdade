BEGIN;

-- Script de carga massiva para o cenário corporativo da Eletromissoes.
-- Estrategia:
-- 1. Limpa as tabelas para permitir reexecucao controlada.
-- 2. Insere perfis de permissao manualmente.
-- 3. Gera 500 usuarios distribuidos conforme o organograma.
-- 4. Gera milhares de eventos para 90 dias de operacao.
-- 5. Injeta falhas de seguranca propositais para auditoria.

TRUNCATE TABLE
    incidentes_auditoria,
    alteracoes_privilegios,
    auditoria_consultas,
    conexoes_bd,
    usuarios,
    perfis_permissao
RESTART IDENTITY CASCADE;

-- Perfis coerentes com as areas da empresa.
INSERT INTO perfis_permissao (nome_perfil, recurso, tipo_permissao, criticidade) VALUES
('Presidencia_Executiva', 'dw_corporativo', 'LEITURA_ESTRATEGICA', 'ALTA'),
('Operacao_COM', 'scada_operacao', 'MONITORAMENTO_OPERACIONAL', 'ALTA'),
('Engenharia_Rede', 'engenharia_ativos', 'LEITURA_ESCRITA_TECNICA', 'ALTA'),
('Planejamento_Energetico', 'planejamento_expansao', 'ANALISE_E_PLANEJAMENTO', 'ALTA'),
('Gestao_Manutencao', 'manutencao_corporativa', 'GESTAO_DE_OS', 'ALTA'),
('Equipe_Manutencao', 'ativos_campo', 'EXECUCAO_DE_OS', 'MEDIA'),
('DBA', 'cluster_postgresql', 'ADMINISTRACAO_TOTAL', 'CRITICA'),
('TI_Operacoes', 'infraestrutura_ti', 'OPERACAO_E_SUPORTE', 'ALTA'),
('Leitura_Comercial', 'crm_clientes', 'LEITURA_E_ATENDIMENTO', 'MEDIA'),
('Gestao_Comercial', 'crm_clientes', 'GESTAO_COMERCIAL', 'ALTA'),
('Gestao_Financeira', 'erp_financeiro', 'FINANCEIRO_COMPLETO', 'CRITICA'),
('Contabilidade_Analitica', 'contabilidade_corporativa', 'CONTABILIDADE_E_FECHAMENTO', 'ALTA'),
('Estoque_Almoxarifado', 'estoque_corporativo', 'MOVIMENTACAO_DE_ESTOQUE', 'MEDIA'),
('Logistica_Distribuicao', 'logistica_operacional', 'PROGRAMACAO_E_RASTREIO', 'MEDIA'),
('RH_Gestao_Pessoas', 'rh_corporativo', 'GESTAO_DE_PESSOAS', 'CRITICA'),
('Juridico_Corporativo', 'juridico_contratos', 'CONSULTA_PROCESSUAL', 'ALTA'),
('Compliance_Regulatorio', 'compliance_aneel', 'COMPLIANCE_E_REGULACAO', 'CRITICA'),
('Seguranca_Ocupacional', 'sst_corporativo', 'GESTAO_SST', 'ALTA'),
('Seguranca_Patrimonial', 'patrimonial_monitoramento', 'MONITORAMENTO_DE_ACESSO', 'ALTA'),
('Meio_Ambiente', 'ambiental_licencas', 'GESTAO_AMBIENTAL', 'ALTA'),
('Treinamento_Corporativo', 'lms_corporativo', 'TREINAMENTO_E_CERTIFICACAO', 'MEDIA'),
('Pesquisa_Desenvolvimento', 'laboratorio_pd', 'PESQUISA_E_PROTOTIPAGEM', 'ALTA');

DO $$
DECLARE
    v_first_names text[] := ARRAY[
        'Ana', 'Bruno', 'Carla', 'Daniel', 'Eduardo', 'Fernanda', 'Gabriel', 'Helena',
        'Igor', 'Juliana', 'Karen', 'Lucas', 'Marina', 'Nicolas', 'Olivia', 'Paulo',
        'Renata', 'Sergio', 'Talita', 'Vinicius', 'Aline', 'Caio', 'Debora', 'Felipe',
        'Giovana', 'Hugo', 'Isabela', 'Joao', 'Larissa', 'Mateus'
    ];
    v_last_names text[] := ARRAY[
        'Silva', 'Souza', 'Oliveira', 'Santos', 'Pereira', 'Costa', 'Ferreira', 'Rodrigues',
        'Almeida', 'Nascimento', 'Lima', 'Araujo', 'Carvalho', 'Gomes', 'Martins', 'Ribeiro',
        'Alves', 'Barbosa', 'Rocha', 'Dias', 'Melo', 'Freitas', 'Teixeira', 'Correia',
        'Moreira', 'Batista', 'Moura', 'Cardoso', 'Campos', 'Monteiro'
    ];
    v_setores text[] := ARRAY[
        'Presidencia',
        'Centro de Operacao e Monitoramento',
        'Engenharia',
        'Planejamento Energetico e Expansao',
        'Gestao de Manutencao',
        'Turmas de Manutencao',
        'T.I.',
        'Call Center',
        'Comercial e Relacionamento com Clientes',
        'Financeiro',
        'Contabilidade',
        'Almoxarifado',
        'Logistica',
        'RH',
        'Juridico',
        'Regulacao e Compliance',
        'Seguranca do Trabalho',
        'Seguranca Patrimonial',
        'Meio Ambiente e Sustentabilidade',
        'Treinamento / Capacitacao',
        'Pesquisa e Desenvolvimento (P&D)'
    ];
    v_quantidades int[] := ARRAY[
        3, 75, 35, 20, 15, 155, 25, 42, 25, 15, 10, 12, 8, 10, 8, 10, 8, 7, 7, 5, 5
    ];
    v_perfis text[] := ARRAY[
        'Presidencia_Executiva',
        'Operacao_COM',
        'Engenharia_Rede',
        'Planejamento_Energetico',
        'Gestao_Manutencao',
        'Equipe_Manutencao',
        'TI_Operacoes',
        'Leitura_Comercial',
        'Gestao_Comercial',
        'Gestao_Financeira',
        'Contabilidade_Analitica',
        'Estoque_Almoxarifado',
        'Logistica_Distribuicao',
        'RH_Gestao_Pessoas',
        'Juridico_Corporativo',
        'Compliance_Regulatorio',
        'Seguranca_Ocupacional',
        'Seguranca_Patrimonial',
        'Meio_Ambiente',
        'Treinamento_Corporativo',
        'Pesquisa_Desenvolvimento'
    ];
    v_sector_idx int;
    v_i int;
    v_j int;
    v_user_seq int := 0;
    v_nome text;
    v_login text;
    v_primeiro_nome text;
    v_sobrenome_1 text;
    v_sobrenome_2 text;
    v_setor text;
    v_profile_name text;
    v_profile_id int;
    v_status text;
    v_days_back int;
    v_base_ts timestamp;
    v_event_ts timestamp;
    v_conns int;
    v_queries int;
    v_ip text;
    v_banco text;
    v_status_login text;
    v_tipo_acao text;
    v_objeto_bd text;
    v_criticidade text;
    v_objetos text[];
    v_tipos text[];
    v_ti_ids int[];
    v_manut_ids int[];
    v_after_hours_ids int[];
    v_fail_ids int[];
    v_target_ids int[];
    v_executor_id int;
    v_target_id int;
    v_anomaly_ts timestamp;
    r_user record;
BEGIN
    PERFORM setseed(0.42042);

    -- Gera exatamente 500 usuarios respeitando o organograma informado.
    FOR v_sector_idx IN 1..array_length(v_setores, 1) LOOP
        v_setor := v_setores[v_sector_idx];

        FOR v_i IN 1..v_quantidades[v_sector_idx] LOOP
            v_user_seq := v_user_seq + 1;

            v_primeiro_nome := v_first_names[1 + ((v_user_seq - 1) % array_length(v_first_names, 1))];
            v_sobrenome_1 := v_last_names[1 + ((v_user_seq * 3 - 1) % array_length(v_last_names, 1))];
            v_sobrenome_2 := v_last_names[1 + ((v_user_seq * 7 - 1) % array_length(v_last_names, 1))];
            v_nome := v_primeiro_nome || ' ' || v_sobrenome_1 || ' ' || v_sobrenome_2;
            v_login := lower(left(v_primeiro_nome, 1) || regexp_replace(v_sobrenome_1, '[^a-zA-Z0-9]', '', 'g') || lpad(v_user_seq::text, 3, '0'));

            v_profile_name := v_perfis[v_sector_idx];
            IF v_setor = 'T.I.' AND v_i <= 6 THEN
                v_profile_name := 'DBA';
            END IF;

            SELECT id_perfil
            INTO v_profile_id
            FROM perfis_permissao
            WHERE nome_perfil = v_profile_name;

            v_status := CASE
                WHEN v_setor = 'Turmas de Manutencao' AND v_i IN (17, 68, 121, 149) THEN 'BLOQUEADO'
                WHEN v_setor = 'Call Center' AND v_i IN (11, 37) THEN 'INATIVO'
                WHEN v_setor = 'Logistica' AND v_i = 8 THEN 'INATIVO'
                ELSE 'ATIVO'
            END;

            INSERT INTO usuarios (nome, login, setor, perfil, status)
            VALUES (v_nome, v_login, v_setor, v_profile_id, v_status);
        END LOOP;
    END LOOP;

    -- Gera historico de 90 dias com milhares de conexoes e consultas.
    FOR r_user IN
        SELECT u.id_usuario, u.login, u.setor, u.status, p.nome_perfil
        FROM usuarios u
        JOIN perfis_permissao p ON p.id_perfil = u.perfil
        ORDER BY u.id_usuario
    LOOP
        v_conns := 10 + floor(random() * 16)::int;

        FOR v_i IN 1..v_conns LOOP
            v_days_back := floor(random() * 90)::int;

            IF random() < 0.94 THEN
                v_base_ts := date_trunc('day', now() - make_interval(days => v_days_back))
                    + time '07:00'
                    + make_interval(
                        hours => floor(random() * 12)::int,
                        mins => floor(random() * 60)::int,
                        secs => floor(random() * 60)::int
                    );
            ELSE
                -- FALHA DE SEGURANCA INJETADA: parte das conexoes ocorre na madrugada.
                v_base_ts := date_trunc('day', now() - make_interval(days => v_days_back))
                    + make_interval(
                        hours => floor(random() * 5)::int,
                        mins => floor(random() * 60)::int,
                        secs => floor(random() * 60)::int
                    );
            END IF;

            v_banco := CASE
                WHEN r_user.setor IN ('Centro de Operacao e Monitoramento', 'Engenharia', 'Planejamento Energetico e Expansao', 'Gestao de Manutencao', 'Turmas de Manutencao') THEN 'operacao_energia'
                WHEN r_user.setor = 'T.I.' THEN 'admin_postgres'
                WHEN r_user.setor IN ('Call Center', 'Comercial e Relacionamento com Clientes') THEN 'crm_clientes'
                WHEN r_user.setor IN ('Financeiro', 'Contabilidade', 'Presidencia') THEN 'erp_corporativo'
                WHEN r_user.setor = 'RH' THEN 'rh_corporativo'
                WHEN r_user.setor IN ('Juridico', 'Regulacao e Compliance') THEN 'compliance_aneel'
                WHEN r_user.setor IN ('Seguranca do Trabalho', 'Seguranca Patrimonial', 'Meio Ambiente e Sustentabilidade') THEN 'ssma_corporativo'
                WHEN r_user.setor IN ('Treinamento / Capacitacao', 'Pesquisa e Desenvolvimento (P&D)') THEN 'inovacao_lab'
                ELSE 'suprimentos_logistica'
            END;

            v_ip := format(
                '10.%s.%s.%s',
                10 + (r_user.id_usuario % 20),
                1 + floor(random() * 200)::int,
                10 + floor(random() * 200)::int
            );

            v_status_login := CASE
                WHEN r_user.status = 'BLOQUEADO' AND random() < 0.85 THEN 'FALHA'
                WHEN r_user.status = 'INATIVO' AND random() < 0.60 THEN 'FALHA'
                WHEN random() < 0.07 THEN 'FALHA'
                ELSE 'SUCESSO'
            END;

            INSERT INTO conexoes_bd (id_usuario, data_hora_login, ip_origem, banco, status_login)
            VALUES (r_user.id_usuario, v_base_ts, v_ip, v_banco, v_status_login);

            IF v_status_login = 'SUCESSO' THEN
                v_queries := 1 + floor(random() * 4)::int;

                CASE r_user.setor
                    WHEN 'Presidencia' THEN
                        v_objetos := ARRAY['kpi_geracao', 'balanco_gerencial', 'contratos_energia', 'inadimplencia_macro'];
                        v_tipos := ARRAY['SELECT', 'SELECT', 'SELECT', 'UPDATE'];
                    WHEN 'Centro de Operacao e Monitoramento' THEN
                        v_objetos := ARRAY['telemetria_usinas', 'eventos_scada', 'subestacoes', 'alarmistica'];
                        v_tipos := ARRAY['SELECT', 'SELECT', 'UPDATE', 'SELECT'];
                    WHEN 'Engenharia' THEN
                        v_objetos := ARRAY['ativos_subestacao', 'projetos_expansao', 'topologia_rede', 'inspecoes_tecnicas'];
                        v_tipos := ARRAY['SELECT', 'UPDATE', 'SELECT', 'INSERT'];
                    WHEN 'Planejamento Energetico e Expansao' THEN
                        v_objetos := ARRAY['carga_prevista', 'expansao_rede', 'projecoes_demanda', 'contratos_energia'];
                        v_tipos := ARRAY['SELECT', 'SELECT', 'INSERT', 'UPDATE'];
                    WHEN 'Gestao de Manutencao' THEN
                        v_objetos := ARRAY['ordens_servico', 'backlog_manutencao', 'planos_preventivos', 'ativos_subestacao'];
                        v_tipos := ARRAY['SELECT', 'UPDATE', 'INSERT', 'SELECT'];
                    WHEN 'Turmas de Manutencao' THEN
                        v_objetos := ARRAY['ordens_servico', 'ativos_campo', 'rotas_manutencao', 'inspecoes_campo'];
                        v_tipos := ARRAY['SELECT', 'UPDATE', 'SELECT', 'INSERT'];
                    WHEN 'T.I.' THEN
                        v_objetos := ARRAY['usuarios_sistema', 'roles_postgres', 'jobs_backup', 'configuracoes_cluster'];
                        v_tipos := ARRAY['SELECT', 'ALTER', 'GRANT', 'UPDATE'];
                    WHEN 'Call Center' THEN
                        v_objetos := ARRAY['clientes', 'atendimentos', 'faturas_cliente', 'medidores'];
                        v_tipos := ARRAY['SELECT', 'SELECT', 'UPDATE', 'INSERT'];
                    WHEN 'Comercial e Relacionamento com Clientes' THEN
                        v_objetos := ARRAY['contratos_cliente', 'campanhas_comerciais', 'inadimplencia_clientes', 'faturas_cliente'];
                        v_tipos := ARRAY['SELECT', 'UPDATE', 'SELECT', 'INSERT'];
                    WHEN 'Financeiro' THEN
                        v_objetos := ARRAY['contas_pagar', 'contas_receber', 'fluxo_caixa', 'fornecedores'];
                        v_tipos := ARRAY['SELECT', 'UPDATE', 'SELECT', 'INSERT'];
                    WHEN 'Contabilidade' THEN
                        v_objetos := ARRAY['lancamentos_contabeis', 'centros_custo', 'balancetes', 'ativo_imobilizado'];
                        v_tipos := ARRAY['SELECT', 'INSERT', 'UPDATE', 'SELECT'];
                    WHEN 'Almoxarifado' THEN
                        v_objetos := ARRAY['estoque_itens', 'movimentacoes_estoque', 'requisicoes_material', 'fornecedores'];
                        v_tipos := ARRAY['SELECT', 'UPDATE', 'INSERT', 'SELECT'];
                    WHEN 'Logistica' THEN
                        v_objetos := ARRAY['rotas_entrega', 'frota_veiculos', 'agendamentos_entrega', 'movimentacoes_estoque'];
                        v_tipos := ARRAY['SELECT', 'UPDATE', 'SELECT', 'INSERT'];
                    WHEN 'RH' THEN
                        v_objetos := ARRAY['folha_pagamento', 'beneficios', 'ferias_colaboradores', 'ponto_eletronico'];
                        v_tipos := ARRAY['SELECT', 'UPDATE', 'SELECT', 'INSERT'];
                    WHEN 'Juridico' THEN
                        v_objetos := ARRAY['processos_judiciais', 'contratos_fornecedores', 'pareceres_juridicos', 'passivos_contingentes'];
                        v_tipos := ARRAY['SELECT', 'INSERT', 'UPDATE', 'SELECT'];
                    WHEN 'Regulacao e Compliance' THEN
                        v_objetos := ARRAY['relatorios_aneel', 'obrigacoes_regulatorias', 'nao_conformidades', 'trilha_auditoria'];
                        v_tipos := ARRAY['SELECT', 'SELECT', 'UPDATE', 'INSERT'];
                    WHEN 'Seguranca do Trabalho' THEN
                        v_objetos := ARRAY['incidentes_sst', 'epi_colaboradores', 'treinamentos_nr', 'permissoes_trabalho'];
                        v_tipos := ARRAY['SELECT', 'UPDATE', 'INSERT', 'SELECT'];
                    WHEN 'Seguranca Patrimonial' THEN
                        v_objetos := ARRAY['controle_acesso', 'cftv_eventos', 'rondas_patrimoniais', 'visitantes'];
                        v_tipos := ARRAY['SELECT', 'SELECT', 'INSERT', 'UPDATE'];
                    WHEN 'Meio Ambiente e Sustentabilidade' THEN
                        v_objetos := ARRAY['licencas_ambientais', 'emissoes', 'condicionantes', 'relatorios_sustentabilidade'];
                        v_tipos := ARRAY['SELECT', 'UPDATE', 'INSERT', 'SELECT'];
                    WHEN 'Treinamento / Capacitacao' THEN
                        v_objetos := ARRAY['cursos_internos', 'trilhas_aprendizado', 'certificacoes', 'presencas_treinamento'];
                        v_tipos := ARRAY['SELECT', 'INSERT', 'UPDATE', 'SELECT'];
                    ELSE
                        v_objetos := ARRAY['projetos_pd', 'experimentos_laboratorio', 'indicadores_inovacao', 'orcamentos_pd'];
                        v_tipos := ARRAY['SELECT', 'INSERT', 'UPDATE', 'SELECT'];
                END CASE;

                FOR v_j IN 1..v_queries LOOP
                    v_event_ts := v_base_ts + make_interval(mins => 1 + floor(random() * 180)::int);
                    v_objeto_bd := v_objetos[1 + floor(random() * array_length(v_objetos, 1))::int];
                    v_tipo_acao := v_tipos[1 + floor(random() * array_length(v_tipos, 1))::int];

                    v_criticidade := CASE
                        WHEN v_objeto_bd IN ('folha_pagamento', 'roles_postgres', 'configuracoes_cluster', 'passivos_contingentes', 'relatorios_aneel') THEN 'CRITICA'
                        WHEN v_objeto_bd IN ('contas_pagar', 'contas_receber', 'fluxo_caixa', 'contratos_cliente', 'contratos_energia') THEN 'ALTA'
                        WHEN v_tipo_acao IN ('ALTER', 'GRANT', 'DELETE') THEN 'ALTA'
                        ELSE 'MEDIA'
                    END;

                    INSERT INTO auditoria_consultas (id_usuario, data_hora, tipo_acao, objeto_bd, criticidade)
                    VALUES (r_user.id_usuario, v_event_ts, v_tipo_acao, v_objeto_bd, v_criticidade);
                END LOOP;
            END IF;
        END LOOP;
    END LOOP;

    SELECT array_agg(id_usuario ORDER BY id_usuario)
    INTO v_manut_ids
    FROM usuarios
    WHERE setor = 'Turmas de Manutencao';

    SELECT array_agg(id_usuario ORDER BY id_usuario)
    INTO v_ti_ids
    FROM usuarios
    WHERE setor = 'T.I.';

    SELECT array_agg(id_usuario ORDER BY id_usuario)
    INTO v_after_hours_ids
    FROM usuarios
    WHERE setor IN ('Presidencia', 'Financeiro', 'T.I.')
      AND status = 'ATIVO';

    SELECT array_agg(id_usuario ORDER BY id_usuario)
    INTO v_fail_ids
    FROM usuarios
    WHERE (setor = 'Turmas de Manutencao' AND status = 'BLOQUEADO')
       OR setor = 'Call Center';

    SELECT array_agg(id_usuario ORDER BY id_usuario)
    INTO v_target_ids
    FROM usuarios
    WHERE setor IN ('Call Center', 'Financeiro', 'Almoxarifado', 'Logistica');

    -- FALHA DE SEGURANCA INJETADA: logins explicitos na madrugada para perfis sensiveis.
    FOR v_i IN 1..6 LOOP
        EXIT WHEN v_after_hours_ids IS NULL OR v_i > array_length(v_after_hours_ids, 1);
        v_anomaly_ts := date_trunc('day', now() - make_interval(days => v_i * 4))
            + time '03:00'
            + make_interval(mins => v_i * 6);

        INSERT INTO conexoes_bd (id_usuario, data_hora_login, ip_origem, banco, status_login)
        VALUES (
            v_after_hours_ids[v_i],
            v_anomaly_ts,
            format('172.20.10.%s', 20 + v_i),
            CASE
                WHEN EXISTS (SELECT 1 FROM usuarios WHERE id_usuario = v_after_hours_ids[v_i] AND setor = 'Financeiro') THEN 'erp_corporativo'
                WHEN EXISTS (SELECT 1 FROM usuarios WHERE id_usuario = v_after_hours_ids[v_i] AND setor = 'T.I.') THEN 'admin_postgres'
                ELSE 'dw_corporativo'
            END,
            'SUCESSO'
        );
    END LOOP;

    -- FALHA DE SEGURANCA INJETADA: equipe de campo tentando consultar folha_pagamento.
    FOR v_i IN 1..12 LOOP
        EXIT WHEN v_manut_ids IS NULL OR v_i > array_length(v_manut_ids, 1);
        v_anomaly_ts := date_trunc('day', now() - make_interval(days => 2 + v_i))
            + time '02:15'
            + make_interval(mins => v_i * 4);

        INSERT INTO conexoes_bd (id_usuario, data_hora_login, ip_origem, banco, status_login)
        VALUES (v_manut_ids[v_i], v_anomaly_ts, format('10.88.40.%s', v_i), 'rh_corporativo', 'SUCESSO');

        INSERT INTO auditoria_consultas (id_usuario, data_hora, tipo_acao, objeto_bd, criticidade)
        VALUES (v_manut_ids[v_i], v_anomaly_ts + interval '2 minutes', 'SELECT', 'folha_pagamento', 'CRITICA');
    END LOOP;

    -- FALHA DE SEGURANCA INJETADA: repetidas falhas de autenticacao no mesmo usuario.
    FOR v_i IN 1..4 LOOP
        EXIT WHEN v_fail_ids IS NULL OR v_i > array_length(v_fail_ids, 1);
        FOR v_j IN 1..6 LOOP
            v_anomaly_ts := date_trunc('day', now() - make_interval(days => 1 + v_i))
                + time '01:20'
                + make_interval(mins => (v_i * 8) + v_j);

            INSERT INTO conexoes_bd (id_usuario, data_hora_login, ip_origem, banco, status_login)
            VALUES (v_fail_ids[v_i], v_anomaly_ts, format('200.180.50.%s', (v_i * 10) + v_j), 'admin_postgres', 'FALHA');
        END LOOP;
    END LOOP;

    -- FALHA DE SEGURANCA INJETADA: TI concede perfil DBA para contas comuns sem justificativa.
    FOR v_i IN 1..4 LOOP
        EXIT WHEN v_ti_ids IS NULL OR v_target_ids IS NULL;
        EXIT WHEN v_i > array_length(v_ti_ids, 1) OR v_i > array_length(v_target_ids, 1);

        v_executor_id := v_ti_ids[v_i];
        v_target_id := v_target_ids[v_i];
        v_anomaly_ts := date_trunc('day', now() - make_interval(days => 5 + v_i))
            + time '22:30'
            + make_interval(mins => v_i * 5);

        INSERT INTO alteracoes_privilegios (
            id_usuario_alvo,
            id_usuario_executor,
            privilegio_anterior,
            privilegio_novo,
            data_hora
        )
        SELECT
            v_target_id,
            v_executor_id,
            pp.nome_perfil,
            'DBA',
            v_anomaly_ts
        FROM usuarios u
        JOIN perfis_permissao pp ON pp.id_perfil = u.perfil
        WHERE u.id_usuario = v_target_id;

        INSERT INTO auditoria_consultas (id_usuario, data_hora, tipo_acao, objeto_bd, criticidade)
        VALUES (v_executor_id, v_anomaly_ts, 'GRANT', 'role_dba', 'CRITICA');

        UPDATE usuarios
        SET perfil = (SELECT id_perfil FROM perfis_permissao WHERE nome_perfil = 'DBA')
        WHERE id_usuario = v_target_id;
    END LOOP;

    INSERT INTO incidentes_auditoria (categoria, descricao, risco, evidencias, veredicto) VALUES
    (
        'ACESSO_FORA_DO_HORARIO',
        'Foram identificados logins em horario de madrugada por usuarios da Presidencia, Financeiro e T.I. no ambiente da Eletromissoes.',
        'ALTO',
        format('usuarios=%s; janela=03h; tabela=conexoes_bd', coalesce(array_to_string(v_after_hours_ids[1:6], ','), 'n/d')),
        'EM_INVESTIGACAO'
    ),
    (
        'ACESSO_INDEVIDO_A_DADO_SENSIVEL',
        'Usuarios de Turmas de Manutencao executaram SELECT em folha_pagamento sem necessidade funcional.',
        'CRITICO',
        format('usuarios=%s; objeto=folha_pagamento; setor=Turmas de Manutencao', coalesce(array_to_string(v_manut_ids[1:12], ','), 'n/d')),
        'INCIDENTE_CONFIRMADO'
    ),
    (
        'ESCALONAMENTO_INDEVIDO_DE_PRIVILEGIO',
        'Contas comuns receberam privilegio DBA por executores da T.I. sem justificativa registrada.',
        'CRITICO',
        format('executores_ti=%s; alvos=%s; origem=alteracoes_privilegios', coalesce(array_to_string(v_ti_ids[1:4], ','), 'n/d'), coalesce(array_to_string(v_target_ids[1:4], ','), 'n/d')),
        'NAO_CONFORME'
    ),
    (
        'MULTIPLAS_FALHAS_AUTENTICACAO',
        'Foram registradas varias tentativas de autenticacao com status FALHA para os mesmos usuarios em curto intervalo.',
        'ALTO',
        format('usuarios=%s; repeticoes=6_por_usuario; origem=conexoes_bd', coalesce(array_to_string(v_fail_ids[1:4], ','), 'n/d')),
        'MONITORAMENTO_REFORCADO'
    ),
    (
        'RISCO_INTERNO',
        'O conjunto de eventos indica fragilidade de segregacao de funcao e monitoramento de acessos privilegiados.',
        'CRITICO',
        'correlacao=conexoes_bd+auditoria_consultas+alteracoes_privilegios',
        'ESCALONAR_PARA_COMITE_DE_SEGURANCA'
    );

    RAISE NOTICE 'Carga Eletromissoes concluida: % usuarios, % conexoes, % eventos de auditoria, % alteracoes de privilegio, % incidentes.',
        (SELECT count(*) FROM usuarios),
        (SELECT count(*) FROM conexoes_bd),
        (SELECT count(*) FROM auditoria_consultas),
        (SELECT count(*) FROM alteracoes_privilegios),
        (SELECT count(*) FROM incidentes_auditoria);
END $$;

COMMIT;
