import sqlite3

class SqlConnect:
	
	
	
	def __init__(self,db_name):
		'''
		Инициализация класса
		:param A:  Type is String. Database name
		'''
		self.db = db_name

	def request(self,question):
		'''
		SQL запрос на получение данных
		:param question:  Type is String. SQL request
		'''
		try:
			
			sqlite_connection = sqlite3.connect(self.db)
			cur = sqlite_connection.cursor()
			res = cur.execute(question)
			#Соединение с SQLite установлено. Запрос выполнен
			
		except sqlite3.Error as error:
			
			print("Ошибка при работе с sqlite: ", error)

		finally:
			
			if (sqlite_connection):
				ans = res.fetchall()
				cur.close()
				sqlite_connection.close()
				#Соединение с SQLite закрыто
				return(ans)

	def write(self,data):
		'''
		SQL запись данных
		:param question:  Type is String. SQL request
		'''
		try:
			
			sqlite_connection = sqlite3.connect(self.db)
			cur = sqlite_connection.cursor()
			res = cur.execute(data)
			sqlite_connection.commit()
			#Соединение с SQLite установлено. Запрос выполнен
			
		except sqlite3.Error as error:
			
			print("Ошибка при работе с sqlite: ", error)

		finally:
			#Соединение с SQLite закрыто
			if (sqlite_connection):
				cur.close()
				sqlite_connection.close()
				

		
Db = SqlConnect('sqlite_python.db')

#creation of tables:
if(Db.request("SELECT COUNT(1) FROM sqlite_master")[0][0] == 0):
	Db.write("CREATE TABLE Students(id, name, surname, age, city);")
	Db.write("CREATE TABLE Courses(id, name, time_start, time_end);")
	Db.write("CREATE TABLE Student_courses(student_id,course_id, FOREIGN KEY (student_id) REFERENCES Students (id), FOREIGN KEY (course_id) REFERENCES Courses (id));")
	Db.write("INSERT INTO Courses VALUES (1, 'python', '21.07.21', '21.08.21'), (2, 'java', '13.07.21', '16.08.21');")
	Db.write("INSERT INTO Students VALUES (1, 'Max', 'Brooks', 24, 'Spb'), (2, 'John', 'Stones', 15, 'Spb'), (3, 'Andy', 'Wings', 45, 'Manhester'), (4, 'Kate', 'Brooks', 34, 'Spb');")
	Db.write("INSERT INTO Student_courses VALUES (1, 1),(2, 1),(3, 1),(4, 2);")

#1. Всех студентов старше 30 лет.
print("Всех студентов старше 30 лет. ",Db.request("SELECT name FROM Students WHERE age > 30;"))

#2. Всех студентов, которые проходят курс по python.
print("Всех студентов, которые проходят курс по python. ",Db.request("SELECT name FROM Students WHERE id IN (SELECT student_id FROM Student_courses WHERE course_id IN (SELECT id FROM Courses WHERE name = 'python'));"))

#3. Всех студентов, которые проходят курс по python и из Spb.
print("Всех студентов, которые проходят курс по python и из Spb. ",Db.request("SELECT name FROM Students WHERE id IN (SELECT student_id FROM Student_courses WHERE course_id IN (SELECT id FROM Courses WHERE name = 'python')) AND city = 'Spb';"))
