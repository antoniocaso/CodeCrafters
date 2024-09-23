--Creazione database
/*DROP DATABASE IF EXISTS "Gruppo01";
CREATE DATABASE "Gruppo01" WITH OWNER = postgres;*/


--Creazione tabelle

begin transaction;

drop table if exists abbonamento cascade;
drop table if exists cliente cascade;
drop table if exists insetticida cascade;
drop table if exists viticoltore cascade;
drop table if exists ordine cascade;
drop table if exists spedizione cascade;
drop table if exists ricevuta cascade;
drop table if exists vigneto cascade;
drop table if exists trattamento cascade;
drop table if exists coinvolgimento cascade;
drop table if exists composizione cascade;
drop table if exists prodotto cascade;
drop table if exists azienda cascade;
drop domain if exists tipo_prodotto cascade;

create table cliente (
	cf char(16) primary key,
	nome varchar(30) not null,
	cognome varchar(30) not null,
	telefono varchar(10),
	mail varchar(40) unique not null,
	nascita date not null,
	indirizzo_via varchar(30) not null,
	indirizzo_civico integer not null,
	indirizzo_cap char(5) not null,
	indirizzo_città varchar(30) not null,
	check(age(nascita) > '18 years')
);


create table insetticida (
	nome varchar(30) primary key
);


create table viticoltore (
	cf char(16) primary key,
	nome varchar(30) not null,
	cognome varchar(30) not null,
	telefono varchar(10),
	mail varchar(40) unique not null,
	nascita date not null
);


create table azienda (
	partita_iva char(11) primary key,
	nome varchar(30) not null,
	direttore char(16) not null,
	constraint fk_direzione foreign key(direttore) references viticoltore(cf)
	on update cascade on delete cascade
);


create table ordine (
	numero char(20) primary key,
	data timestamp default current_timestamp, 
	peso decimal(6,3) not null,
	spedito boolean not null, 
	consegnato boolean not null,
	data_consegna date null,
	cliente char(16) not null,
	constraint fk_esecuzione foreign key (cliente) references cliente(cf)
	on update cascade on delete restrict,
	unique(data, cliente),
	check((data_consegna is not null and consegnato = 'true') or (consegnato = 'false' and data_consegna is null)),
	check((consegnato = 'true' and spedito = 'true') or consegnato = 'false')
);


create table spedizione (
	ordine char(20) primary key,
	tracking varchar(20) not null,
	corriere varchar(30) not null,
	data_spedizione date not null,
	constraint fk_invio foreign key(ordine) references ordine(numero)
	on update cascade on delete restrict
);


create table ricevuta (
	ordine char(20) primary key,
	subtotale decimal(8,2) not null,
	sconto decimal(8,2) not null,
	iva decimal(8,2) not null,
	spedizione decimal(8,2) not null, 
	totale decimal(8,2) not null,
	constraint fk_emissione foreign key(ordine) references ordine(numero)
	on update cascade on delete cascade
	deferrable initially deferred
);


create table vigneto (
	id serial primary key,
	codice char(8) not null,
	dimensione integer not null,
	esposizione varchar(30) not null,
	altitudine varchar(30) not null,
	locazione_regione varchar(30) not null,
	locazione_comune varchar(30) not null,
	locazione_foglio integer not null,
	locazione_particella integer not null,
	proprietario char(16) not null,
	constraint fk_proprieta foreign key (proprietario) references viticoltore(cf)
	on update cascade on delete restrict,
	unique(proprietario, codice)
);

create domain tipo_prodotto as char check
    (value = 'U' or value = 'V' or value = 'A');

