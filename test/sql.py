#!/usr/bin/env python
# -*- coding: utf-8 -*-

# · Documentação de referência: https://dev.mysql.com/doc/connector-python/en/connector-python-example-connecting.html
import mysql.connector
from random import randint

areas = ['Física', 'Química', 'Medicina', 'Literatura', 'Paz', 'Economia']
cnx = mysql.connector.connect(user='bcd', password='f4UXZpFr', host='200.135.233.38', database='producao')
cursor = cnx.cursor()

# Limpeza
cursor.execute('delete from contrato')
cursor.execute('delete from plano;')
cursor.execute('delete from operadora;')
cursor.execute('delete from pessoa;')

# Operadora
for operadora in areas:
  sql = "INSERT INTO operadora(nome, cnpj) VALUES ('" + operadora + "', '" + str(randint(1000, 9999)) + "');"
  print sql
  cursor.execute(sql)

# Plano
for operadora in areas:
  for ano in range(1901, 2016):
    sql = "INSERT INTO plano(operadora, vigenciaInicio, tipo) VALUES ((SELECT id FROM operadora WHERE operadora.nome = '" + operadora + "'), '"+ str(ano) + "-01-01', 'pós-pago')"
    print sql
    cursor.execute(sql)

# Pessoas + Contratos
arquivo = open('pessoas.csv', 'r')
for linha in arquivo.readlines():
  tokens = linha.strip().split(';')
  # https://en.wikipedia.org/wiki/Category:Nobel_laureates_with_multiple_Nobel_awards
  # Marie Curie recebeu 2 prêmios;
  # International Committee of the Red Cross, 3;
  # Linus Pauling, 2;
  # Frederick Sanger, 2;
  # John Bardeen, 2;
  # United Nations High Commissioner for Refugees, 3.
  # Documento duplicado em pessoas.csv.
  sql = "INSERT IGNORE INTO pessoa(nome, documento) VALUES ('" + tokens[1] + "', '" + tokens[2] + "');"
  print sql
  cursor.execute(sql)
  try:
    sql = "INSERT INTO contrato(contratado, contratante, plano) VALUES ((SELECT id FROM operadora WHERE nome = '" + tokens[3] + "'), (SELECT id FROM pessoa WHERE nome = '" + tokens[1] + "'), (SELECT id FROM plano WHERE vigenciaInicio = '" + tokens[0] + "-01-01' AND operadora = (SELECT id FROM operadora WHERE nome = '" + tokens[3] + "')));"
    print sql
    cursor.execute(sql)
  except:
    print 'falhou' 

arquivo.close()

cnx.commit()
cursor.close()
cnx.close()
