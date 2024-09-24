# HPC PROJECT WORK - Gruppo AH0010

https://docs.google.com/document/d/1OpeTJZ1ymqJpATKm9S0xIsG9o8ut8L7QgoXxubfDUIM/edit?usp=sharing

## TODO
### Generazione Grafo
- [x] capire come generare il grafo (dimensione almeno un paio di GB)
- [x] Progettare ADT Grafo in C
- [x] Implementare Grafo con lista di adiacenza
- [x] Completare e testare la funzione di serializzazione

### Taglio
- [x] Scrivere la funzione cut()
- [x] Implementare e testare l'algoritmo di shuffle di Fisher-Yates su un array compatibile con il tipo del bucket del grafo.
- [x] Capire come inviare ai nodi MPI i tagli 
- [x] Se il numero di nodi non è divisibile per il numero di processi MPI...

### Tarjan
- [ ] Capire come parallelizzare con CUDA l'algoritmo vedi [scc-cuda](https://github.com/ShubhaniGupta/scc-cuda)
- [ ] Risolvere problema con linter CUDA

### Unione
- [ ] Progettare macronodi

### Scheduler
- [ ] Vedere se inserire barriera
