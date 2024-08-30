#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#include<cstdio>
#include<conio.h>


using namespace std;
class student{
  private:
    char name[20];
    char address[20];
    float marks;
    int rollno;
 public:
    void getdata(){
        cout<<setw(20)<<"\tEnter Name:\n"<<endl; 
        cin>>name;
        cout<<setw(50)<<"\tEnter Address:\n"<<endl;
         cin>>address;
        cout<<"\tEnter double digit rollno:\n"<<endl; 
        cin>>rollno;
        cout<<"\tEnter Total Marks:\n"<<endl; 
        cin>>marks;
    }
    void putdata(){
        cout<<setw(30)<<"Name:"<<name<<setw(30)<<"Address:"<<address<<setw(10)<<"Roll no:"<<rollno<<setw(10)<<setprecision(2)<<"Marks:"<<marks<<endl;
    }
    int rolln(){
        return rollno;
    }
};
//to write file 
  void write_data(){
    student s;
    fstream input;
    input.open("student.dat",ios::out);
    int n;
    cout<<"Enter the no. of Students:\n";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        s.getdata();
        input.write((char*)&s,sizeof(s));
    }
    cout<<"\n\t FIlE Written!";
    input.close();  
  }
  //to read files 
    void read_data(){
    student s;
    fstream output;
    output.open("student.dat",ios::in);
    if (output.fail())//error handeling while operating file 
    {
        cout<<"Error Opening file!\n";
        cout<<"Exiting............"<<endl;
        exit(1);
    }
    while(output.read((char*)&s,sizeof(s))){
        s.putdata();

    }
    cout<<"\n\t FIlE READ sucessfully!";
    output.close();  
  } 
   //Adding data 
    void add_data(){
    student s;
    fstream input;
    input.open("student.dat",ios::app);
        if (input.fail())//error handeling while operating file 
    {
        cout<<"Error Opening file!\n";
        cout<<"Exiting............"<<endl;
        exit(1);
    }
    char choice;
    do{
        s.getdata();
        input.write((char*)&s,sizeof(s));
        cout<<"Want to add more?(y/n)\n";
        cin>>choice;

    }while(choice=='y'||choice=='Y');
    
    cout<<"\n\t Added Sucessfully!";
    input.close();  
  }

  //searching data 
void search_data() {
    student s;
    fstream output;
    output.open("student.dat", ios::in);
    if (output.fail()) { // error handling while opening file
        cout << "Error Opening file!\n";
        cout << "Exiting............" << endl;
        exit(1);
    }
    
    int roll;
    cout << "Enter The Roll no:\n"; 
    cin >> roll;
    
    bool found = false; // Flag to track if any record is found
    
    while (output.read((char*)&s, sizeof(s))) {
        
        if (s.rolln() == roll) {
            s.putdata();
            found = true;
            cout << "Do you want to continue searching....(y/n)? ";
            char ch;
            cin >> ch;
            if (ch == 'y' || ch == 'Y') {
                 cout << "Enter The Roll no:\n"; 
                 cin >> roll;
                continue; // Continue searching for more records
            } else {
                break; // Exit the loop
            }
        }
    }
    
    if (!found) {
        cout << "\n\tNo record found!";
    } else {
        cout << "\n\tSearch successful!";
    }
    
    output.close();  
}

// to modify the selected data 
void modify_data() {
    student s;
    fstream output;
    output.open("student.dat", ios::in | ios::out | ios::binary);
    if (output.fail()) { // Error handling while opening the file
        cout << "Error Opening file!\n";
        cout << "Exiting............" << endl;
        exit(1);
    }
    
    int roll;
    cout << "Enter The Roll no:\n"; 
    cin >> roll;
    
    bool found = false; // Flag to track if any record is found
    
    while (output.read((char*)&s, sizeof(s))) {
        if (s.rolln() == roll) {
            cout << "Record found. Enter new details:\n";
            s.getdata();
            
            // Move the file pointer back to the start of the current record
            output.seekp(output.tellg() - static_cast<std::streamoff>(sizeof(student)));
            
            // Write the modified record
            output.write((char*)&s, sizeof(s));
            
            found = true;
            cout << "\n\tRecord updated successfully!";
            break; // Exit the loop after updating
        }
    }
    
    if (!found) {
        cout << "\n\tNo record found!";
    }
    
    output.close();  
}

//for deleting data 
void delete_data() {
    student s;
    fstream input, temp;
    int roll;
    bool found = false;

    input.open("student.dat", ios::in | ios::binary);
    if (input.fail()) {
        cout << "Error Opening file!\n";
        return;
    }

    temp.open("temp.dat", ios::out | ios::binary);
    if (temp.fail()) {
        cout << "Error Creating temporary file!\n";
        input.close();
        return;
    }

    cout << "Enter the Roll no to delete:\n";
    cin >> roll;

    while (input.read((char*)&s, sizeof(s))) {
        if (s.rolln() == roll) {
            found = true; // Skip writing this record to the temp file
            cout << "Record deleted successfully!\n";
        } else {
            temp.write((char*)&s, sizeof(s)); // Write all other records to the temp file
        }
    }

    input.close();
    temp.close();

    if (!found) {
        cout << "No record found with Roll no: " << roll << endl;
    } else {
        // Remove the original file and rename the temp file to the original file name
        remove("student.dat");
        rename("temp.dat", "student.dat");
    }
}
 // file info
 void file_info(){
       student s;
       fstream calc;
       calc.open("student.dat",ios::in | ios::binary);
       if(calc.fail()){
          cout<<"Error Opening File...";
          cout<<"Exiting...";
       }
       calc.seekg(0,ios::end);
    //   streampos total_size=calc.tellg();
      cout<<"\nTotal size of file:"<<calc.tellg()<<"bytes.\n";
      cout<<"\nTotal No. of record:"<< calc.tellg()/sizeof(student);
    calc.close();
 }


  //MAIN PROGRAM
int main(){
    while(1){
    int ch;
    cout<<"\n\n<------Student Management System-------->\n\n";
    cout<<"1-->Write student record to a file\n"; 
    cout<<"2-->Read students record from a file\n";
    cout<<"3-->Update(add) the student record\n"; 
    cout<<"4-->Search a student record\n";
    cout<<"5-->Modify the student record\n";
    cout<<"6-->Delete the student record\n";
    cout<<"7-->Total file size and No. of records\n";
    cout<<"8-->EXIT\n";
    cin>>ch;
    switch (ch)
    {
    case 1:
        write_data();
        break;
    case 2:
        read_data();
        break;
    case 3:
        add_data();
        break;
    case 4:
        search_data();
        break;
    case 5:
        modify_data();
        break;
    case 6:
        delete_data();
        break;
    case 7:
        file_info();
        break;
    case 8:
       exit(1);
    default:
        cout<<"Invliad Input!";
        break;

  }
  getch();}
 }