create table prodotto (
	codice char(13) primary key,
	provenienza integer not null,
	tipo tipo_prodotto not null,
	prezzo_unitario decimal(8,2),
	disponibilità integer not null, 
	peso decimal(6,3) not null,
	vino_gradazione_alcolica decimal(3,1),
	vino_annata char(4), 
	vino_formato decimal(4,2),
	vino_denominazione varchar(50),
	vino_marchio_qualità varchar(30),
	aceto_formato decimal(4,2),
	aceto_denominazione varchar(50), 
	uva_qualità varchar(30),
	constraint fk_provenienza foreign key(provenienza) references vigneto(id)
	on update cascade on delete restrict,
	check((tipo = 'U' and uva_qualità is not null
		 and vino_gradazione_alcolica is null and vino_annata is null and vino_formato is null
		 and vino_denominazione is null and vino_marchio_qualità is null
		 and aceto_formato is null and aceto_denominazione is null) or 
	(tipo = 'V' and vino_gradazione_alcolica is not null and vino_annata is not null and vino_formato is not null
		 and vino_denominazione is not null and vino_marchio_qualità is not null 
		 and aceto_formato is null and aceto_denominazione is null and uva_qualità is null) or 
	(tipo = 'A' and uva_qualità is null
		 and vino_gradazione_alcolica is null and vino_annata is null and vino_formato is null
		 and vino_denominazione is null and vino_marchio_qualità is null
		 and aceto_formato is not null and aceto_denominazione is not null))
);


create table trattamento (
	insetticida varchar(30) references insetticida(nome)
	on update cascade on delete restrict,
	vigneto integer references vigneto(id)
	on update cascade on delete restrict,
	primary key(insetticida, vigneto)
);


create table composizione (
	prodotto char(13),
	ordine char(20),
	quantità integer not null,
	sconto integer not null, 
	constraint fk_composizione_prodotto foreign key (prodotto) references prodotto(codice)
	on update cascade on delete restrict
	deferrable initially deferred,
	constraint fk_composizione_ordine foreign key(ordine) references ordine(numero)
	on update cascade on delete restrict
	deferrable initially deferred,
	primary key(prodotto, ordine)
);


create table abbonamento (
	cliente char(16), 
	vigneto integer,
	data_sottoscrizione date not null,
	risparmio decimal(8,2) default 0.00,
	frequenza integer not null,
	costo_abbonamento decimal(8,2) not null,
	tipologia char not null,
	primary key(cliente, vigneto),
	constraint fk_sottoscrizione foreign key (cliente) references cliente(cf)
	on update cascade on delete cascade,
	constraint fk_provenienza foreign key (vigneto) references vigneto(id)
	on update cascade on delete cascade,
	check((tipologia = 'A' and (frequenza = 1 or frequenza = 2 or frequenza = 3 or frequenza = 4 or frequenza = 6)) or
			tipologia = 'S' and (frequenza = 1 or frequenza = 2 or frequenza = 3))
);


create table coinvolgimento (
	cliente char(16),
	vigneto integer,
	prodotto char(13),
	quantità integer not null,
	primary key(cliente, vigneto, prodotto),
	constraint fk_coinvolgimento_abbonamento foreign key(cliente, vigneto) references abbonamento(cliente, vigneto)
	on update cascade on delete restrict
	deferrable initially deferred, 
	constraint fk_coinvolgimento_prodotto foreign key(prodotto) references prodotto(codice)
	on update cascade on delete restrict
	deferrable initially deferred
);


--Popolamento

delete from ricevuta cascade;
delete from coinvolgimento cascade;
delete from abbonamento cascade;
delete from spedizione cascade;
delete from cliente cascade;
delete from composizione cascade;
delete from prodotto cascade;
delete from ordine cascade;
delete from insetticida cascade;
delete from vigneto cascade;
delete from viticoltore cascade;
delete from trattamento cascade;
delete from azienda cascade;

ALTER SEQUENCE vigneto_id_seq RESTART WITH 1;

insert into viticoltore(cf, nome, cognome, mail, nascita) 
values('PRLSGS36P49B813O', 'Mario', 'Rui', 'mariorui@gmail.com', '1966-05-11'),
      ('VVRLVA87B13H916I', 'Maria', 'Della Vecchia', 'mariadv@gmail.com', '1956-05-11'),
      ('RGPPZJ27M68G977O', 'Giorgio', 'Chiellini', 'gichi@gmail.com', '1994-05-11'),
      ('SFPLHG62M28A625K', 'Luca', 'Rossi', 'lucarossi@gmail.com', '1994-07-11'),
      ('PBMLCL53P05B989C', 'Matteo', 'Bianchi', 'matteobianchi@gmail.com', '1994-06-11'),
      ('DPHNTV37E71H347W', 'Ernesto', 'Iannaccone', 'ernestoiannaccone@gmail.com', '1956-05-11'),
      ('KLMPVI79E02A427C', 'Pasquale', 'De Crescenzo', 'pdescrescenzo@gmail.com', '1978-05-11'),
      ('ZTVTVM63B21C452E', 'Amilcare', 'Esposito', 'amilcareesp@gmail.com', '1932-09-13'),
      ('PYTRFV92H47C348D', 'Ciro', 'Esposito', 'ciroesp@gmail.com', '1978-05-23'),
      ('RVHPSY44B15M147B', 'Gennaro', 'Savastano', 'gennycar@gmail.com', '1988-02-16');

