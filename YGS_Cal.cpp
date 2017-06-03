#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LL.h"



class Student{
private:
	string id;
	double scores[4][3];
	void setScores(double s[4][2]){
		for (int i = 0; i < 4; i++){
			scores[i][0] = s[i][0];
			scores[i][1] = s[i][1];
			scores[i][2] = s[i][0] - ((double)s[i][1]) / 3;
		}
	}
public:
	Student()
	{
		id = -1;
	}
	Student(string i, double s[4][2]){
		id = i;
		setScores(s);
	}
	string getId()
	{
		return id;
	}
	double* getScores(){
		double nets[4];
		for (int i = 0; i < 4; i++)
			nets[i] = scores[i][2];
		return nets;
	}
	
};
template <size_t N>
void splitString(string(&arr)[N], string str)
{
	int n = 0;
	istringstream iss(str);
	for (auto it = istream_iterator<string>(iss); it != istream_iterator<string>() && n < N; ++it, ++n)
		arr[n] = *it;
}
string CalculateScores(double nets[])
{
	string result;
	double ygs_1 =(nets[0]*10+50)*20+(nets[1]*10+50)*10+(nets[2]*10+50)*40+(nets[3]*10+50)*30;
	double ygs_2 =(nets[0]*10+50)*20+(nets[1]*10+50)*10+(nets[2]*10+50)*30+(nets[3]*10+50)*40;
	double ygs_3 =(nets[0]*10+50)*40+(nets[1]*10+50)*30+(nets[2]*10+50)*20+(nets[3]*10+50)*10;
	double ygs_4 =(nets[0]*10+50)*30+(nets[1]*10+50)*40+(nets[2]*10+50)*20+(nets[3]*10+50)*10;

	result ="YGS-1:" + to_string( ygs_1) +"\n" +"YGS-1:" +  to_string(ygs_2)+"\n" +"YGS-1:" + to_string( ygs_3)+"\n" +"YGS-1:" + to_string( ygs_4)+"\n" ;
	return result;
}
class StudentLL : public LinkedList<Student>
{
public:
	Student search(string s){
	
		Node <Student> *p = head;
	bool found = false;
	//node in the list
	while (p != NULL && !found) //search the list
	{
		if (p->data.getId() == s )
			found = true;
		else
			p = p->link;
	}
	return p->data;
	}

};
int main()
{
	StudentLL student_list = StudentLL();
	//read friends file and place friends
	ifstream stuFile("students_notes.txt");
	string line;
	int i = 0;
	if (stuFile.is_open())
	{
		while (!stuFile.eof())
		{
			getline(stuFile, line);
			string id;
			double nts[4][2];
			string notesString[9];
			splitString(notesString, line);
			for (int n = 0; n < 9; n++)
			{
				id = notesString[0];
				nts[0][0] = stod(notesString[1]);
				nts[0][1] = stod(notesString[2]);
				nts[1][0] = stod(notesString[3]);
				nts[1][1] = stod(notesString[4]);
				nts[2][0] = stod(notesString[5]);
				nts[2][1] = stod(notesString[6]);
				nts[3][0] = stod(notesString[7]);
				nts[3][1] = stod(notesString[8]);
			}
			Student s = Student(id,nts);
			student_list.insertFirst(s);
			i++;
		}
		//puan hesaplayan function yazýlacak
		//kullanýcý için yazýlacak
		// kullanýcýnýn girdigine göre student puanlarý hesaplanacak
		//puanlar ekranda gösterilecek
		string userReq;
		cout<<"Find | List | Quit"<<endl;
		cout<<"Enter your choice of action:";
		cin>>userReq;
		Node<Student> *onStud= student_list.head;
		while(!(userReq=="Quit"))
		{
			if(userReq=="Find")
			{
				do{
					cout<<CalculateScores(onStud->data.getScores())<<endl;
				onStud= onStud->link;
				}while(onStud!=NULL);
			}
			else if(userReq=="List"){
				string id;
				cout<<"Enter student id";
				cin>>id;
				Student stdnt=student_list.search(id);
				cout<<CalculateScores(stdnt.getScores())<<endl;
			}
		}
		stuFile.close();
	}
	cout<<"can not read file"<<endl;
	system("Pause");
	return 0;
}