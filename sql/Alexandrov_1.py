import sqlite3
try:
    sqlite_connection = sqlite3.connect('sqlite_python.db')
    cur = sqlite_connection.cursor()
    #creation of tables:
    res = cur.execute("CREATE TABLE Students(id, name, surname, age, city);")
    res = cur.execute("CREATE TABLE Courses(id, name, time_start, time_end);")
    res = cur.execute("CREATE TABLE Student_courses(student_id,course_id, FOREIGN KEY (student_id) REFERENCES Students (id), FOREIGN KEY (course_id) REFERENCES Courses (id));")
    
    sqlite_connection.commit()
    res = cur.execute("SELECT name FROM sqlite_master")
    print("Таблицы созданы:",res.fetchall())
    cur.close()
except sqlite3.Error as error:
    print("Ошибка при подключении к sqlite", error)

finally:
    if (sqlite_connection):
        sqlite_connection.close()
        print("Соединение с SQLite закрыто")