insert into azienda(partita_iva, nome, direttore)
values('75685900823', 'Torre dei Chiusi', 'PRLSGS36P49B813O'),
      ('52224190570', 'Torre Venere', 'VVRLVA87B13H916I'),
      ('14348440885', 'Borgo Giulia', 'RGPPZJ27M68G977O'),
      ('10188390149', 'Alepa', 'SFPLHG62M28A625K'),
      ('48766970122', 'Cantine Ruggiero', 'PBMLCL53P05B989C'),
      ('59909760353', 'Bosco de Medici', 'DPHNTV37E71H347W'),
      ('56275190157', 'Cantina del Angelo', 'KLMPVI79E02A427C'),
      ('66788950278', 'Cantine del mare', 'ZTVTVM63B21C452E'),
      ('67971160154', 'Cantina Sociale Solopaca', 'PYTRFV92H47C348D'),
      ('79606460594', 'San Giovanni', 'RVHPSY44B15M147B');

insert into cliente(cf, nome, cognome, telefono,  mail, nascita, indirizzo_via, indirizzo_civico, indirizzo_cap,  indirizzo_città) 
values('SPLCQZ32S62I400K', 'Andrea', 'Verdi', '3384778956', 'averdi@gmail.com', '1967-04-11', 'Roma', 420, 69000, 'Genova');
insert into cliente(cf, nome, cognome, mail, nascita, indirizzo_via, indirizzo_civico, indirizzo_cap,  indirizzo_città) 
values('QRRSVC71D59F865Z', 'Luca', 'Massi', 'lmassi@gmail.com', '1955-05-11', 'Garibali', 124, 86000, 'Trieste');
insert into cliente(cf, nome, cognome, telefono, mail, nascita, indirizzo_via, indirizzo_civico, indirizzo_cap,  indirizzo_città) 
values('ZZHWPP90B08G358A', 'Pino', 'Insegno', '3456778996', 'pinse@gmail.com', '1945-08-11', 'Isonzo', 167, 87540, 'Gorizia');
insert into cliente(cf, nome, cognome, telefono, mail, nascita, indirizzo_via, indirizzo_civico, indirizzo_cap,  indirizzo_città) 
values('MTMZBN40H24C595L', 'Giuseppe', 'Brambilla', '3453445657', 'gbramb@gmail.com', '1967-05-12', 'Trieste', 189, 83500, 'Pordenone');
insert into cliente(cf, nome, cognome, mail, nascita, indirizzo_via, indirizzo_civico, indirizzo_cap,  indirizzo_città) 
values('XZHXNG84C24L864S', 'Pasquale', 'Borsellin', 'borsep@gmail.com', '1967-09-24', 'Monte Grappa', 245, 88700, 'Pordenone');
insert into cliente(cf, nome, cognome, mail, nascita, indirizzo_via, indirizzo_civico, indirizzo_cap,  indirizzo_città) 
values('YLMNGD73B61F533I', 'Fausto', 'Bisognin', 'fbisogn@gmail.com', '1977-05-30', 'Brennero', 42, 86340, 'Udine');
insert into cliente(cf, nome, cognome, telefono, mail, nascita, indirizzo_via, indirizzo_civico, indirizzo_cap,  indirizzo_città) 
values('CLGWTV39E17G914M', 'Lucia', 'Marzullo', '3308989555', 'lmarz@gmail.com', '1988-07-26', 'Vittorio Veneto', 78, 82999, 'Udine');
insert into cliente(cf, nome, cognome, mail, nascita, indirizzo_via, indirizzo_civico, indirizzo_cap,  indirizzo_città) 
values('KHRGDZ86R53A200C', 'Rosa', 'Mauriello', 'mmaur@gmail.com', '1999-03-11', 'Caduti In Guerra', 69, 89780, 'Venezia');
insert into cliente(cf, nome, cognome, mail, nascita, indirizzo_via, indirizzo_civico, indirizzo_cap,  indirizzo_città) 
values('GTGGFS76D12I663C', 'Paola', 'Iannicelli', 'pian@gmail.com', '1962-01-19', 'Eroi di Patria', 56, 81666, 'Verona');
insert into cliente(cf, nome, cognome, mail, nascita, indirizzo_via, indirizzo_civico, indirizzo_cap,  indirizzo_città) 
values('GTSTJP48C11H862F', 'Carmine', 'Petraglia', 'cpetr@gmail.com', '1998-01-11', 'Patria', 22, 81420, 'Varese');

