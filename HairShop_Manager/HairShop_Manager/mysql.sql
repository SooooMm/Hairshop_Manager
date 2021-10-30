CREATE DATABASE hairshop_manager DEFAULT CHARACTER SET utf8;
use hairshop_manager;

create table customer(
	name varchar(15) not null,
	phone_num varchar(20) primary key,
	charge varchar(15),
	reward_point int,
	details varchar(45)
);

create table designer(
	name varchar(15) not null,
	phone_num varchar(20) primary key,
	time varchar(45),
	details varchar(45)
);

create table reservation(
	name varchar(15) not null,
	phone_num varchar(20) primary key,
	re_time varchar(30),
	details varchar(45)
);

SET @temp=0;
