# Server Aloo <!-- omit in toc -->
- [1. Introduction](#1-introduction)
- [2. What you need](#2-what-you-need)
- [3. build](#3-build)
  - [3.1. build with qmake](#31-build-with-qmake)
  - [3.2. build with GNU make](#32-build-with-gnu-make)
- [4. Note](#4-note)

## 1. Introduction
This is a server which is built by Qt Framework run on Transport Layer with protocol TCP using for a chat application. This server manages message of client in a chat rooom. Identifications of client are saved in MySQL.

This server can be connected by all IP addresses of server (localhost, IP local, IP on Internet)
## 2. What you need

- qt5
```bash
sudo apt-get install qt5-default
```
- [mysql](https://dev.mysql.com/doc/mysql-apt-repo-quick-guide/en/)
- mysql driver for Qt
```bash
sudo apt-get install libqt5sql5-mysql
```
## 3. build

### 3.1. build with qmake
If you want to build this application with qmake, open file ``*.pro`` in QtCreator and ``Run qmake`` and then ``Run``.

### 3.2. build with GNU make
If you use GNU Make:
```Bash
# From root path of project
make all 
# Run application
make run
```

## 4. Note
You can get client application from this [repo](https://github.com/minhthuc2502/AlooClient)

