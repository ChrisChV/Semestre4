use tienda;
describe Clientes;

create table Producto(
codPro int not null,
nombre varchar(100) not null,
RUC char(11) not null);

describe Producto;

alter table Producto
add constraint pk_Producto
primary key(codPro);

alter table Compras
add constraint fk_compras_producto
foreign key(codPro)
references Producto(codPro);

create table Proveedor(
RUC char(11) not null,
nombre varchar(100) not null,
dir varchar(200));

describe Proveedor;

alter table Proveedor
add constraint pk_proveedor
primary key(RUC);

alter table Producto
add constraint fk_producto_proveedor
foreign key(RUC)
references Proveedor(RUC);

