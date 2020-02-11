create database guestbook_db;

use guestbook_db;

create table guestbook_table (
    guest_idx   int primary key auto_increment
,   guest_name  varchar(100)    not null
,   guest_text  varchar(500)    not null
);