insert into insetticida(nome)
values('Verderame'),
      ('Naturalis'),
      ('Prodatix');

insert into vigneto(codice, dimensione, esposizione, altitudine, locazione_regione, locazione_comune, locazione_foglio, locazione_particella, proprietario)
values('PRLSGS1', 1000, 'nord', 500, 'Liguria', 'La Spezia', '20', '100', 'PRLSGS36P49B813O'),
      ('PRLSGS2', 2000, 'sud', 1300, 'Lombardia', 'Varese', '10', '56', 'PRLSGS36P49B813O'),
      ('VVRLVA1', 1400, 'sud', 800, 'Emilia-Romagna', 'Forli', '24', '120', 'VVRLVA87B13H916I'),
      ('VVRLVA2', 2400, 'est', 1500, 'Piemonte', 'Novara', '36', '145', 'VVRLVA87B13H916I'),
      ('RGPPZJ1', 3000, 'est', 700, 'Sardegna', 'Nuoro', '43', '176', 'RGPPZJ27M68G977O'),
      ('RGPPZJ2', 3200, 'west', 300, 'Emilia-Romagna', 'Ravenna', '12', '65', 'RGPPZJ27M68G977O'),
      ('SFPLHG1', 2200, 'est', 300, 'Toscana', 'Grosseto', '3', '12', 'SFPLHG62M28A625K'),
      ('PBMLCL1', 1700, 'nord', 355, 'Piemonte', 'Vercelli', '45', '187', 'PBMLCL53P05B989C'),
      ('DPHNTV1', 3400, 'nord', 700, 'Lombardia', 'Brescia', '34', '134', 'DPHNTV37E71H347W'),
      ('KLMPVI1', 5000, 'sud', 450, 'Liguria', 'Genova', '37', '162', 'KLMPVI79E02A427C'),
      ('ZTVTVM1', 1500, 'west', 700, 'Molise', 'Isernia', '29', '119', 'ZTVTVM63B21C452E'),
      ('ZTVTVM2', 1500, 'sud', 100, 'Sicilia', 'Palermo', '18', '75', 'ZTVTVM63B21C452E'),
      ('PYTRFV1', 5000, 'nord', 600, 'Lombardia', 'Lodi', '26', '104', 'PYTRFV92H47C348D'),
      ('PYTRFV2', 2700, 'sud', 95, 'Toscana', 'Arezzo', '42', '169', 'PYTRFV92H47C348D'),
      ('RVHPSY1', 3000, 'est', 740, 'Lazio', 'Rieti', '7', '30', 'RVHPSY44B15M147B'),
      ('RVHPSY2', 3800, 'west', 467, 'Marche', 'Macerata', '43', '167', 'RVHPSY44B15M147B');

insert into trattamento(insetticida, vigneto)
values('Verderame', 1),
      ('Verderame', 2),
      ('Verderame', 3),
      ('Verderame', 4),
      ('Verderame', 5),
      ('Naturalis', 6),
      ('Naturalis', 7),
      ('Naturalis', 8),
      ('Naturalis', 9),
      ('Naturalis', 10),
      ('Prodatix', 11),
      ('Prodatix', 12),
      ('Prodatix', 13),
      ('Prodatix', 14);

