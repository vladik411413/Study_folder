#https://github.com/vladik411413/Study_folder.git

from datetime import date
from peewee import *

db = SqliteDatabase('peewee_db.db') #creation of the db

		
		
class Students(Model):
	
	student_id = IntegerField()
	name = CharField()
	surname = CharField()
	age = IntegerField()
	city = CharField()

	class Meta:
		database = db # This model uses the "peewee_db" database.



class Courses(Model):
	
	course_id = IntegerField()
	name = CharField()
	time_start = DateField()
	time_end = DateField()

	class Meta:
		database = db # This model uses the "peewee_db" database.



class Student_courses(Model):
	student_id = ForeignKeyField(Students, backref='stud_id')
	course_id = ForeignKeyField(Courses, backref='cour_id')
	class Meta:
		database = db # This model uses the "peewee_db" database.
		

db.connect() # connection to the db

if((db.table_exists(Students) and db.table_exists(Courses) and db.table_exists(Student_courses))==False):
	db.create_tables([Students,Courses,Student_courses]) #creation of tables
	
	Courses.create(course_id = 1, name = 'python', time_start = date(21,7,21), time_end = date(21,8,21))
	Courses.create(course_id = 2, name = 'java', time_start = date(21,7,21), time_end = date(21,8,21))


	Students.create(student_id = 1, name = 'Max', surname = 'Brooks', age = 24, city = 'Spb')
	Students.create(student_id = 2, name = 'John', surname = 'Stones',age =  15, city = 'Spb')
	Students.create(student_id = 3, name = 'Andy', surname = 'Wings',age =  45, city = 'Manhester')
	Students.create(student_id = 4, name = 'Kate', surname = 'Brooks',age =  34, city = 'Spb')

	Student_courses.create(student_id = 1,course_id = 1)
	Student_courses.create(student_id = 2,course_id = 1)
	Student_courses.create(student_id = 3,course_id = 1)
	Student_courses.create(student_id = 4,course_id = 2)

#1. Всех студентов старше 30 лет.

query = Students.select().where(Students.age < 30)
print("Всех студентов старше 30 лет. ")
for person in query:
    print(person.name)



#2. Всех студентов, которые проходят курс по python.

print("Всех студентов, которые проходят курс по python. ")

#выбираем текущие курсы python

python_ids = Courses.select(Courses).where(Courses.name == 'python')

for python in python_ids: #для каждого из текущих курсов python
	for student_courses in python.cour_id: #для каждой из пар (текущий курс, студент_id)
		for student in Students.select().where(Students.student_id == student_courses.student_id): #выписываем имена людей зная студент_id
			print(student.name)



#3. Всех студентов, которые проходят курс по python и из Spb.
print("Всех студентов, которые проходят курс по python и из Spb. ")
for python in python_ids: #для каждого из текущих курсов python
	for student_courses in python.cour_id: #для каждой из пар (текущий курс, студент_id)
		for student in Students.select().where((Students.student_id == student_courses.student_id) & (Students.city == 'Spb')): #выписываем имена людей зная студент_id и зная что они из Спб
			print(student.name)

    
