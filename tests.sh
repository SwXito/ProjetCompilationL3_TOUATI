#!/bin/bash

# Vérifie si le compilateur (tpcas) est présent
if [ ! -f "./bin/tpcas" ]; then
  echo "Le compilateur 'tpcas' n'est pas présent dans le répertoire courant."
  exit 1
fi

good_directory="test/good"

syn_err_directory="test/syn-err"

valid=0

score_success=0
score_syntax_err=0

echo "#### Test des fichiers réussis ####"
for file in "$good_directory"/*.tpc; do
  echo "Analyse syntaxique de $file"

  ./bin/tpcas < "$file"

  if [ $? -eq 0 ]; then
    echo "Pas d'erreur syntaxique."
    ((valid++))
    ((score_success++))
  else
    echo "Erreur syntaxique détectée."
  fi

  echo "---------------------"
done

echo "Nombre de fichiers avec erreur syntaxique : $valid"
echo "Score pour les tests réussis : $score_success"
echo ""

echo "#### Test des fichiers en erreur syntaxique ####"
valid=0

for file in "$syn_err_directory"/*.tpc; do
  echo "Analyse syntaxique de $file"

  ./bin/tpcas < "$file"

  if [ $? -eq 0 ]; then
    echo "Pas d'erreur syntaxique (ERREUR : le fichier devrait produire une erreur)."
  else
    echo "Erreur syntaxique détectée comme prévu."
    ((valid++))
    ((score_syntax_err++))
  fi

  echo "---------------------"
done

echo "Nombre total de fichiers avec erreur syntaxique : $valid"
echo "Score pour les tests en erreur syntaxique : $score_syntax_err"
