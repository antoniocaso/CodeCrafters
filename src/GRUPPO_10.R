#### Progetto Statistica Applicata GRUPPO 10 ####

#### Caricamento librerie ####
library(corrplot)
library(faraway)
library(leaps)

#### Caricamento e preparazione dataset ####
dataset = read.csv("Dataset_AH_gruppo10.csv")
colnames(dataset) = c('y', 'x1', 'x2', 'x3', 'x4','x5', 'x6')

#### Definizioni funzioni di supporto ####
create_graphic = function(x){
  par(mfrow=c(1,2))
  
  boxplot(x, horizontal = F,col = "#F4CCCC") 
  hist(x, freq=T, main ="", col = "#CFDAF8")
  
  par(mfrow=c(1,1))
}

create_scatterplot = function(x, title, xlbl){
  plot(x, dataset$y, main = title, ylab = "Y", col = "#195FFF", pch = 20, xlab = xlbl)
  # Aggiunta retta di regressione
  reg = lm(dataset$y ~ x)
  abline(reg, col = "#FF313E", lwd = 2)
  # Calcolo del coefficiente di correlazione
  annotation = paste("r =", cor(x,dataset$y))
  mtext(annotation, side = 1)
}

#### Analisi preliminare dei dati ####
head(dataset)

# Il seguente codice genera uno scatter plot
# dove la variabile dipendente è rappresentata 
# in funzione di ogni predittore del dataset
par(mfrow = c(2,3))
for(x in dataset[,2:7]){
  plot(x, dataset$y)
  mod = lm(y ~ x, data=dataset)
  abline(mod)
}
par(mfrow = c(1,1))

#### Analisi di correlazione ####
# Matrice di correlazione
correlation_matrix = cor(dataset)
# Grafico riassuntivo
corrplot(correlation_matrix, main="Matrice di correlazione")

#### Predittore X1 ####
create_graphic(dataset$x1)
create_scatterplot(dataset$x1, "Velocità CPU", "X1")
# Regressione polinomiale
model_cpu = lm(y ~ x1 + I(x1^2) + I(x1^3), data = dataset)
summary(model_cpu)

# Solo il termine lineare risulta avere un parametro 
# significativamente diverso da zero

# Test F
model_cpu_ftest = aov(y ~ x1, data = dataset)
summary(model_cpu_ftest)

# Il p-value è molto basso, per cui non possiamo escludere
# una relazione lineare tra Y e X1

#### Predittore X2 ####
create_graphic(dataset$x2)
create_scatterplot(dataset$x2, "Dimensione Hard-Disk", "X2")

# Regressione polinomiale
model_hdd = lm(y ~ x2 + I(x2^2) + I(x2^3), data = dataset)
summary(model_hdd)

# Test F
model_hdd_ftest = aov(y ~ x2, data = dataset)
summary(model_hdd_ftest) 

# Il p value è maggiore del rischio di prima specie
# per cui non si ha sufficiente evidenza per decidere

#### Predittore X3 ####
create_graphic(dataset$x2)
create_scatterplot(dataset$x2, "Numero di processi SW", "X3")

# Regressione polinomiale
model_proc = lm(y ~ x3 + I(x3^2) + I(x3^3), data = dataset)
summary(model_proc)

model_proc = lm(y ~ I(x3^2) + I(x3^3), data = dataset)
summary(model_proc)

## Il migliore sembra essere cubico con termine di primo grado nullo
model_proc_ftest = aov(y ~ I(x3^2) + I(x3^3), data = dataset)
summary(model_proc_ftest)

#### Predittore X4 ####
create_graphic(dataset$x4)
create_scatterplot(dataset$x4, "Aging SW", "X4")

model_aging = lm(y ~ x4 + I(x4^2) + I(x4^3), data=dataset)
summary(model_aging)

model_aging = lm(y ~ x4 + I(x4^2), data=dataset)
summary(model_aging)

model_aging = lm(y ~ x4, data=dataset)
summary(model_aging)

# F test
model_aging_ftest = aov(y ~ x4, data = dataset)
summary(model_aging_ftest) 

