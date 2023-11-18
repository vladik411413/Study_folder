import sqlite3
try:
    sqlite_connection = sqlite3.connect('sqlite_python.db')
    cur = sqlite_connection.cursor()
    
    #adding data into tables
    
    cur.execute("INSERT INTO Courses VALUES (1, 'python', '21.07.21', '21.08.21'), (2, 'java', '13.07.21', '16.08.21');")
    cur.execute("INSERT INTO Students VALUES (1, 'Max', 'Brooks', 24, 'Spb'), (2, 'John', 'Stones', 15, 'Spb'), (3, 'Andy', 'Wings', 45, 'Manhester'), (4, 'Kate', 'Brooks', 34, 'Spb');")
    cur.execute("INSERT INTO Student_courses VALUES (1, 1),(2, 1),(3, 1),(4, 2);")
    sqlite_connection.commit()
    print("Информация загружена.")
    
    #Напишите запросы, чтобы получить:
	
	#1. Всех студентов старше 30 лет.
    res = cur.execute("SELECT name FROM Students WHERE id IN (SELECT student_id FROM Student_courses WHERE course_id IN (SELECT id FROM Courses WHERE name = 'python'));")
    print("Все студенты, которые проходят курс по python",res.fetchall())
    
    #2. Всех студентов, которые проходят курс по python.
    res = cur.execute("SELECT name FROM Students WHERE age > 30;")
    print("Все студенты старше 30 лет", res.fetchall())
    
    #3. Всех студентов, которые проходят курс по python и из Spb.
    res = cur.execute("SELECT name FROM Students WHERE id IN (SELECT student_id FROM Student_courses WHERE course_id IN (SELECT id FROM Courses WHERE name = 'python')) AND city = 'Spb';")
    print("Все студенты, которые проходят курс по python и из Spb",res.fetchall())
    
    cur.close()
    
except sqlite3.Error as error:
    print("Ошибка при подключении к sqlite", error)

finally:
    if (sqlite_connection):
        sqlite_connection.close()
        print("Соединение с SQLite закрыто")
