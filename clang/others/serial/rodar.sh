#!/bin/bash

echo "====> Limpando diretorio de binarios antigos"
make clean

echo "====> Compilando o programa"
make

echo "====> Matando software de interacao do PC para evitar que ele ocupe a serial (talvez peca senha)"
sudo pkill client

echo "====> Mandando o programa para a placa"
make isp
echo "====> Resete a placa para o programa entrar em vigor"

echo "====> Executando tser para calibrar terminal"
echo "====> Feche o tser com CTRL + X para continuar para o programa"
make tser
#echo "====> Configurando a serial para o programa do PC"
#stty -F /dev/ttyS0 ispeed 19200 oddp

echo "====> Executando software auxiliar do PC (favor verificar que a internet esta funcionando)"
sudo `pwd`/client


exit 0
