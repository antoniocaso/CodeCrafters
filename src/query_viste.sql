-- ABBONAMENTI PER VITICOLTORE
select 
    viticoltore.cf as "Viticoltore",
    viticoltore.nome as "Nome Viticoltore",
    viticoltore.cognome as "Cognome Viticoltore",
    count(*) as "Abbonamenti Attivi"
from abbonamento, vigneto, viticoltore
where
    abbonamento.vigneto = vigneto.id and 
    vigneto.proprietario = viticoltore.cf
group by
    viticoltore.cf, viticoltore.nome, viticoltore.cognome;


--- ARTICOLI CORRELATI
create or replace view ordini_per_cliente(cf, codice) as 
    select cliente.cf, prodotto.codice
    from
        cliente, ordine, composizione, prodotto
    where
        ordine.cliente = cliente.cf and 
        ordine.numero = composizione.ordine and  
        composizione.prodotto = prodotto.codice;

select distinct J.codice as "Correlati"
from  ordini_per_cliente J, (select distinct *
                from ordini_per_cliente J1
                where 
                    J1.cf <> 'MTMZBN40H24C595L' and
                    exists (select *
                            from ordini_per_cliente J2 
                            where J2.codice = J1.codice and 
                            J2.cf <> J1.cf and
                            J2.codice = '000000000aaaa')) as correlati
where J.codice <> correlati.codice and J.cf = correlati.cf;

-- NUMERO DI VENDITE PER PRODOTTO 
(select prodotto.uva_qualità as  "Nome Prodotto", count(prodotto.codice) as "Vendite"
from ordine, composizione, prodotto
where 
    ordine.numero = composizione.ordine and  
    composizione.prodotto = prodotto.codice and
    prodotto.tipo = 'U'
group by
    prodotto.codice)

union

(select prodotto.vino_denominazione as  "Nome Prodotto", count(prodotto.codice) as "Vendite"
from ordine, composizione, prodotto
where 
    ordine.numero = composizione.ordine and  
    composizione.prodotto = prodotto.codice and
    prodotto.tipo = 'V'
group by
    prodotto.codice)

union

(select prodotto.aceto_denominazione as  "Nome Prodotto", count(prodotto.codice) as "Vendite"
from ordine, composizione, prodotto
where 
    ordine.numero = composizione.ordine and  
    composizione.prodotto = prodotto.codice and
    prodotto.tipo = 'A'
group by
    prodotto.codice)

order by "Vendite" desc;

-- VISTA: VENDITE TRIMESTRALI
create or replace view vendite_trimestrali(prodotto,prezzo) as 
    select
        P.codice as prodotto,
        sum(C.quantità*(p.prezzo_unitario-(p.prezzo_unitario*sconto/100)))
    from 
        prodotto as P 
        join composizione as C on (P.codice = C.prodotto) 
        join ordine as O on (c.ordine=o.numero)
    where current_date - o.data < interval '3 months'
    group by p.codice;

-- VENDITE TRIMESTRALI PER VITICOLTORE
select
    v.nome,
    v.cognome,
    v.azienda,
    sum(vt.prezzo)
from
    vendite_trimestrali as vt
    join prodotto as p on(vt.prodotto=p.codice)
    join vigneto as vg on(p.provenienza=vg.id)
    join viticoltore as v on(vg.proprietario=v.cf)
group by 
    v.cf,
    v.nome,
    v.cognome,
    v.azienda;