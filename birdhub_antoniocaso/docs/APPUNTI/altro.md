## A cosa serve la resistenza in un LED
Il LED è un diodo ad emissione luminosa (light emitting diode), per cui, come tutti i diodi, interrompe il flusso di corrente in una direzione. Bisogna quindi stare attenti al verso in cui viene orientato. 

Il polo positivo del LED viene detto **anodo** mentre il polo negativo viene detto **catodo**. L'anodo dev'essere orientato verso una zona a potenziale maggiore mentre il catodo dev'essere orientato verso una zona a potenziale minore (ground).

La caratteristica principale dei diodi è il fatto che lavorano a bassa tensione. Un led rosso, ad esempio ha una tensione nominale di 1.8 V. La corrente massima misurabile è di 30mA.

Per questo motivo bisogna inserire una resistenza tra l'anodo e la sorgente.

Nota la tensione nominale del LED, si ricava la caduta di tensione che si vuole avere sul resistore. Per un LED rosso (con tensione nominale 1.8V) vogliamo che la caduta di tensione sul resistore sia:

$$
V_R = V_s - V_n = 5 - 1.8 = 3.2 V
$$

Nota la caduta di tensione necessaria sul resistore e fissata una corrente (minore della corrente nominale del LED), si ricava la resistenza applicando la legge di Ohm:

$$
    R = \frac{V_R}{I} = \frac{3.2}{0.02} = 175 \Omega
$$