/*VINO*/
insert into prodotto(codice,provenienza, tipo,prezzo_unitario,disponibilità,peso,vino_gradazione_alcolica, vino_annata, vino_formato, vino_marchio_qualità, vino_denominazione) 
values('000000000aaaa',4 , 'V', 13.00,100,1, 12, 2021 ,0.75, 'igp', 'Aglianico'),
      ('000000000aaab',2 , 'V', 12.00,150,1.250, 14, 2019 ,1.00, 'dop', 'Solopaca'),
      ('000000000aaac',3 , 'V', 12.50,100,1, 12.5, 2018 ,0.75, 'igp', 'Fiano'),
      ('000000000aaad',3 , 'V', 18.00,200,1.750, 13.6, 2021 ,1.50, 'dop', 'Montepulciano'),
      ('000000000aaan',4 , 'V', 13.50,100,1, 12.5, 2019 ,0.75, 'igp', 'Fiano'),
      ('000000000aaao',4, 'V', 20.00,100,5.50, 16, 2021 ,5, 'stg', 'Primitivo di Manudria'),
      ('000000000aaas',5, 'V', 11.50,200,1, 12.5, 2018 ,0.75, 'dop', 'Lambrusco'),
      ('000000000aaat',5 , 'V', 20.00,100,1.50, 12, 2021 ,1, 'stg', 'Chianti');

/*Aceti*/
insert into prodotto(codice,provenienza,tipo,prezzo_unitario, disponibilità,peso,aceto_formato, aceto_denominazione) 
values('000000000aaae', 7 ,'A' ,5.00,100,1.00,0.75, 'Di Vino'),
      ('000000000aaaf', 7 ,'A' ,6.00,200,1.00,0.75, 'Di Vino Bianco'),
      ('000000000aaag', 3 ,'A' ,4.00,150,1.00,0.75, 'Di Vino Rosso'),
      ('000000000aaap', 4 ,'A' ,4.70,300,1.00,0.75, 'Di Vino Decolorato'); 

/*UVA*/
insert into prodotto(codice,provenienza,tipo,prezzo_unitario, disponibilità,peso,uva_qualità) 
values('000000000aaah',2, 'U', 3.30, 20,5.50 ,'Scarlotta Seedless'),
      ('000000000aaai',2, 'U', 3.50, 50,6.50 ,'Red Globe'),
      ('000000000aaal',3, 'U', 2.50, 50,5.50 ,'Zibibbo'),
      ('000000000aaam',4, 'U', 1.50, 50,5.50 ,'Fragola'),
      ('000000000aaaq',4 , 'U', 2.80, 50,5.00 ,'Regina'),
      ('000000000aaar',4 , 'U', 1.90, 50,5.00 ,'Italia');

commit;


--abbonamento  di 'GTSTJP48C11H862F'
begin transaction;
    insert into coinvolgimento(cliente, vigneto, prodotto, quantità)
    values('GTSTJP48C11H862F', 1, '000000000aaaa', 1),
        ('GTSTJP48C11H862F', 1, '000000000aaab', 3),
        ('GTSTJP48C11H862F', 1, '000000000aaac', 1);

    insert into abbonamento(cliente, vigneto, tipologia, data_sottoscrizione, frequenza, costo_abbonamento)
    values('GTSTJP48C11H862F', 1, 'A', '2021-07-14', 2, 12.0);
commit;


--abbonamento  di 'GTGGFS76D12I663C'
begin transaction;
    insert into coinvolgimento(cliente, vigneto, prodotto, quantità)
    values('GTGGFS76D12I663C', 2, '000000000aaab', 2),
        ('GTGGFS76D12I663C', 2, '000000000aaad', 1);

    insert into abbonamento(cliente, vigneto, tipologia, data_sottoscrizione, frequenza, costo_abbonamento)
    values('GTGGFS76D12I663C', 2, 'S', '2021-06-15', 2, 15.0);
commit;


