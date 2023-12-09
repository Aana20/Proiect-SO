#!/bin/bash

# Verifica daca s-a furnizat un singur argument
if test "$#" -ne 1; then
    echo "Trebuie furnizat un singur argument de forma 'bash script.sh <c>'"
    exit 1
fi

# Caracterul furnizat ca argument
caracter=$1

# Functie pentru a valida propozitia
valid_propozitie() {
         if [[ $1 =~ ^[A-Z][A-Za-z0-9,[:blank:],.!?]*[.!?]$ ]]  && ! [[ $1 =~ ^.*[,]si ]]

     then
     	echo "OK"
        return 0  
        
        #Propozitie valida
    else
    	echo "NOT OK"
        return 1  
        
        #Propozitie nvalida
    fi
}
#Initializare contor
sentence_count=0

#Citeste linie cu linie pana la EOF (CTRL+D)
while  read -r line
do
    status=$(valid_propozitie "$line")                                                                              
        
    # Verifica daca linia este o propozitie corecta si contine caracterul
    if [[ "$line" == *"$caracter"* ]] && [[ $(valid_propozitie "$line") == "OK" ]]
     then
        ((sentence_count++))
    fi
done

# fiseaza rezultatul
echo "Numarul de propozitii corecte care contin caracterul '$caracter': $sentence_count"
