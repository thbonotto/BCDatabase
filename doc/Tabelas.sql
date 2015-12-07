CREATE TABLE Operadora{
    cnpj		BIGINT		UNSIGNED	NOT NULL,
    nome		VARCHAR(30)	NOT NULL,
    PRIMARY KEY(cnpj)
};

CREATE TABLE Pessoa{
    id			INT		UNSIGNED	NOT NULL,
    documento		VARCHAR(18)	NOT NULL,
    nome		VARCHAR(60)	NOT NULL,
    endereco		VARCHAR(60)	NOT NULL,
    PRIMARY KEY(id)
};

CREATE TABLE Plano{
    id			MEDIUMINT	UNSIGNED	NOT NULL,
    tipo		TINYINT		UNSIGNED	NOT NULL,
    cadencia		SMALLINT	UNSIGNED,
    custo_cadencia	FLOAT(6,4),
    fk_operadora	BIGINT		UNSIGNED	NOT NULL	references Operadora(cnpj),
    PRIMARY KEY (id)
};


CREATE TABLE Central{
    id			SMALLINT	UNSIGNED	NOT NULL,
    regiao		TINYINT		UNSIGNED,
    cap_ligacoes	SMALLINT	UNSIGNED,
    fk_operadora	BIGINT		UNSIGNED	NOT NULL	references Operadora(cnpj),
    PRIMARY KEY (id)
};


CREATE TABLE ERB{
    id			SMALLINT	UNSIGNED	NOT NULL,
    capacidade		SMALLINT	UNSIGNED,
    area		TINYINT		UNSIGNED,
    latitude		FLOAT(8,6),
    longitude		FLOAT(8,6),
    qos			BIT(1),
    fk_operadora	BIGINT		UNSIGNED	NOT NULL	references Operadora(cnpj),
    PRIMARY KEY(id)
};


CREATE TABLE Numero{
    id			BIGINT		UNSIGNED	NOT NULL,
    n_telefone		VARCHAR(15)			NOT NULL,
    credito		FLOAT(7,5),
    fk_operadora	BIGINT		UNSIGNED	NOT NULL	references Operadora(cnpj),
    PRIMARY KEY(id)
};


CREATE TABLE Contrato{
    id			BIGINT		UNSIGNED	NOT NULL,
    end_cobranca	VARCHAR(60),
    fidelizacao		BIT(1),
    vigencia_i   	DATATIME(0),
    vigencia_t   	DATATIME(0),
    fk_plano 		MEDIUMINT	UNSIGNED	NOT NULL	references Plano(id),
    fk_numero		BIGINT		UNSIGNED	NOT NULL	references Numero(id),
    PRIMARY KEY (id)
};


CREATE TABLE Chamada{
    id			BIGINT		UNSIGNED	NOT NULL,
    hora		DATATIME(3),
    origem		TINYINT		UNSIGNED	NOT NULL,
    destino		TINYINT		UNSIGNED	NOT NULL,
    duracao		SMALLINT	UNSIGNED	NOT NULL,
    fk_plano	 	MEDIUMINT	UNSIGNED	NOT NULL	references Plano(id),	
    PRIMARY KEY (id)
};


CREATE TABLE Telefone{
    id			BIGINT		UNSIGNED	NOT NULL,	
    fk_pessoa		INT		UNSIGNED	NOT NULL	references Pessoa(id),
    IMEI		BIGINT		UNSIGNED,
    PRIMARY KEY (id)
};

CREATE TABLE Chip{
    id			BIGINT		UNSIGNED	NOT NULL,
    fk_erb		SMALLINT	UNSIGNED	NOT NULL	references ERB(id),
    ICCID		BIGINT		UNSIGNED	NOT NULL,
    fk_numero		BIGINT		UNSIGNED	NOT NULL	references Numero(id),
    fk_telefone		BIGINT		UNSIGNED	NOT NULL	references Telefone(id),
    PRIMARY KEY (id)
};