#### Predittore X5 ####
create_graphic(dataset$x5)
create_scatterplot(dataset$x5, "Prestazioni scheda audio", "X5")

model_audio = lm(y ~ x5 + I(x5^2) + I(x5^3), data = dataset)
summary(model_audio)

model_audio = lm(y ~ x5 + I(x5^2), data = dataset)
summary(model_audio)

model_audio_ftest = aov(y ~ x5, data = dataset)
summary(model_audio_ftest)

#### Predittore X6 ####
create_graphic(dataset$x6)
create_scatterplot(dataset$x6, "Prestazioni RAM", "X6")

model_ram = lm(y ~ x6 + I(x6^2) + I(x6^3), data = dataset)
summary(model_ram)

model_ram = lm(y ~ x6 + I(x6^2), data = dataset)
summary(model_ram)

model_ram = lm(y ~ x6, data = dataset)
summary(model_ram)

# F test
model_ram_ftest = aov(y ~ x6 + I(x6^2), data = dataset)
summary(model_ram_ftest)

#### Termini di interazione ####
# Analisi di regressione che include tutti i possibili 
# termini di interazione per i 6 predittori
interaction_terms = lm(y ~ x1*x2*x3*x4*x5*x6, data=dataset)
summary(interaction_terms)

# Gli unici termini che potrebbero avere un effetto 
# sulla variabile dipendente sono termini di interazione
# ottenuti dal prodotto di due o tre variabili, per cui
# si testano i prodotti fino a tre varaibili

interaction_terms = lm(y ~ (x1+x2+x3+x4+x5+x6)^3, data=dataset)
summary(interaction_terms)

# Gli unici termini di interazione con p-value inferiore a 0.05
# sono x1:x6 x3:x5

# I termini di interazione dati dal prodotto a tre variabili
# hanno perso significatività a confronto con la presenza
# nel nuovo modello testato dei predittori singoli al primo
# ordine, per cui si testano i prodotti fino a due variabili

interaction_terms = lm(y ~ (x1+x2+x3+x4+x5+x6)^2, data=dataset)
summary(interaction_terms) # x1,x6 x3,x5 x3,x4 x4,x6

# I termini con valore del p-value inferiore a 0.05 sono
# x1:x6, x3:x5, x3:x4, x4:x6

## Inserire Test F per accettazione del regressore
interaction_test1 = aov(y ~ x1:x6, data = dataset)
summary(interaction_test1)

interaction_test2 = aov(y ~ x3:x5, data = dataset)
summary(interaction_test2)

interaction_test3 = aov(y ~ x3:x4, data = dataset)
summary(interaction_test3)
# Non abbiamo sufficiente evidenza per accettare
# il predittore x3:X4 nel modello

interaction_test4 = aov(y ~ x4:x6, data = dataset)
summary(interaction_test4)
# Non abbiamo sufficiente evidenza per accettare
# il predittore x4:x6 nel modello

#### Stepwise Regression con Forward Selection ####
# Criterio utilizzato: p-value

# Step 1: aggiunta del predittore X1
step_1 = lm(y ~ x1, data = dataset)
summary(step_1)

# Intervalli di confidenza del predittore X1
S = sqrt( sum( (dataset$y - step_1$fitted.values)^2)/(98) )
SE_0 = S*sqrt(1/100+( (mean(dataset$x1))^2  / (sum(dataset$x1^2)-100*(mean(dataset$x1))^2 ) ) )
SE_1 = S*sqrt(  (1  / (sum(dataset$x1^2)-100*(mean(dataset$x1))^2 ) ) )

upper_beta_0 = beta_0 + (qt(0.975, 98) * SE_0)
lower_beta_0 = beta_0 - (qt(0.975, 98) * SE_0)
print(upper_beta_0)
print(lower_beta_0)

beta_1 = step_1$coefficients[2]
upper_beta_1 = beta_1 + (qt(0.975, 98) * SE_1)
lower_beta_1 = beta_1 - (qt(0.975, 98) * SE_1)
print(upper_beta_1)
print(lower_beta_1)

# Equivalente al comando
# confint(step_1)

