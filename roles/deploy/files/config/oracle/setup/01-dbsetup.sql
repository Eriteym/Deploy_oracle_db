alter session set container = ORCLPDB1;

grant sysdba to PDBADMIN;

CREATE TABLESPACE STX DATAFILE 'stx.dat' SIZE 100M AUTOEXTEND ON;
CREATE TABLESPACE STARTEXT DATAFILE 'startext.dat' SIZE 100M AUTOEXTEND ON;
CREATE TABLESPACE RDM DATAFILE 'rdm.dat' SIZE 100M AUTOEXTEND ON;

create or replace directory LOCAL_PUMP_DIR as '/opt/oracle/dump';

grant read,write on DIRECTORY LOCAL_PUMP_DIR to PDBADMIN;

grant create table to PDBADMIN;

grant imp_full_database to PDBADMIN;

ALTER USER PDBADMIN quota unlimited on USERS;