--abbonamento  di 'KHRGDZ86R53A200C'
begin transaction;
    insert into coinvolgimento(cliente, vigneto, prodotto, quantità)
    values('KHRGDZ86R53A200C', 3, '000000000aaaa', 2);

    insert into abbonamento(cliente, vigneto, tipologia, data_sottoscrizione, frequenza, costo_abbonamento)
    values('KHRGDZ86R53A200C', 3, 'A', '2021-05-16', 3, 16.0);
commit;


--abbonamento  di 'CLGWTV39E17G914M'
begin transaction;
    insert into coinvolgimento(cliente, vigneto, prodotto, quantità)
    values('CLGWTV39E17G914M', 4, '000000000aaad', 5);

    insert into abbonamento(cliente, vigneto, tipologia, data_sottoscrizione, frequenza, costo_abbonamento)
    values('CLGWTV39E17G914M', 4, 'S', '2021-08-17', 1, 12.0);
commit;


--abbonamento  di 'YLMNGD73B61F533I'
begin transaction;
    insert into coinvolgimento(cliente, vigneto, prodotto, quantità)
    values('YLMNGD73B61F533I', 5, '000000000aaaf', 1);

    insert into abbonamento(cliente, vigneto, tipologia, data_sottoscrizione, frequenza, costo_abbonamento)
    values('YLMNGD73B61F533I', 5, 'A', '2021-04-18', 1, 100.0);
commit;

--ORDINI

--ordine di 'SPLCQZ32S62I400K'
begin transaction;
    --Primo ordine composto da due vini diversi: primo vino è ...a, 5 bottiglie; secondo vino è ...b, 5 bottiglie.
    insert into composizione(prodotto, ordine, quantità, sconto)
    values('000000000aaaa', '8ZIXCQNTXMIUIBETXAJY', 5, 10),
        ('000000000aaab', '8ZIXCQNTXMIUIBETXAJY', 5, 10),
        ('000000000aaac', '8ZIXCQNTXMIUIBETXAJY', 5, 10),
        ('000000000aaad', '8ZIXCQNTXMIUIBETXAJY', 5, 10);

    --Problema nella consegna
    insert into ordine(numero, peso, spedito, consegnato, data_consegna, cliente, data)
    values('8ZIXCQNTXMIUIBETXAJY', 2.6, 'true', 'false', null, 'SPLCQZ32S62I400K', '2022-01-01');

    --spedizione
    insert into spedizione(ordine, tracking, corriere, data_spedizione)
    values('8ZIXCQNTXMIUIBETXAJY', 'AAV0XJOI67CJGSUV0E', 'UPS','2021-09-15');
commit;


--ordine di 'SPLCQZ32S62I400K'
begin transaction;
    insert into composizione(prodotto, ordine, quantità, sconto)
    values('000000000aaaa', '8ZIXCQNTXMIUIBETXAJJ', 5, 10);
    insert into composizione(prodotto, ordine, quantità, sconto)
    values('000000000aaab', '8ZIXCQNTXMIUIBETXAJJ', 5, 10);

    --Problema nella consegna
    insert into ordine(numero, peso, spedito, consegnato, data_consegna, cliente, data)
    values('8ZIXCQNTXMIUIBETXAJJ', 2.6, 'false', 'false', null, 'SPLCQZ32S62I400K', '2022-01-02');
commit;

--ordine di QRRSVC71D59F865Z
begin transaction;
    --Secondo ordine composto da un solo vino, 3 bottilie e nessuno sconto.
    insert into composizione(prodotto, ordine, quantità, sconto)
    values('000000000aaab', 'VE8URM7NEMTE6VZF6CQZ', 3, 0);
    insert into composizione(prodotto, ordine, quantità, sconto)
    values('000000000aaac', 'VE8URM7NEMTE6VZF6CQZ', 3, 0);
    insert into composizione(prodotto, ordine, quantità, sconto)
    values('000000000aaad', 'VE8URM7NEMTE6VZF6CQZ', 3, 0);
    insert into composizione(prodotto, ordine, quantità, sconto)
    values('000000000aaae', 'VE8URM7NEMTE6VZF6CQZ', 3, 0);

    insert into ordine(numero, peso, spedito, consegnato, data_consegna, cliente, data)
    values('VE8URM7NEMTE6VZF6CQZ', 15.4, 'true', 'true','2021-09-19', 'QRRSVC71D59F865Z', '2022-01-03'); --Consegnato con successo

    insert into spedizione(ordine, tracking, corriere, data_spedizione)
    values('VE8URM7NEMTE6VZF6CQZ', 'MD3DACGXXFES7CE2JGRG', 'BRT','2021-09-16');
