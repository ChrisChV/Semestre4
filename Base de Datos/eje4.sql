create database ejercicio4;
use ejercicio4;


create table Coche(
Matricula char(11) not null,
Marca varchar(100) not null,
Precio int not null,
Color varchar(100),
DNI char(8) not null,
Modelo varchar(100));

alter table Coche
add constraint pk_coche
primary key(Matricula);

describe Coche;

create table Revision(
CodRev int not null);

alter table Revision
add constraint pk_revision
primary key(CodRev);