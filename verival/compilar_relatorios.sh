#!/bin/bash
set -o posix

cd plano_de_testes
make dist-clean
make
make clean
cd ../relatorio_final
make dist-clean
make
make clean
cd ../relatorio_tecnico
make dist-clean
make
make clean
cd ..
