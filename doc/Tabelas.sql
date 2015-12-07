CREATE TABLE IF NOT EXISTS Operadora(
    cnpj		BIGINT		UNSIGNED	NOT NULL,
    nome		VARCHAR(30)	NOT NULL,
    PRIMARY KEY(cnpj)
);

CREATE TABLE IF NOT EXISTS Pessoa(
    id			INT		UNSIGNED	NOT NULL,
    documento		VARCHAR(18)	NOT NULL,
    nome		VARCHAR(60)	NOT NULL,
    endereco		VARCHAR(60)	NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE IF NOT EXISTS Plano(
    id			MEDIUMINT	UNSIGNED	NOT NULL,
    tipo		TINYINT		UNSIGNED	NOT NULL,
    cadencia		SMALLINT	UNSIGNED,
    custo_cadencia	FLOAT(6,4),
    operadora		BIGINT		UNSIGNED	NOT NULL,
    CONSTRAINT		fk_plano_operadora	foreign key (operadora) references Operadora(cnpj),
    PRIMARY KEY (id)
);


CREATE TABLE IF NOT EXISTS Central(
    id			SMALLINT	UNSIGNED	NOT NULL,
    regiao		TINYINT		UNSIGNED,
    cap_ligacoes	SMALLINT	UNSIGNED,
    operadora		BIGINT		UNSIGNED	NOT NULL,
    CONSTRAINT		fk_central_operadora	foreign key (operadora) references Operadora(cnpj),
    PRIMARY KEY (id)
);


CREATE TABLE IF NOT EXISTS ERB(
    id			SMALLINT	UNSIGNED	NOT NULL,
    capacidade		SMALLINT	UNSIGNED,
    area		TINYINT		UNSIGNED,
    latitude		FLOAT(8,6),
    longitude		FLOAT(8,6),
    qos			BIT(1),
    operadora		BIGINT		UNSIGNED	NOT NULL,
    CONSTRAINT		fk_erb_operadora	foreign key (operadora) references Operadora(cnpj),
    PRIMARY KEY(id)
);


CREATE TABLE IF NOT EXISTS Numero(
    id			BIGINT		UNSIGNED	NOT NULL,
    n_telefone		VARCHAR(15)			NOT NULL,
    credito		FLOAT(7,5),
    operadora		BIGINT		UNSIGNED	NOT NULL,
    CONSTRAINT		fk_numero_operadora	foreign key (operadora) references Operadora(cnpj),
    PRIMARY KEY(id)
);


CREATE TABLE IF NOT EXISTS Contrato(
    id			BIGINT		UNSIGNED	NOT NULL,
    end_cobranca	VARCHAR(60),
    fidelizacao		BIT(1),
    vigencia_i   	DATETIME,
    vigencia_t   	DATETIME,
    plano		MEDIUMINT	UNSIGNED	NOT NULL,
    numero		BIGINT		UNSIGNED	NOT NULL,
    CONSTRAINT		fk_contrato_plano	foreign key (plano) references Plano(id),
    CONSTRAINT		fk_contrato_numero	foreign key (numero) references Numero(id),
    PRIMARY KEY (id)
);


CREATE TABLE IF NOT EXISTS Chamada(
    id			BIGINT		UNSIGNED	NOT NULL,
    hora		DATETIME,
    origem		TINYINT		UNSIGNED	NOT NULL,
    destino		TINYINT		UNSIGNED	NOT NULL,
    duracao		SMALLINT	UNSIGNED	NOT NULL,
    plano		MEDIUMINT	UNSIGNED	NOT NULL,
    CONSTRAINT		fk_chamada_plano	foreign key (plano) references Plano(id),
    PRIMARY KEY (id)
);


CREATE TABLE IF NOT EXISTS Telefone(
    id			BIGINT		UNSIGNED	NOT NULL,	
    pessoa		INT		UNSIGNED	NOT NULL,
    CONSTRAINT		fk_telefone_pessoa	foreign key (pessoa) references Pessoa(id),
    IMEI		BIGINT		UNSIGNED,
    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS Chip(
    id			BIGINT		UNSIGNED	NOT NULL,
    fk_erb		SMALLINT	UNSIGNED	NOT NULL	references ERB(id),
    ICCID		BIGINT		UNSIGNED	NOT NULL,
    numero		BIGINT		UNSIGNED	NOT NULL,
    telefone		BIGINT		UNSIGNED	NOT NULL,
    CONSTRAINT		fk_chip_numero		foreign key (numero) references Numero(id),
    CONSTRAINT		fk_chip_telefone  	foreign key (telefone)references Telefone(id),
    PRIMARY KEY (id)
);
