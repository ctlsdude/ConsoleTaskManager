Прим: Задачи, которые изначально есть в файле tasklst.csv, используются для доказательства работы комманды select
task1,description example1,2022-11-11 20:54,category1,ON
task2,description example2,1990-10-09 20:54,category1,ON
task3,description example3,2021-03-04 23:54,category2,ON
task4,description example4,2020-05-05 00:53,category2,ON
newNameVariant1,another text1,1999-05-05 20:54,animals,ON
newNameVariant2,another text2,1998-10-30 20:55,tracks,ON
newNameVariant3,another text3,2030-10-30 20:55,tracks,ON

//----------Готовый текст комманд для проверки  
1) Добавление задачи
select *
add "testAdd" "testAdd Description" "2000-01-01 00:00" "test"
select *

2) Отметка задачи как выполненной
add "testDone" "testDone Description" "2000-01-01 00:00" "test"
select * where description="testDone Description"
done testDone
select * where description="testDone Description"

3.1) Select, Разница между операторами >, >= и =
select * where date > "2021-03-04 23:54"
select * where date >= "2021-03-04 23:54"
select * where date = "2021-03-04 23:54"

3.2) Select, Подверждение работы ключевого слова like для description
select * where description like "ex"
select * where description="description example2"

3.3) Select, Подверждение работы комбинации условия:
select * where date > "2000-01-01 00:01" and category="category1" and description like "example"

4) Подверждение работы комманды update
add "testUpdate" "testUpdate Description" "2000-01-01 00:00" "test"
select * where description="testUpdate Description"
update testDone
...Ввод пользователем значений
select * 

5)Удаление задачи
add "testDelete" "testDelete Description" "2000-01-01 00:00" "test"
select *
delete testDelete
select *

6)Сохранение результатов
select *
add "testUpdate" "testUpdate Description" "2000-01-01 00:00" "test"
quit или q
Запустите снова
select *   