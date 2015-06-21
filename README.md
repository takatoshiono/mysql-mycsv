## mysql-mycsv

This is an example of MySQL storage engine for learning.
Target mysql version is 5.6.23.

Only read(select) is available.

## Install

1. git clone git@github.com:takatoshiono/mysql-mycsv.git
2. copy files under the `src` directory to the `storage/mycsv/` directory of the MySQL source tree.
  * e.g. ```cp -r `ghq list -p mysql-mycsv`/src/ mysql-5.6.23/storage/mycsv/```
3. build MySQL
  * e.g. `cmake . && make`
4. make install
5. now installed to `/usr/local/mysql`

### Install plugin

1. run mysql
  * e.g. `bin/mysqld --port=13306`
2. mysql -uroot -P13306
3. install plugin
  * e.g. ```mysql> install plugin MYCSV soname 'ha_mycsv.so';```
4. show storage engine

```
mysql> show storage engines ;
+--------------------+---------+----------------------------------------------------------------+--------------+------+------------+
| Engine             | Support | Comment                                                        | Transactions | XA   | Savepoints |
+--------------------+---------+----------------------------------------------------------------+--------------+------+------------+
| FEDERATED          | NO      | Federated MySQL storage engine                                 | NULL         | NULL | NULL       |
| MRG_MYISAM         | YES     | Collection of identical MyISAM tables                          | NO           | NO   | NO         |
| MyISAM             | YES     | MyISAM storage engine                                          | NO           | NO   | NO         |
| BLACKHOLE          | YES     | /dev/null storage engine (anything you write to it disappears) | NO           | NO   | NO         |
| CSV                | YES     | CSV storage engine                                             | NO           | NO   | NO         |
| MYCSV              | YES     | Example storage engine                                         | NO           | NO   | NO         |
| MEMORY             | YES     | Hash based, stored in memory, useful for temporary tables      | NO           | NO   | NO         |
| ARCHIVE            | YES     | Archive storage engine                                         | NO           | NO   | NO         |
| InnoDB             | DEFAULT | Supports transactions, row-level locking, and foreign keys     | YES          | YES  | YES        |
| PERFORMANCE_SCHEMA | YES     | Performance Schema                                             | NO           | NO   | NO         |
+--------------------+---------+----------------------------------------------------------------+--------------+------+------------+
10 rows in set (0.00 sec)
```

### SELECT * FROM ...

1. create table
  * `mysql> use test`
  * ```mysql> CREATE TABLE mycsv_test (id int NOT NULL, col1 int NOT NULL) ENGINE=MYCSV```
2. create file by yourself
  * ```echo 100,200 > /usr/local/mysql/data/test/mycsv_test.csv```
3. select

```
mysql> select * from mycsv_test ;
+-----+------+
| id  | col1 |
+-----+------+
| 100 |  200 |
+-----+------+
1 row in set (0.02 sec)
```

## References

* [MySQL Internals Manual :: 22 Writing a Custom Storage Engine](https://dev.mysql.com/doc/internals/en/custom-engine.html)
* [詳解MySQL](http://www.oreilly.co.jp/books/9784873113432/)

