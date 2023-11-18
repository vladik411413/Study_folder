import sqlite3
try:
    sqlite_connection = sqlite3.connect('sqlite_python.db')
    cur = sqlite_connection.cursor()
    #res = cur.execute("CREATE TABLE Students(id, name, surname, age, city);")
    #res = cur.execute("CREATE TABLE Courses(id, name, time_start, time_end);")
    #res = cur.execute("CREATE TABLE Student_courses(student_id,course_id, FOREIGN KEY (student_id) REFERENCES Students (id), FOREIGN KEY (course_id) REFERENCES Courses (id));")
    #cur.execute("INSERT INTO Courses VALUES (1, 'python', '21.07.21', '21.08.21'), (2, 'java', '13.07.21', '16.08.21');")
    #cur.execute("INSERT INTO Students VALUES (1, 'Max', 'Brooks', 24, 'Spb'), (2, 'John', 'Stones', 15, 'Spb'), (3, 'Andy', 'Wings', 45, 'Manhester'), (4, 'Kate', 'Brooks', 34, 'Spb');")
    cur.execute("""INSERT INTO Student_courses VALUES
	(1, 1),
	(2, 1),
	(3, 1),
	(4, 2);
    """)
    sqlite_connection.commit()
    print("Таблицы созданы:")
    res = cur.execute("SELECT * FROM Student_courses,Courses WHERE Courses.name = 'python' ")
    print("Всех студентов, которые проходят курс по python",res.fetchall())
    res = cur.execute("SELECT * FROM Students WHERE age > 30;")
    print("Всех студентов старше 30 лет", res.fetchall())
    res = cur.execute("SELECT * FROM Courses;")
    print(res.fetchall())
    cur.close()
except sqlite3.Error as error:
    print("Ошибка при подключении к sqlite", error)

finally:
    if (sqlite_connection):
        sqlite_connection.close()
        print("Соединение с SQLite закрыто")