commit;


--ordine di ZZHWPP90B08G358A
begin transaction;
    --Terzo ordine composto da un solo vino, 2 bottilie e sconto totale ( parente del gestore del sito ).
    insert into composizione(prodotto, ordine, quantità, sconto)
    values('000000000aaab', 'BST75O1O07DQ8334YMQ6', 2, 80),
        ('000000000aaai', 'BST75O1O07DQ8334YMQ6', 2, 10),
        ('000000000aaag', 'BST75O1O07DQ8334YMQ6', 2, 10);

    insert into ordine(numero, peso, spedito, consegnato, data_consegna, cliente)
    values('BST75O1O07DQ8334YMQ6', 14, 'true', 'false',null, 'ZZHWPP90B08G358A'); --Non ancora consegnato

    insert into spedizione(ordine, tracking, corriere, data_spedizione)
    values('BST75O1O07DQ8334YMQ6', 'ZNEIZDR1XBP1', 'SDA','2021-09-17');
commit;


--ordine di MTMZBN40H24C595L
begin transaction;
    --Quarto ordine composto da due aceti diversi: primo aceto è ...e, 2 bottiglie; secondo aceto è ...f, 15 bottiglie.
    insert into composizione(prodotto, ordine, quantità, sconto)
    values('000000000aaae', 'CDV2OCARAJ1IRK3142F2', 2, 4);
    insert into composizione(prodotto, ordine, quantità, sconto)
    values('000000000aaai', 'CDV2OCARAJ1IRK3142F2', 15, 7.67);

    insert into ordine(numero, peso, spedito, consegnato, data_consegna, cliente, data)
    values('CDV2OCARAJ1IRK3142F2', 23.20, 'false', 'false',null, 'MTMZBN40H24C595L', '2022-01-04'); --Non ancora consegnato
commit;


--ordine di MTMZBN40H24C595L
begin transaction;
    --Quinto ordine composto da un solo acetp, 8 bottilie e sconto 50%.
    insert into composizione(prodotto, ordine, quantità, sconto)
    values('000000000aaae', 'IJJE0HVD2RYNS36AJ4SD', 8, 50);

    insert into ordine(numero, peso, spedito, consegnato, data_consegna, cliente, data)
    values('IJJE0HVD2RYNS36AJ4SD',3, 'true', 'false',null, 'MTMZBN40H24C595L', '2022-01-05'); --Non ancora consegnato

    insert into spedizione(ordine, tracking, corriere, data_spedizione)
    values('IJJE0HVD2RYNS36AJ4SD', '7581XQAUI8F1W1I1RS', 'UPS','2021-09-19');
commit;


--ordine di MTMZBN40H24C595L
begin transaction;
    insert into composizione(prodotto, ordine, quantità, sconto)
    values('000000000aaaa', 'IJJE0HVD2RYNS36AK4SD', 8, 50);

    insert into ordine(numero, peso, spedito, consegnato, data_consegna, cliente, data)
    values('IJJE0HVD2RYNS36AK4SD', 3, 'false', 'false',null, 'MTMZBN40H24C595L', '2022-01-06'); --Non ancora consegnato

commit;

/*begin transaction;
    --Ordine senza prodotti fa fallire la transazione
    insert into ordine(numero, peso, spedito, consegnato, data_consegna, cliente, data)
    values('IJJE0HVD2RYNS36A4SD', 2.6, 'false', 'false', null, 'SPLCQZ32S62I400K', '2010-01-10');
commit;*/

/*
begin transaction;
	-- Abbonamento privo di prodotti fa fallire la transazione
    insert into abbonamento(cliente, vigneto, tipologia, data_sottoscrizione, frequenza, costo_abbonamento)
    values('YLMNGD73B61F533I', 1, 'A', '2021-04-18', 1, 104.0);
commit;
*/