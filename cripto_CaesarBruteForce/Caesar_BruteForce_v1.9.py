#!/usr/bin/python3
# -*- coding: utf-8 -*-

instala_requisitos=[
   'pyfiglet',
   'colorama',
   'pyenchant'
]

import os
import enchant
from pyfiglet import Figlet
from colorama import Fore, Back, Style
from unicodedata import normalize

# FUNÇÕES
def dasegArt():
    custom_fig = Figlet(font='digital')
    print(Fore.RED + custom_fig.renderText('....CaesarBruteForce_v1.9....'))
    custom_fig = Figlet(font='cosmic')
    print(Style.DIM + custom_fig.renderText('  DASEG'))
    custom_fig = Figlet(font='digital')
    print(Style.NORMAL + custom_fig.renderText('..Developed by PsyDeciphers..'))

def encryptCaesar(string, shift): # Realiza criptografia de Cesar
# https://www.thecrazyprogrammer.com/2018/05/caesar-cipher-in-python.html
    cipher = ''
    for char in string: 
        if char == ' ':
            cipher = cipher + char
        elif char.isupper():
            cipher = cipher + chr((ord(char) + shift - 65) % 26 + 65)
        else:
            cipher = cipher + chr((ord(char) + shift - 97) % 26 + 97)
    return cipher

def bfCaesar(encryptedWord): # Função que realiza força bruta em palavra criptografada
    letras = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    dic = enchant.Dict("pt_BR") # Verifica se a palavra existe no dicionário português
    with open('resultados_bfCaesar.txt', 'w') as resultados:
        for chave in range(len(letras)):
            resultado = ''
            for letra in encryptedWord.upper():          
                if letra in letras:
                    num = letras.find(letra)
                    num = num - chave
                    if num < 0:
                        num = num + len(letras)
                    resultado = resultado + letras[num]
                else:
                    resultado = resultado + letra
            resultados.write("%s\n" % resultado.lower())
            if dic.check(resultado) == True:
                print(Fore.GREEN)
                print ('Chave #%s: %s <--- Palavra encontrada!' % (chave, resultado))
                print(Fore.RED)
            else:
                print ('Chave #%s: %s' % (chave, resultado))
        resultados.close()
    return 0

def cls(): # Função para limpar a tela
    os.system('clear') or None

def removeAcentos(texto):
    return normalize('NFKD', texto).encode('ASCII', 'ignore').decode('ASCII')

# FLUXO PRINCIPAL 
loop = True
while loop:
    dasegArt()
    escolha = int(input('Escolha uma opção:\n1- Criptografar uma palavra com Cesar \n2- Força bruta em arquivo de texto \n3- Limpar tela \n4- Sair\n\nSua escolha? ' ))
    cls() 
    if escolha==1:     
        dasegArt()
        print ('Opção escolhida: Criptografar uma palavra com Cesar\n')
        textoClaro = input('Insira uma palavra para criptografar: ')
        textoClaro = textoClaro.replace(" ","")
        s = int(input('\nEscolha a chave entre 1~25: '))
        encrypted = encryptCaesar(removeAcentos(textoClaro), s)
        print ('\nPalavra criptografada: %s' % (encrypted));
        gravar = input('\nDeseja salvar no arquivo palavraCifradaCaesar.txt (S/N)? ')
        if gravar.upper() == 'S':
            saida = open('palavraCifradaCaesar.txt', 'w')
            saida.write(encrypted)
            saida.close()

    elif escolha==2:
        dasegArt()
        print ('Opção escolhida: Força bruta em arquivo de texto \n')
        arquivoEntrada = open('palavraCifradaCaesar.txt', 'r')
        encryptedWord = arquivoEntrada.read()
        arquivoEntrada.close()
        bfCaesar(encryptedWord)

    elif escolha==3:
        cls()

    elif escolha==4:
        print ('Fechando...')
        loop=False

    else: # Qualquer entrada fora do intervalo de 1~4 retornará a mesagem de erro
        print('Opção errada! Tente novamente.\n')
