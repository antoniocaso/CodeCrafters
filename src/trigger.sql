drop trigger if exists ricevuta on composizione;
drop trigger if exists disponibilità on composizione;
drop trigger if exists check_composizione on ordine;
drop trigger if exists check_composizione on composizione;
drop trigger if exists check_coinvolgimento on abbonamento;
drop trigger if exists check_coinvolgimento on coinvolgimento;

-- TRIGGER INIZIALIZZAZIONE (IMPLEMENTAZIONE PARTECIPAZIONE OBBLIGATORIA)
-- PARTECIPAZIONE OBBLIGATORIA RELAZIONE COMPOSIZIONE
create or replace function at_least_one_composizione() returns trigger as $$
	begin
	if (exists (select numero from ordine 
					where numero not in (select ordine from composizione)
					)) then 
						raise exception 'Ordine privo di prodotti, operazione annullata';
	end if;
	return new;
end $$ language plpgsql;

create trigger check_composizione
	after insert on ordine
	for each row 
	execute procedure at_least_one_composizione();

create trigger check_composizione
	after update or delete on composizione
	for each row 
	execute procedure at_least_one_composizione();

-- PARTECIPAZIONE OBBLIGATORIA RELAZIONE COINVOLGIMENTO
create or replace function at_least_one_coinvolgimento() returns trigger as $$
	begin
	if (exists (select cliente, vigneto from abbonamento 
					where (cliente, vigneto) not in (select cliente, vigneto from coinvolgimento)
					)) then 
						raise exception 'Abbonamento privo di prodotti, inserimento annullato';
	end if;
	return new;
end $$ language plpgsql;

create trigger check_coinvolgimento
	after insert on abbonamento
	for each row
	execute procedure at_least_one_coinvolgimento();

create trigger check_coinvolgimento
	after update or delete on coinvolgimento
	for each row
	execute procedure at_least_one_coinvolgimento();

-- TRIGGER RICEVUTA
create or replace function calcolo_ricevuta() returns trigger as $$
	declare subtot decimal(8,2);
	declare percentuale_iva INTEGER;
	declare sped decimal(8,2);
	declare scorporo_iva decimal(8,2);
	declare sconto_tipo_prodotto INTEGER;

	begin
		sconto_tipo_prodotto = new.sconto;
		if (not exists (select * from ricevuta where ordine = new.ordine)) then
		
			if((select tipo from prodotto where new.prodotto = prodotto.codice) = 'U') then
				percentuale_iva = 4;
			else
				percentuale_iva = 22;
			end if;
			select ((percentuale_iva*prezzo_unitario/100) + prezzo_unitario) * new.quantità, ((percentuale_iva*prezzo_unitario/100)) * new.quantità from prodotto where new.prodotto = prodotto.codice into subtot, scorporo_iva;
			
			if (subtot<50.00) then
				sped = 7.00;
			else
				sped = 0.00;
			end if;
			
			insert into ricevuta (ordine, subtotale, sconto, iva, spedizione, totale)
			values(new.ordine, subtot, (sconto_tipo_prodotto*subtot/100), scorporo_iva, sped, ((subtot)-(sconto_tipo_prodotto*subtot/100)) + sped);
		
		else
		
			if((select tipo from prodotto where new.prodotto = prodotto.codice) = 'U') then
				percentuale_iva = 4;
			else
				percentuale_iva = 22;
			end if;
			
			select ((percentuale_iva*prezzo_unitario/100) + prezzo_unitario) * new.quantità, ((percentuale_iva*prezzo_unitario/100)) * new.quantità from prodotto where new.prodotto = prodotto.codice into subtot, scorporo_iva;
			
			if((select subtotale+subtot from ricevuta where ricevuta.ordine = new.ordine)<50) then
				sped = 7.00;
			else
				sped = 0.00;
			end if;
			
			update  ricevuta set 
				subtotale = ricevuta.subtotale+subtot, 
				sconto = ricevuta.sconto + (sconto_tipo_prodotto*subtot/100), 
				iva=ricevuta.iva+scorporo_iva, 
				spedizione = sped, 
				totale=(ricevuta.subtotale- ricevuta.sconto) + ((subtot)-(sconto_tipo_prodotto*subtot/100)) + sped  
			where ricevuta.ordine = new.ordine;
			
			if (subtot<50.00) then
				sped = 7.00;
			else
				sped = 0.00;
			end if;
		end if;
		
	return new;
end $$ language plpgsql;

create trigger ricevuta
	before insert on composizione
	for each row
	execute procedure calcolo_ricevuta();

-- TRIGGER DISPONIBILITÀ
create or replace function verifica_disponibilità() returns trigger as $$
	declare disponibilità_prodotto integer;
	begin
		select disponibilità from prodotto where prodotto.codice = new.prodotto into disponibilità_prodotto;
		if ( disponibilità_prodotto < new.quantità ) then
			raise notice 'Quantità di prodotti disponibili non sufficienti!';
			delete from composizione where composizione.ordine = new.ordine;
			delete from ricevuta where ricevuta.ordine = new.ordine; 
			delete from ordine where ordine.numero = new.ordine;
			
			raise exception 'Ordine annullato';
		else 
			update prodotto
			set
				disponibilità = disponibilità - new.quantità
			where prodotto.codice = new.prodotto;
		end if;
	return new;
end $$ language plpgsql;

create trigger disponibilità
	before insert on composizione
	for each row
	execute procedure verifica_disponibilità();