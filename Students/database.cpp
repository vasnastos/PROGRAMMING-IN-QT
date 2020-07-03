#include "database.h"

Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("students.db");
    db.open();
    QSqlQuery q(db);
    q.exec("create table if not exists student(sid integer,name varchar(100),lastname varchar(100))");
    q.exec(QString("create table if not exists lesson(")+
           QString("lid integer,name varachar(100),semester integer)"));
    q.exec(QString("create table if not exists enroll(")+
           QString("sid integer,lid integer)"));
}


void    Database::addStudent(Student &s)
{
    if(existsStudent(s)) return;
    QSqlQuery query(db);
    query.prepare("INSERT INTO student (sid,name,lastname) VALUES (:sid,:name,:lastname)");
    query.bindValue(":sid",s.getId());
    query.bindValue(":name",s.getName());
    query.bindValue(":lastname",s.getLastname());
    query.exec();
}

void    Database::addLesson(Lesson &l)
{
    if(existsLesson(l)) return;
    QSqlQuery query(db);
    query.prepare("INSERT INTO lesson (lid,name,semester) VALUES (:lid,:name,:semester)");
    query.bindValue(":lid",l.getLessonId());
    query.bindValue(":name",l.getName());
    query.bindValue(":semester",l.getSemester());
    query.exec();
}

void    Database::addEnroll(Enroll &e)
{
    // na ylopoihthei na min mporei na mpei dilosi gia kodikous poy den yparxoun stin database
    if(existsEnroll(e)) return;
    QSqlQuery query(db);
    query.exec("select * from student where sid="+QString::number(e.getStudentId()));
    if(!query.next()) return;
    query.exec("select * from lesson where lid="+QString::number(e.getLessonId()));
    if(!query.next()) return;
    query.prepare("INSERT INTO enroll (sid,lid) VALUES (:sid,:lid)");
    query.bindValue(":sid",e.getStudentId());
    query.bindValue(":lid",e.getLessonId());
    query.exec();
}

bool    Database::existsStudent(Student &s)
{
    QSqlQuery q(db);
    q.exec("select * from student where sid="+QString::number(s.getId()));
    return q.next();
}

bool    Database::existsLesson(Lesson &l)
{
    QSqlQuery q(db);
    q.exec("select * from lesson where lid="+QString::number(l.getLessonId()));
    return q.next();
}

bool    Database::existsEnroll(Enroll &e)
{
   QSqlQuery q(db);
   q.exec("select * from enroll where sid="+QString::number(e.getStudentId())+" and lid="+QString::number(e.getLessonId()));
   return q.next();
}


QVector<Student>    Database::getStudents()
{
    QVector<Student> x;
    QSqlQuery query(db);
    query.exec("SELECT * FROM student");
    while (query.next())
    {
        Student C(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString());
        x.append(C);
    }
    return x;
}

QVector<Lesson>     Database::getLessons()
{
    QVector<Lesson> x;
    QSqlQuery query(db);
    query.exec("SELECT * FROM lesson");
    while (query.next())
    {
        Lesson C(query.value(0).toInt(),query.value(1).toString(),query.value(2).toInt());
        x.append(C);
    }
    return x;
}

QVector<Enroll>     Database::getEnrolls()
{
    QVector<Enroll> x;
    QSqlQuery query(db);
    query.exec("SELECT * FROM enroll");
    while (query.next())
    {
        Enroll C(query.value(0).toInt(),query.value(1).toInt());
        x.append(C);
    }
    return x;
}

void    Database::deleteStudent(Student &s)
{
    //Na ylopoihthei kai i diagrafi ton antistoixon mathimaton tou apo tin dilosi
    QSqlQuery query(db);
    query.exec("delete from student where sid="+QString::number(s.getId()));
    query.exec("delete from enroll where sid="+QString::number(s.getId()));
}

void    Database::deleteLesson(Lesson &l)
{
    //na ylopoihhthei kai i diagrafi ton diloseon me auto to mathima
    QSqlQuery query(db);
    query.exec("delete from lesson where lid="+QString::number(l.getLessonId()));
    query.exec("delete from enroll where lid="+QString::number(l.getLessonId()));
}

void    Database::deleteEnroll(Enroll &e)
{
    QSqlQuery query(db);
    query.exec("delete from enroll where sid="+QString::number(e.getStudentId())+" and lid="+
               QString::number(e.getLessonId()));
}

QString Database::getstudentlastname(int id)
{
    QSqlQuery qr(db);
    qr.exec("select lastname from student where sid="+QString::number(id));
    qr.next();
    return qr.value(0).toString();
}

QString Database::getlessonname(int lid)
{
    QSqlQuery qr(db);
    qr.exec("select name from lesson where lid="+QString::number(lid));
    qr.next();
    return qr.value(0).toString();
}
