import sys

# NÃO DEIXAR RODAR EM VERSÃO INFERIOR AO PYTHON 3
if sys.version_info[0] < 3:
    raise Exception("E necessario Python 3 ou versao posterior para rodar o programa!")
	
from bs4 import BeautifulSoup
import requests
import requests.exceptions
from urllib.parse import urlsplit
from collections import deque
import re

# FUNÇÕES
def filtrarNumeros(conteudoPagina):
	# FILTRA NÚMEROS ENCONTRADOS NÁ PÁGINA PARA REMOVER OS LIXOS
	numerosEncontrados = re.findall(r"[\'\+\(]?\d+[\(\d\)\ \-]*[\d\']+", conteudoPagina)
	numerosValidos = []

	for d in numerosEncontrados:
		temp = re.sub(r"[\+\ \-\(\)+]", "", d)
		if not (len(str(temp)) > 13 or len(str(temp)) < 10):
			if '+' in d or '(' in d or ')' in d:
				numerosValidos.append(d)
	return numerosValidos

def extraiBase(url):
	# EXTRAI A URL BASE PARA SER COMPARADA DEPOIS
	partes = urlsplit(url)
	base_url = "{0.netloc}".format(partes) + '/'
	return base_url	
	
def limpaUrl(url):
	# LIMPA A URL ENCONTRADA PARA EVITAR DUPLICIDADE 
	if re.match(r"(https://www\.|http://www\.|https://|http://)+.*", url):
		url = re.sub(r"(https://www\.|http://www\.|https://|http://)", '', url)
		if url.endswith('/'or'#'):
			st = url[:-1]
			url = st
		return url
	else:
		return url
	
# MAIN

# SETs
urlProcessadas = set()
urlProcessadasLimpas = set()
emails = set()
numeros = set()

paginaInicial = str(input("Digite a página que será varrida em busca de emails e telefones: "))

if 'http://' not in paginaInicial and 'https://' not in paginaInicial:
	paginaInicial = 'https://' + paginaInicial

urlBase = extraiBase(paginaInicial)
print("URL BASE: ", urlBase)

new_urls = deque([paginaInicial])

# PROCESSA AS URLS UMA A UMA ENQUANTO COUBER NA QUEUE
while len(new_urls):

	# MOVE PARA A PRÓXIMA
	url = new_urls.popleft()
	urlProcessadas.add(url)
	urlProcessadasLimpas.add(limpaUrl(url))

	# EXTRAI A BASE DA URL PARA RESOLVER LINK RELATIVOS
	partes = urlsplit(url)
	base_url = "{0.scheme}://{0.netloc}".format(partes)
	path = url[:url.rfind('/') + 1] if '/' in partes.path else url
	
	# PEGA O CONTEÚDO DA URL
	print("Processando %s" % url)
	try:
		response = requests.get(url)
	except (requests.exceptions.MissingSchema, requests.exceptions.ConnectionError):
		# IGNORA PÁGINAS COM ERRO
		continue
		
	# EXTRAI EMAILS E NÚMEROS E COLOCA EM UM SET
	new_emails = set(re.findall(r"[a-z0-9\.\-+_]+@[a-z0-9\.\-+_]+\.[a-z]+", response.text, re.I))
	new_numeros = filtrarNumeros(response.text)
	emails.update(new_emails)
	numeros.update(new_numeros)
	
	# ADICIONA OS EMAILS, NÚMEROS E URLS ENCONTRADOS EM SEUS ARQUIVOS
	with open('Emails-Encontrados.txt', 'w') as f:
		for email in emails:
			f.write("%s\n" % email)
	with open('Números-Encontrados.txt', 'w') as g:
		for numero in numeros:
			g.write("%s\n" % numero)
	with open('Páginas-Encontrados.txt', 'w') as h:
		for pagina in urlProcessadasLimpas:
			h.write("%s\n" % pagina)

	# CRIA UM BEAUTIFUL SOUP
	soup = BeautifulSoup(response.text)
	
	# ACHA E PROCESSA OS LINKS
	for ancora in soup.find_all("a"):
		# EXTRAI O LINK 
		link = ancora.attrs["href"] if "href" in ancora.attrs else ''
		# RESOLVE LINKS RELATIVOS
		if link.startswith('/'):
			link = base_url + link
		elif not link.startswith('http'):
			link = path + link
		# ADICIONA A NOVA URL PARA A FILA SE A MESMA AINDA NÃO FOI PROCESSADA E SE PERTENCE A URL BASE
		if not link in new_urls and not link in urlProcessadas and urlBase in link:
			if 'mailto' not in link:
				if '@' not in link:
					if 'javascript' not in link:
						new_urls.append(link)