# Step 2: aggiunta del predittore X2
step_2 = lm(y ~ x1 + x2, data = dataset)
summary(step_2)

# Step 3: aggiunta del predittore X3 e rimozione X2
step_3 = lm(y ~ x1 + I(x3^2) + I(x3^3), data = dataset)
summary(step_3)

# Step 4: aggiunta del predittore X4
step_4 = lm(y ~ x1 + I(x3^2) + I(x3^3) + x4, data = dataset)
summary(step_4)

# Step 5: aggiunta del predittore X5
step_5 = lm(y ~ x1 + I(x3^2) + I(x3^3) + x4 + x5, data = dataset)
summary(step_5)

# Step 6: aggiunta del predittore X6
step_6 = lm(y ~ x1 + I(x3^2) + I(x3^3) + x4 + x5 + x6 + I(x6^2), data = dataset)
summary(step_6)

# Step 7: aggiunta del predittore X1:X6 e rimozione di X6^2
step_7 = lm(y ~ x1 + I(x3^2) + I(x3^3) + x4 + x5 + x6 + x1:x6, data = dataset)
summary(step_7)

# Step 8: aggiunta del predittore X3:X5
step_8 = lm(y ~ x1 + I(x3^2) + I(x3^3) + x4 + x5 + x6 + x1:x6 + x3:x5, data = dataset)
summary(step_8)

# Step 9: rimozione predittore X3:X5
step_9 = lm(y ~ . - x2 - x3 + I(x3^2) + I(x3^3) + x1:x6, data = dataset)
summary(step_9)

#### Criteri di confronto dei modelli ####
# Usando la funzione regsubsets della libreria leaps
# per ottenere gli indici R^2, BIC, AIC e l'MSE di ciascun
# sottoinsieme dei predittori del modello definito in step_9
best_subsets = regsubsets(y ~ . -x2 -x3 + I(x3^2) + I(x3^3) + x1:x6, data = dataset)
best_subsets_summary = summary(best_subsets)
print(best_subsets_summary)

# RSS
plot(best_subsets_summary$rss)
best = which.min(best_subsets_summary$rss)
points(best, best_subsets_summary$rss[best], col ="red")

# R^2
plot(best_subsets_summary$rsq)
best = which.max(best_subsets_summary$rsq)
points(best, best_subsets_summary$rsq[best], col ="red")

# Il modello con il miglior indice R^2 è il modello
# con più predittori, così come atteso

# Schwarz (Bayesian) Information Criterion
plot(best_subsets_summary$bic)
best = which.min(best_subsets_summary$bic)
points(best, best_subsets_summary$bic[best], col ="red")

# Sebbene il criterio BIC penalizzi i modelli con più predittori,
# in questo caso, il modello con step_9, con 7 predittori,
# sembra comunque avere un buon valore del BIC

# Anche se entrambi i criteri selezionano il modello step_9 come
# il miglior modello, lo scarto tra gli indici R^2 e BIC del modello
# a 7 predittori e il modello a 6 predittori è molto basso
delta_rsq = best_subsets_summary$rsq[7] - best_subsets_summary$rsq[6]
delta_bic = best_subsets_summary$bic[7] - best_subsets_summary$bic[6]
print(delta_rsq)
print(delta_bic)

#### Plot diagnostici ####
# Confrontiamo i plot diagnostici
# del modello step_9 e del seguente modello, ottenuto rimuovendo 
# il predittore X5 dal modello step_9
step_10 = lm(y ~ . - x2 - x3 + I(x3^2) + I(x3^3) + x1:x6 -x5, data = dataset)
summary(step_10)

# Analisi dei residui
# Equivalente a 
# plot(step_9$fitted.values, step_9$residuals)
# abline(h = 0) 
plot(step_9, which = 1, main = "Residui modello a 7 predittori")
plot(step_10, which = 1, main = "Residui modello a 6 predittori")

# QQPlots
plot(step_9, which = 2, main = "Q-Q Plot modello a 7 predittori")
plot(step_10, which = 2, main = "Q-Q Plot modello a 6 predittori")
