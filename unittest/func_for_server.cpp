#include "func_for_server.h"
#include <QDebug>
#include <iostream>
#include <QCoreApplication>


QByteArray parsing(QString str, long desc)
{
QByteArray stats;
QByteArray ansv;//создание масива для ответа на сервер
QStringList args = str.split(" ");//создание списка копирующего строку ввода разделяя её по пробелу
	str = args.front();//оставляет в строке первое слова из неё 
	args.pop_front();//удаляет слово команду (первое) из списка

//по строке определяет какую функцию нужно выполнять
	if(str=="auth")
	{
		return auth(args[0],args[1],desc);
		//sends the list to the authorization function
	}
	if(str=="reg")
	{
		return reg(args[0],args[1],desc);
		//sends the list to the registration function
	}
	if(str=="stat")
	{
	return stat(desc, stats);
	//plug
	}
	if (str == "checktask1")
	{
		return get_var_task_1(args[0], args[1], desc, stats);
		//plug
	}
	return "check is this thing work \r\n";
	//it speaks for itself
}
QByteArray stat(long desc, QByteArray& stats)
{
	
	QByteArray ansv;
	ansv = stats;
	return ansv;
	/*
	QString socket_descriptor = QString::number(desc);
	QString query = Singleton::getInstance()->sendQuery("SELECT task1 FROM users WHERE token = '" + socket_descriptor + "'");
	qDebug() << query;
	QString response = "";
	if (Singleton::getInstance()->sendQuery("SELECT task1 FROM users WHERE token = '" + socket_descriptor + "'") != "") { //Singleton::getInstance()->execQuery(query).size() > 0
		//response = Singleton::getInstance()->execQuery(query);
		ansv = ("stat+ " + query + "\r\n").toUtf8();
		return ansv;
	}
	else
		return "stat- \r\n";
		*/
}

QByteArray auth(QString log, QString pas,long desc)
{
QByteArray ansv;
		if(Singleton::getInstance()->sendQuery("SELECT * from Users where login = '"+log+"' and password = '"+pas+"' and token = 0")!="")
			{
			ansv= ("auth+ "+log+"\r\n").toUtf8();
			//success authorization report
			QString socket_descriptor=QString::number(desc);
			Singleton::getInstance()->sendQuery("update Users set token = '" + socket_descriptor + "' WHERE login = '" + log+"'" );
			//shows that is online
			return ansv;
			}
		else 
			{
			ansv= "auth- \r\n";
			//authorization denied report
			qDebug()<<ansv;
			return ansv;
			}
}
QByteArray reg(QString log, QString pas,long desc)
{
QByteArray ansv;
QString socket_descriptor=QString::number(desc);
if(Singleton::getInstance()->sendQuery("SELECT * from Users where login = '"+log+"'")=="")
//check registration before doing some thing
{	
	Singleton::getInstance()->sendQuery("insert into Users (userid,login, password, token) VALUES ('" + socket_descriptor + "','"+log+"','"+pas+"',0)");
	//registration

	//Singleton::getInstance()->sendQuery("INSERT into Users (userid,login, password, token) VALUES (224,'admin','admin',0)");
	//code for check how registration work

	if(Singleton::getInstance()->sendQuery("SELECT * from Users where login = '"+log+"' and password = '"+pas+"' and token = 0")!="")
	//check registration	
	{
	ansv= "reg+ \r\n";//success registration report
	return ansv;
	}
	else
	{
	ansv= "reg- \r\n";//error registration report
	return ansv;
	}
}
else
	{
	ansv= "reg- already taken \r\n";//registration denied report
	return ansv;
	}

}
/*
QByteArray mlta(QString ansv)
{
	bool flag= true;
	int s[10], k, z = 0, o = 0, x1 = 15, x2 = 10, x3 = 0;
	int massive[x1 = 15, x2 = 10, x3 = 0]; // x1 строки а x2 столбцы x3 значение
	for (int i = 0; i <=9;i++) { 
		for (int j = 0; j <= 14; j++) {
			k = ansv.split(" ")[z].toInt();
			massive[j, i, k];
			z++;
		}
	}
	z = 0;
	while (flag == true){
		for (int g = 0; g <= 9; g++) {
			for (int r = 0; r <= 14; r++) {
				s[z] = s[z] + massive[r, g];	
				z++;
			}
		}
		for (int o = 0; o<=9; o++) {
			if (s[o] >= s[o + 1]) {
				sokr(massive, o, s);
			}
		}	
	}
}
void sokr(int*& massive, int o, int*& s) {
	int sovp = 0;
	for (int i = 0; i <= 14; i++) {

		if (massive[i, o] == massive[i, o + 1]) {
			sovp++;
		}
	}
	if (sovp == s[o]) {
		for (int g = 0; g <= 9; g++) {
			for (int r = 0; r <= 14; r++) {
				massive[r, g, 0];
			}
		}
	}

}
*/
QByteArray get_var_task_1(QString var, QString otvet, long desc, QByteArray& stats)
{
	QString neznayu;
	QByteArray ansv;
	QString socket_descriptor = QString::number(desc);
	if (check_task_1(var, otvet))
	{
		Singleton::getInstance()->sendQuery("update Users set task1 = 1 where token ='" + socket_descriptor + "'");
		ansv = "Check+\r\n";//Задание выполнено успешно
		neznayu = "5";
		stats = neznayu.toUtf8();
		return ansv;
	}
	else
	{
		Singleton::getInstance()->sendQuery("update Users set task1 = -1 where token ='" + socket_descriptor + "'");
		ansv = "Check- \r\n";//Задание провалено 
		neznayu = "2";
		stats = neznayu.toUtf8();
		return ansv;
	}
}
bool check_task_1(QString variant, QString answer)
{
	QString prom2;
	float prom;
	if (variant == "1")
	{
		prom = 3;
	}
	if (variant == "2")
	{
		prom = 5;
	}
	prom2 = QString::number(prom);
	if (prom2 == answer)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*	first prototype

if (str == "stop")
		return ("goodbye" +str).toUtf8();
	if (str == "rigistraciya")
		return ("vvedite nik i parol: " +str).toUtf8();
		if (str != NULL)
		//добовляем в бд ник и пароль
		return ("vy uspesno za rigistrovalis" +str).toUtf8();
	if (str == "autorizaciya")
		return ("vvedite nik i parol: " +str).toUtf8();
		if (str != NULL)
		//проверяем в бд ник и пароль
		return ("vy uspesno voshli" +str).toUtf8();
	if (str == "start work")
	//проверка на автористрацию
		return ("zdes poka nichego net no ya rabotau" +str).toUtf8();
	else
		return ("net takoy komandy " +str).toUtf8();*/

//pair<int,string> func(){
// return pair<int,string> (123456, "asdfghjkuytew")
//}